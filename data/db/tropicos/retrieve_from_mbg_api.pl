#################################################################
# Retrieve complete dump of Tropicos taxonomy, formatted for
# import to the TNRS database
#
# Script by: Jerry Lu
# All comments added by: Brad Boyle (bboyle@email.arizona.edu)
#################################################################


use strict;
use Readonly;
use POE qw( Wheel::Run Filter::Line );
use Getopt::Long;
use LWP::Simple ();
use HTML::Entities;
use Encode;
use JSON::XS;
#use XML::Bare;
use Text::CSV_XS;

Readonly::Scalar my $MAX_CHILDREN => 6;
Readonly::Scalar my $MAX_RETRY	=> 30;
Readonly::Scalar my $TIME_OUT => 10;
Readonly::Scalar my $base_uri => "http://services.tropicos.org";
Readonly::Scalar my $key => '00fdfffb-5e72-48f8-90fa-dc41c09f8db0';
Readonly::Scalar my $format => "json";

binmode(STDOUT, ":utf8");

#my $startid=25542851;
my $count=0;

my @header=qw/
	nameID
	parentNameID
	scientificName
	scientificNameAuthorship
	nameRank
	nameUri
	isHybrid
	genus
	specificEpithet
	rankIndicator
	otherEpithet
	subclass
	family
	acceptance
	acceptedNameID
	NomenclatureStatusID
	NomenclatureStatusName
	Symbol
/;

my ($startid, $pagesize, $limit, $input, $noheader);
GetOptions (
	"s|startid=i"	=> \$startid,
	"p|pagezies=i"	=> \$pagesize,
	"l|limit=i"		=> \$limit,
	"i|input=s"		=> \$input,
	"n|noheader"	=> \$noheader,
);
$startid||=0;
$pagesize||=1000;
if ($limit && $limit < $pagesize) {
	$pagesize=$limit;
}

my $sid=$startid;
my @nameid;
if (defined $input) {
	unless ($input eq 'stdin') {
		push @ARGV, $input;
	}
	while (<>) {
		chomp;
		next if $_ eq 'nameID';
		push @nameid, $_;
	}
} else {
	my $n=0;
	while( my @nid=@{retrieve_nameid($sid)} ) {
		my $retrieved=scalar @nid;
		last unless $retrieved;
		if ($limit && ($n+$retrieved) > $limit) {
			push @nameid, @nid[0 .. $limit-$n-1];
			last;
		} else {
			push @nameid, @nid;
			$n+=$retrieved;
		}
		$sid=$nameid[-1]+1;
	}
}

my $csv = Text::CSV_XS->new({ binary => 1 }) or die "Cannot use CSV: ".Text::CSV_XS->error_diag();
unless ($noheader) {
	$csv->print(\*STDOUT, \@header);
	print "\n";
}

sub on_start {
	my ($kernel, $heap) = @_[KERNEL, HEAP];
	$heap->{child}||={};
	while (keys(%{$heap->{child}}) < $MAX_CHILDREN) {
		last if $count > $#nameid;
		my $nameid=$nameid[$count++];
		my $child = POE::Wheel::Run->new(
			Program => \&worker,
			StdoutEvent  => "got_child_stdout",
			StderrEvent  => "got_child_stderr",
			CloseEvent   => "got_child_close",
		);

		$kernel->sig_child($child->PID, "got_child_signal");
		$heap->{child}{$child->ID} = $child;

		$child->put($nameid, "");
		print STDERR "Processed $count\n" if $count % 1000 == 0;
	}
}

sub on_child_stdout {
	my ($heap, $stdout_line, $wid) = @_[HEAP, ARG0, ARG1];
	my $child = $heap->{child}{$wid};
	#print "pid ", $child->PID, " STDOUT: $stdout_line\n";
	print decode_utf8($stdout_line) . "\n";
}

sub on_child_stderr {
	my ($heap, $stderr_line, $wid) = @_[HEAP, ARG0, ARG1];
	my $child = $heap->{child}{$wid};
	print STDERR "pid ", $child->PID, " STDERR: " . decode_utf8($stderr_line) . "\n";
}

sub on_child_close {
	my ($kernel, $heap, $wid) = @_[KERNEL, HEAP, ARG0];
	my $child=delete $heap->{child}->{$wid};
	$kernel->yield("next_task");
	#print "pid ", $child->PID, " closed\n"; 
}

sub on_child_signal {
	my ($heap, $sig, $pid, $exit_val)= @_[ HEAP, ARG0..ARG2];
	my $details = delete $heap->{$pid};
	#print "pid ", $pid, " exited with: $exit_val\n";
}

sub worker {
	binmode(STDOUT, ":utf8");
	while (my $line=<STDIN>) {
		chomp $line;
		last if $line eq "";
		my $nameid=$line;
		my $output=build_output($nameid);
		$csv->print(\*STDOUT, $output);
		print "\n";
	}
}

