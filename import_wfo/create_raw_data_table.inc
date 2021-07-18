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
`taxonID` VARCHAR(250) NOT NULL,
`scientificNameID` VARCHAR(250) DEFAULT NULL,
`scientificName` VARCHAR(250) DEFAULT NULL,
`taxonRank` VARCHAR(50) DEFAULT NULL,
`parentNameUsageID` VARCHAR(250) DEFAULT NULL,
`scientificNameAuthorship` VARCHAR(250) DEFAULT NULL,
`family` VARCHAR(50) DEFAULT NULL,
`genus` VARCHAR(100) DEFAULT NULL,
`specificEpithet`  VARCHAR(100) DEFAULT NULL,
`infraspecificEpithet` VARCHAR(100) DEFAULT NULL,
`verbatimTaxonRank` VARCHAR(50) DEFAULT NULL,
`nomenclaturalStatus` VARCHAR(50) DEFAULT NULL,
`namePublishedIn` VARCHAR(500) DEFAULT NULL,
`taxonomicStatus` VARCHAR(50) DEFAULT NULL,
`acceptedNameUsageID` VARCHAR(250) DEFAULT NULL,
`nameAccordingToID` VARCHAR(250) DEFAULT NULL,
`created` VARCHAR(50) DEFAULT NULL,
`modified` VARCHAR(50) DEFAULT NULL,
`references` VARCHAR(250) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>