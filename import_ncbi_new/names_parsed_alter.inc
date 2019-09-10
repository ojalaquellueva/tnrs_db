<?php
// Performs integrity checks, adds columns and indexes table `names_parsed`

// Check name field is unique
Echo "Checking integrity of table $names_parsed:\r\n";
Echo "  Checking duplication in name field...";
$sql="
	select count(*) as total
       	from 
	(
	select ScientificName_submitted, count(*) as tot
	from `$names_parsed`
	group by ScientificName_submitted
	having tot>1
	) as a;
";
$msg_error="Failed query:\r\n$sql\r\n";
if (($dupes=sql_get_first_result($dbh, $sql,"total"))===false) {
	die($msg_error);
} elseif ($dupes>0) {
	// confirm that duplication is in name field only
	// if other columns contain duplicates then have multiple results for 
	// same name; quit and warn user
	echo "$dupes duplicates found\r\n";
	echo "  Checking different records for same name...";
	$sql="
		select count(*) as total
		from
		(
		  select distinct p.*
			from `$names_parsed` p join
			(
			select ScientificName_submitted, count(*) as tot
			from `$names_parsed`
			group by ScientificName_submitted
			having tot>1
			) as a
			on p.ScientificName_submitted=a.ScientificName_submitted
		) as b
		";
	$msg_error="Failed query:\r\n$sql\r\n";
	if (($unique_dupes=sql_get_first_result($dbh, $sql,"total"))===false) {
		die($msg_error);
	} elseif ($unique_dupes>$dupes) {
		$r=$unique_dupes-$dupes;
		echo "$r records found!\r\nWARNING: different results for same name in table `$names_parsed`!\r\n";
		//die();
		
		/////////////////////////////////////////////////////////////////
		// Some dirty pool to get this working: delete all names with 
		// >1 records where these are not all identical. 
		// In practice this works because such names in NCBI are junk names, none
		// are taxonomically-valid plant names
		// This is temporary; restore die (above) and remove everything from
		// here to the next ifelse once figure out how to deal with these
		// names before import
		/////////////////////////////////////////////////////////////////
		
		echo "  Removing names with multiple records that are not duplicates...";
		
		// Create table of with all fields except the submitted name smushed
		// into one field
		$sql="
			DROP TABLE IF EXISTS names_parsed_concat;
			CREATE TABLE names_parsed_concat
			select ScientificName_submitted, 
			CONCAT_WS(' ',
			IFNULL(Taxon_name,''),
			IFNULL(Canonical_name,''),
			IFNULL(Author_submitted,''),
			IFNULL(Family_submitted,''),
			IFNULL(Genus_submitted,''),
			IFNULL(SpecificEpithet_submitted,''),
			IFNULL(InfraspecificRank_submitted,''),
			IFNULL(Infraspecific1Epithet_submitted,''),
			IFNULL(Infraspecific2Rank_submitted,''),
			IFNULL(Infraspecific2Epithet_submitted,''),
			IFNULL(Annotation,''),
			IFNULL(Unmatched_terms,'')
			) AS ScientificName_parsed
			FROM `$names_parsed`;

			ALTER TABLE names_parsed_concat
			CHANGE COLUMN ScientificName_parsed ScientificName_parsed VARCHAR(500) DEFAULT NULL;

			ALTER TABLE names_parsed_concat
			ADD INDEX (ScientificName_submitted),
			ADD INDEX (ScientificName_parsed);

			ALTER TABLE names_parsed_concat
			ADD COLUMN is_dupe INT(1) DEFAULT 0,
			ADD COLUMN distinct_records INT(10) DEFAULT 1,
			ADD INDEX (is_dupe),
			ADD INDEX (distinct_records);
		";
		sql_execute_multiple($dbh, $sql);
		
		// Now index submitted names with >1 record,
		// and submitted names with >1 record which are not all identical
		$sql="
			UPDATE names_parsed_concat a 
			JOIN
			(
			SELECT ScientificName_submitted, COUNT(ScientificName_parsed) AS records
			FROM names_parsed_concat
			GROUP BY ScientificName_submitted
			HAVING records>1
			) AS b
			ON a.ScientificName_submitted=b.ScientificName_submitted
			SET a.is_dupe=1;

			UPDATE names_parsed_concat a 
			JOIN
			(
			SELECT ScientificName_submitted, 
			COUNT(DISTINCT ScientificName_parsed) AS distinct_records
			FROM names_parsed_concat
			WHERE is_dupe=1
			GROUP BY ScientificName_submitted
			HAVING distinct_records>1
			) AS b
			ON a.ScientificName_submitted=b.ScientificName_submitted
			SET a.distinct_records=b.distinct_records
			WHERE a.is_dupe=1;
		";
		sql_execute_multiple($dbh, $sql);
		
		// Now delete submitted names with >1 record which are not all identical
		$sql="
			UPDATE names_parsed_concat a JOIN `$names_parsed` b
			ON a.ScientificName_submitted=b.ScientificName_submitted
			SET b.Taxon_name='delete'
			WHERE b.distinct_records>1;
			
			DELETE FROM `$names_parsed`
			WHERE Taxon_name='delete';
			
			DROP TABLE IF EXISTS names_parsed_concat;
		";
		sql_execute_multiple($dbh, $sql);		
		echo "done\r\n";

		/////////////////////////////////////////////////////////////////
		// End dirty pool (delete when issue is fixed
		/////////////////////////////////////////////////////////////////

	} else {
		// Purge redundant records
		
		echo "0 records found\r\n";
		Echo "  Removing duplicate records...";

		// Make temporary table of unique values of duplicated records
		$sql="drop table if exists dupes_temp;";
		$msg_error="failed to drop previous table dupes_temp!\r\n";
		if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));
		$sql="
			create table dupes_temp
			select *
			from
			(
			  select distinct p.*
				from `$names_parsed` p join
				(
				select ScientificName_submitted, count(*) as tot
				from `$names_parsed`
				group by ScientificName_submitted
				having tot>1
				) as a
				on p.ScientificName_submitted=a.ScientificName_submitted
			) as b
		";
		$msg_error="failed to create table`dupes_temp`!\r\n";
		if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));

		// Delete duplicated records from main table
		$sql="
			delete p.*
			from `$names_parsed` p join dupes_temp d
			on p.ScientificName_submitted=d.ScientificName_submitted
		";
		$msg_error="failed to delete duplicate records from table`$names_parsed`!\r\n";
		if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));

		// Re-add distinct versions of duplicated records
		$sql="insert into `$names_parsed` select * from dupes_temp;";
		$msg_error="failed to insert distinct records into table`$names_parsed`!\r\n";
		if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));

		// clean up
		$sql="drop table if exists dupes_temp;";
		$msg_error="failed to drop temporary table dupes_temp!\r\n";
		if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));		
	}
} else {
	echo $msg_success;
}

// Add new columns
// rank group distinguishes genus and below, above genus and unranked
echo "Adding columns to table $names_parsed...";
$sql="
	ALTER TABLE `$names_parsed`
	ADD COLUMN is_parse_error INTEGER NOT NULL DEFAULT 0,
	ADD COLUMN nameMinusAuthor VARCHAR(255) DEFAULT NULL,
	ADD COLUMN rankGroup VARCHAR(25) DEFAULT NULL,
	ADD COLUMN division VARCHAR(25) DEFAULT NULL,
	ADD COLUMN accepted_tax_id INTEGER DEFAULT NULL
";
$msg_error="failed to add columns to table `$names_parsed`!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

echo "Indexing table $names_parsed...";
// Remove current index
$sql="
	ALTER TABLE `$names_parsed`
	DROP INDEX `".$names_parsed."_ScientificName_submitted`;
";
$msg_error="failed to drop index `".$names_parsed."_ScientificName_submitted` in table `$names_parsed`!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));

// Add primary key
$sql="
	ALTER TABLE `$names_parsed`
	ADD PRIMARY KEY (ScientificName_submitted);
";
$msg_error="failed to add primary key to table `$names_parsed`!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));


?>
