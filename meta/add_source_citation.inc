<?php

//////////////////////////////////////////////////////
// Load citation for this source from bibtex file in 
// source data directory
// Parameter $TNRS_DATA_DIR set in global params file
//////////////////////////////////////////////////////

echo "  Populating citations in table `meta`:\r\n";

// 
$fbib_array=array(
	"TNRS_publication",
	"TNRS_website"
);

foreach ($fbib_array as $fbib) {
	$bibfile = $fbib . ".bib.no-line-endings";
	$fileandpath = $TNRS_DATA_DIR . $bibfile;
	
	if ($fbib="TNRS_publication") {
		$cit_fld="publication";
	} else if ($fbib="TNRS_website") {
		$cit_fld="citation";
	} 
		
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
		
		echo "    Adding citation...";
		// Note use of dummy DOS line endings ('\r') to force loading as single row
		$sql="
		UPDATE meta m, citation_raw c
		SET m.".$cit_fld."=c.citation
		;
		DROP TABLE citation_raw;
		";
		$msg_error="ERROR: Failed to update field $cit_fld in table meta!";
		if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));
	}
}

?>