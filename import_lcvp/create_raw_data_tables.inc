<?php

///////////////////////////////////////////////////////////////////////
// Purpose:
// Create mysql tables identical in structure to 
// raw taxonomic file
///////////////////////////////////////////////////////////////////////

// Create raw data table
echo "Creating table `$tbl_names_raw`...";

$msg_error="failed to drop previous table!";
$sql="DROP TABLE IF EXISTS `$tbl_names_raw`;";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));

$msg_error="failed to create table!\r\n";
$sql="
CREATE TABLE `$tbl_names_raw` (
inputTaxon VARCHAR(250) DEFAULT NULL,
status VARCHAR(250) DEFAULT NULL,
plComparison VARCHAR(250) DEFAULT NULL,
plAlternative VARCHAR(250) DEFAULT NULL,
outputTaxon VARCHAR(250) DEFAULT NULL,
family VARCHAR(250) DEFAULT NULL,
`order` VARCHAR(250) DEFAULT NULL,
INDEX (inputTaxon),
INDEX (outputTaxon),
INDEX (status),
INDEX (plComparison)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Create DwC format data table
echo "Creating table `$tbl_names_raw_dwc`...";

$msg_error="failed to drop previous table!";
$sql="DROP TABLE IF EXISTS `$tbl_names_raw_dwc`;";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));

$msg_error="failed to create table!\r\n";
$sql="
CREATE TABLE `$tbl_names_raw_dwc` (
nameID_char VARCHAR(250) DEFAULT NULL,
parentNameID_char VARCHAR(250) DEFAULT NULL,
rank VARCHAR(25) DEFAULT NULL,
family VARCHAR(50) DEFAULT NULL,
scientificName VARCHAR(250) DEFAULT NULL,
scientificNameAuthorship VARCHAR(150) DEFAULT NULL,
genusHybridMarker VARCHAR(25) DEFAULT NULL,
genus VARCHAR(50) DEFAULT NULL,
speciesHybridMarker VARCHAR(25) DEFAULT NULL,
specificEpithet VARCHAR(100) DEFAULT NULL,
infraspecificRank VARCHAR(25) DEFAULT NULL,
infraspecificEpithet VARCHAR(100) DEFAULT NULL,
infraspecificRank2 VARCHAR(25) DEFAULT NULL,
infraspecificEpithet2 VARCHAR(100) DEFAULT NULL,
taxonomicStatus VARCHAR(25) DEFAULT NULL,
acceptedNameID_char VARCHAR(250) DEFAULT NULL,
taxonUri VARCHAR(500) DEFAULT NULL,
lsid VARCHAR(500) DEFAULT NULL,
INDEX (nameID_char),
INDEX (parentNameID_char),
INDEX (rank),
INDEX (family),
INDEX (scientificName),
INDEX (genus),
INDEX (specificEpithet),
INDEX (infraspecificRank),
INDEX (infraspecificEpithet),
INDEX (infraspecificRank2),
INDEX (infraspecificEpithet2),
INDEX (taxonomicStatus),
INDEX (acceptedNameID_char)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));
	
?>

