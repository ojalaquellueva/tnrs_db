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
`kew_id` VARCHAR(100) NOT NULL,
`family` VARCHAR(100) DEFAULT NULL,
`genus` VARCHAR(100) DEFAULT NULL,
`species` VARCHAR(100) DEFAULT NULL,
`infraspecies` VARCHAR(100) DEFAULT NULL,
`taxon_name` VARCHAR(250) DEFAULT NULL,
`authors` VARCHAR(250) DEFAULT NULL,
`rank` VARCHAR(50) DEFAULT NULL,
`taxonomic_status` VARCHAR(100) DEFAULT NULL,
`accepted_kew_id` VARCHAR(100) DEFAULT NULL,
`accepted_name` VARCHAR(250) DEFAULT NULL,
`accepted_authors` VARCHAR(250) DEFAULT NULL,
`parent_kew_id` VARCHAR(100) DEFAULT NULL,
`parent_name` VARCHAR(250) DEFAULT NULL,
`parent_authors` VARCHAR(250) DEFAULT NULL,
`reviewed` VARCHAR(100) DEFAULT NULL,
`publication` VARCHAR(500) DEFAULT NULL,
`original_name_id` VARCHAR(100) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>