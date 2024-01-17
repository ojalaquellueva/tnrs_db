<?php

//////////////////////////////////////////////////////
// Load citation for this source from bibtex file in 
// source data directory
// Parameter $fileandpath set in local params file
//////////////////////////////////////////////////////

echo "  Populating citation in table `source` for sourceName='$src':\r\n";

$bibfile = $src . ".bib.no-line-endings";
$fileandpath = $filepath . $bibfile;

echo "    Checking for file '$bibfile' in directory '$filepath'...";

if (!file_exists($fileandpath)) {
	echo "WARNING: file `$bibfile` not found!\r\n";
} else {
	echo "done\r\n";
	echo "    Creating temporary table `citation_raw`...";
	$sql="
	DROP TABLE IF EXISTS citation_raw;
	CREATE TABLE citation_raw (
	citation TEXT DEFAULT NULL
	) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
	";
	$msg_error="ERROR: Failed to create table `citation_raw`!";
	if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));
	
	echo "    Importing bibtex citation...";
	// Dummy DOS line endings ('\r') force loading as single row
	$sql="
	LOAD DATA LOCAL INFILE '$fileandpath' 
	INTO TABLE citation_raw 
	LINES TERMINATED BY '\r'
	;
	";
	$msg_error="ERROR: Failed to load citation data!";
	if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));
	
	echo "    Updating citation in table `source`...";
	// Note use of dummy DOS line endings ('\r') to force loading as single row
	$sql="
	UPDATE source s, citation_raw c
	SET s.citation=c.citation
	WHERE s.sourceName='".$src."'
	;
	DROP TABLE citation_raw;
	";
	$msg_error="ERROR: Failed to update table source!";
	if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));
}

?>