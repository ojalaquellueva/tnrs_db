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
`plant_name_id` VARCHAR(100) NOT NULL,
`ipni_id` VARCHAR(100) DEFAULT NULL,
`rank` VARCHAR(50) DEFAULT NULL,
`taxonomic_status` VARCHAR(100) DEFAULT NULL,
`family` VARCHAR(100) DEFAULT NULL,
`genus_hybrid` VARCHAR(5) DEFAULT NULL,
`genus` VARCHAR(100) DEFAULT NULL,
`species_hybrid` VARCHAR(5) DEFAULT NULL,
`species` VARCHAR(100) DEFAULT NULL,
`infraspecific_rank` VARCHAR(100) DEFAULT NULL,
`infraspecies` VARCHAR(100) DEFAULT NULL,
`parenthetical_author` VARCHAR(250) DEFAULT NULL,
`primary_author` VARCHAR(250) DEFAULT NULL,
`publication_author` VARCHAR(250) DEFAULT NULL,
`place_of_publication` VARCHAR(100) DEFAULT NULL,
`volume_and_page` VARCHAR(50) DEFAULT NULL,
`first_published` VARCHAR(50) DEFAULT NULL,
`nomenclatural_remarks` VARCHAR(500) DEFAULT NULL,
`geographic_area` VARCHAR(250) DEFAULT NULL,
`lifeform_description` VARCHAR(250) DEFAULT NULL,
`climate_description` VARCHAR(250) DEFAULT NULL,
`taxon_name` VARCHAR(250) DEFAULT NULL,
`taxon_authors` VARCHAR(250) DEFAULT NULL,
`accepted_plant_name_id` VARCHAR(100) DEFAULT NULL,
`basionym_plant_name_id` VARCHAR(100) DEFAULT NULL,
`replaced_synonym_author` VARCHAR(250) DEFAULT NULL,
`homotypic_synonym` VARCHAR(250) DEFAULT NULL,
`parent_plant_name_id` VARCHAR(100) DEFAULT NULL,
`powo_id` VARCHAR(100) DEFAULT NULL,
`hybrid_formula` VARCHAR(500) DEFAULT NULL,
`reviewed` VARCHAR(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>