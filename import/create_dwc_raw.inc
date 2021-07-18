<?php

///////////////////////////////////////////////////////////////////////
// Purpose:
// Create general Simplified DwC raw data table
///////////////////////////////////////////////////////////////////////
	
// Create empty Simplified DwC table
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