sub build_output {
	my ($nameid)=@_;
	my $result;
	my $retry=0;
	while (1) {
		my $name_data=retrieve_name($nameid);
		my $acceptance_data=retrieve_acceptance($nameid);
		my $highertaxa_data=retrieve_highertaxa($nameid);
		my %hash;
		$hash{nameID}=$name_data->{NameId};
		$hash{parentNameID}='';
		if (exists $highertaxa_data->[-1]) {
			$hash{parentNameID}=$highertaxa_data->[-1]{NameId};
		}
		$hash{scientificName}=$name_data->{ScientificName};
		$hash{scientificNameAuthorship}=$name_data->{ScientificNameWithAuthors};
		$hash{scientificNameAuthorship}=~s/^\Q$hash{scientificName}\E\s+//;
		$hash{nameRank}=$name_data->{Rank};
		$hash{nameUri}=$name_data->{Source};
		$hash{isHybrid}=$name_data->{IsHybrid} || '';
		$hash{genus}=$name_data->{Genus} || '';
		$hash{specificEpithet}=$name_data->{SpeciesEpithet} || '';
		$hash{rankIndicator}=$name_data->{RankAbbreviation};
		$hash{otherEpithet}=$name_data->{OtherEpithet} || '';
		$hash{NomenclatureStatusID}=$name_data->{NomenclatureStatusID} || '';
		$hash{NomenclatureStatusName}=$name_data->{NomenclatureStatusName} || '';
		$hash{Symbol}=$name_data->{Symbol} || '';

		$hash{subclass}='';
		foreach (@$highertaxa_data) {
			if ($_->{Rank} eq "subclass") {
				$hash{subclass}=$_->{ScientificName};
			}
		}
		$hash{family}=$name_data->{Family} || '';
		$hash{acceptance}=$acceptance_data->{Acceptance};
		if ($hash{acceptance} eq "Synonym") {
			$hash{acceptance}='S';
		} elsif ($hash{acceptance} eq "Accepted") {
			$hash{acceptance}='A';
		} else {
			$hash{acceptance}='';
		}

		$hash{acceptedNameID}=$acceptance_data->{AcceptedNameId} || '';

		$retry++;
		if ( $hash{nameID} ) {
			$result=[@hash{@header}];
			last;
		} else {
			sleep($TIME_OUT);
			unless ($retry < $MAX_RETRY) { 
				print STDERR "Too many tries in building data: $nameid\n";
				$retry=0;
			}
		}
	}
	$result;
}

sub retrieve_nameid {
	my ($startid)=@_;
	my $uri="$base_uri/Name/List?startid=$startid&PageSize=$pagesize&apikey=$key&format=$format";
	my $result=[];
	if (my $json=retrieve_parsed_from_api($uri)) {
		unless (exists $json->[0]{Error}) {
			foreach (@$json) {
				push @$result, $_->{NameId} if exists $_->{NameId};
			}
		}
	}
	$result;
}

sub retrieve_name {
	my ($nameid)=@_;
	my $uri="$base_uri/Name/$nameid?apikey=$key&format=$format";
	my $result={};
	if (my $json=retrieve_parsed_from_api($uri)) {
		unless (exists $json->{Error}) {
			$result=$json;
		}
	}
	$result;
}

sub retrieve_acceptance {
	my ($nameid)=@_;
	my $uri="$base_uri/Name/$nameid/ComputedAcceptance?apikey=$key&format=$format";
	my $result={};
	if (my $json=retrieve_parsed_from_api($uri)) {
		unless (exists $json->{Error}) {
			$result->{Acceptance}=$json->{Acceptance};
			if ($result->{Acceptance} eq "Synonym" && exists $json->{AcceptedName}) {
				$result->{AcceptedNameId}=$json->{AcceptedName}{NameId};
			}
		}
	}
	$result;
}

sub retrieve_highertaxa {
	my ($nameid)=@_;
	my $uri="$base_uri/Name/$nameid/HigherTaxa?apikey=$key&format=$format";
	my $result=[];
	if (my $json=retrieve_parsed_from_api($uri)) {
		#my $tree=XML::Bare::xmlin($res);
		unless ($json->[0]{Error}) {
			#$result=$tree->{Name};
			#unless (ref $result eq "ARRAY") {
			#	$result=[$result];
			#}
			$result=$json;
		}
	}
	$result;
}

sub retrieve_raw_from_api { 
	my ($uri)=@_;
	my $retry=0;
	my $res='';
	#while ( ! $res && $retry < $MAX_RETRY) {
	while(! $res) {
		$res=LWP::Simple::get($uri);
		$retry++;
		sleep($TIME_OUT) unless $res;
		unless ($retry < $MAX_RETRY) {
			print STDERR "Too many tries in retrieving data: $uri\n";
			$retry=0;
		}
	}
	unless ($res) {
		print STDERR "Error in retrieving data: $uri\n";
	}
	$res;
}

sub retrieve_parsed_from_api {
	my ($uri)=@_;
	my $retry=0;
	my $json='';
	my $res='';
	while (1) {
		$res=retrieve_raw_from_api($uri);
		$retry++;
		eval {
			$json=decode_json($res);
		};
		if ($@) {
			sleep($TIME_OUT);
		} else {
			last;
		}
		unless ($retry < $MAX_RETRY) {
			print STDERR "Too many tries in parsing data: $uri\n";
			$retry=0;
		}
	}
	unless ($json) {
		print STDERR "Error in parsing data: $uri\n";

	}
	$json;
}

POE::Session->create(
	inline_states => {
		_start           => \&on_start,
		next_task		 => \&on_start,
		got_child_stdout => \&on_child_stdout,
		got_child_stderr => \&on_child_stderr,
		got_child_close  => \&on_child_close,
		got_child_signal => \&on_child_signal,
	},
);
POE::Kernel->run();

1;
