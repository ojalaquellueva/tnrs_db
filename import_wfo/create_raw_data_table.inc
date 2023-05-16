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
`scientificNameID`  VARCHAR(250) DEFAULT NULL,
`localID`  VARCHAR(250) DEFAULT NULL,
`scientificName`  VARCHAR(250) DEFAULT NULL,
`taxonRank`  VARCHAR(50) DEFAULT NULL,
`parentNameUsageID`  VARCHAR(250) DEFAULT NULL,
`scientificNameAuthorship`  VARCHAR(250) DEFAULT NULL,
`family`  VARCHAR(50) DEFAULT NULL,
`subfamily`  VARCHAR(250) DEFAULT NULL,
`tribe`  VARCHAR(250) DEFAULT NULL,
`subtribe`  VARCHAR(250) DEFAULT NULL,
`genus`  VARCHAR(250) DEFAULT NULL,
`subgenus`  VARCHAR(250) DEFAULT NULL,
`specificEpithet`  VARCHAR(250) DEFAULT NULL,
`infraspecificEpithet`  VARCHAR(250) DEFAULT NULL,
`verbatimTaxonRank`  VARCHAR(50) DEFAULT NULL,
`nomenclaturalStatus`  VARCHAR(50) DEFAULT NULL,
`namePublishedIn`  VARCHAR(250) DEFAULT NULL,
`taxonomicStatus`  VARCHAR(250) DEFAULT NULL,
`acceptedNameUsageID`  VARCHAR(250) DEFAULT NULL,
`originalNameUsageID`  VARCHAR(250) DEFAULT NULL,
`nameAccordingToID`  VARCHAR(250) DEFAULT NULL,
`taxonRemarks`  VARCHAR(250) DEFAULT NULL,
`created`  VARCHAR(250) DEFAULT NULL,
`modified`  VARCHAR(250) DEFAULT NULL,
`references`  VARCHAR(250) DEFAULT NULL,
`source`  VARCHAR(250) DEFAULT NULL,
`majorGroup`  VARCHAR(250) DEFAULT NULL,
`tplId`  VARCHAR(250) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>