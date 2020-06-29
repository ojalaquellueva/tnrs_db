<?php

///////////////////////////////////////////////////////////////////////
// Purpose:
// Create mysql tables identical in structure to 
// raw taxonomic file
///////////////////////////////////////////////////////////////////////

// Create the empty table
echo "Creating table `$tbl_names_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_names_raw`;
CREATE TABLE `$tbl_names_raw` (
t1id VARCHAR(250) DEFAULT NULL,
fullName VARCHAR(250) DEFAULT NULL,
rank VARCHAR(250) DEFAULT NULL,
genusHybridMarker VARCHAR(250) DEFAULT NULL,
genus VARCHAR(250) DEFAULT NULL,
speciesHybridMarker VARCHAR(250) DEFAULT NULL,
species VARCHAR(250) DEFAULT NULL,
infraspecificRank VARCHAR(250) DEFAULT NULL,
infraspecificEpithet VARCHAR(250) DEFAULT NULL,
basionymAuthors VARCHAR(250) DEFAULT NULL,
primaryAuthors VARCHAR(250) DEFAULT NULL,
publication VARCHAR(250) DEFAULT NULL,
collation VARCHAR(250) DEFAULT NULL,
page VARCHAR(250) DEFAULT NULL,
date VARCHAR(250) DEFAULT NULL,
basionymID VARCHAR(250) DEFAULT NULL,
taxonomicStatus VARCHAR(250) DEFAULT NULL,
acceptedNameID VARCHAR(250) DEFAULT NULL,
source VARCHAR(250) DEFAULT NULL,
originalID VARCHAR(250) DEFAULT NULL,
dateExported VARCHAR(250) DEFAULT NULL,
ipniID VARCHAR(250) DEFAULT NULL,
assignedFamilyText VARCHAR(250) DEFAULT NULL,
confidenceLevel VARCHAR(250) DEFAULT NULL,
majorGroup VARCHAR(250) DEFAULT NULL,
ccrStatus VARCHAR(250) DEFAULT NULL,
removedBasionymID VARCHAR(250) DEFAULT NULL,
tidyMask VARCHAR(250) DEFAULT NULL,
assignedParentNameId VARCHAR(250) DEFAULT NULL,
division VARCHAR(250) DEFAULT NULL,
ranknameAlt VARCHAR(250) DEFAULT NULL,
fullAuthor VARCHAR(250) DEFAULT NULL,
field0 VARCHAR(250) DEFAULT NULL,
field1 VARCHAR(250) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;
	
// Create empty sDwC table
$tbl_names_raw_dwc = $tbl_names_raw . "_dwc";
echo "Creating table `$tbl_names_raw_dwc`...";
$sql="
DROP TABLE IF EXISTS `$tbl_names_raw_dwc`;
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
lsid VARCHAR(500) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>