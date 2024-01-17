<?php

//////////////////////////////////////////////////////
// Load citation for this source from bibtex file in 
// source data directory
// Parameter $COLLABORATORS_DATA_DIR set in global params file
//////////////////////////////////////////////////////

echo "  Populating table `collaborators`:\r\n";

$datafile = "collaborators.csv";
$fileandpath = $COLLABORATORS_DATA_DIR . $datafile;
	
echo "    Checking for file '$datafile' in directory '$COLLABORATORS_DATA_DIR'...";

if (!file_exists($fileandpath)) {
	echo "WARNING: file `$datafile` not found!\r\n";
} else {
	echo "done\r\n";
	
	echo "    Creating temporary table `collaborator_raw`...";
	$sql="
	DROP TABLE IF EXISTS collaborator_raw;
	CREATE TABLE collaborator_raw LIKE collaborator;
	ALTER TABLE collaborator_raw DROP COLUMN collaboratorID;
	";
	$msg_error="ERROR: Failed to create table `collaborator_raw`!";
	if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));
	
	echo "    Importing collaborator metadata...";
	// Dummy DOS line endings ('\r') force loading as single row
	$sql="
	LOAD DATA LOCAL INFILE '$fileandpath' 
	INTO TABLE collaborator_raw
	FIELDS TERMINATED BY ','
	OPTIONALLY ENCLOSED BY '\"'
	LINES TERMINATED BY '\n'
	IGNORE 1 LINES
	;
	";
	$msg_error="ERROR: Failed to load collaborator metadata!";
	if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));
	
	echo "    Loading table...";
	$sql="
	INSERT INTO collaborator (
	collaboratorName,
	collaboratorNameFull,
	collaboratorUrl,
	description,
	logo_path
	)
	SELECT
	collaboratorName,
	collaboratorNameFull,
	collaboratorUrl,
	description,
	logo_path
	FROM collaborator_raw
	;
	DROP TABLE collaborator_raw;
	";
	$msg_error="ERROR: Failed to load table `collaborator`!";
	if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));
}

?>