<?php

/////////////////////////////////////////////////////
// Transfers contents of the verbatim raw table
// to a simplified darwin core table and renames
// tables. This allows the DwC table to processed
// by existing sDwC import scripts
/////////////////////////////////////////////////////

// Remove metadata rows from raw file
echo "Deleting non-data rows...";
$sql="
DELETE FROM $tbl_names_raw
WHERE rank IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Transferring raw data to Simplified Darwin Core...";

$msg_error="failed to create table!\r\n";
$sql="
INSERT INTO `$tbl_names_raw_dwc` (
nameID_char,
parentNameID_char,
`rank`,
family,
scientificName,
scientificNameAuthorship,
genusHybridMarker,
genus,
speciesHybridMarker,
specificEpithet,
infraspecificRank,
infraspecificEpithet,
infraspecificRank2,
infraspecificEpithet2,
taxonomicStatus,
acceptedNameID_char,
taxonUri,
lsid
)
SELECT
t1ID,
assignedParentNameID,
rank,
assignedFamilyText,
fullName,
TRIM(CONCAT(
IF(TRIM(basionymAuthors)='' OR basionymAuthors IS NULL,'',
CONCAT('(',TRIM(basionymAuthors),') ')
),
TRIM(IFNULL(primaryAuthors,''))
)),
genusHybridMarker,
genus,
speciesHybridMarker,
species,
infraspecificRank,
infraspecificEpithet,
NULL,
NULL,
taxonomicStatus,
acceptedNameID,
CASE
WHEN rank='family' THEN CONCAT('$base_url_gen_fam',majorGroup,'/',assignedFamilyText,'/')
WHEN rank='genus' AND assignedFamilyText IS NOT NULL THEN CONCAT('$base_url_gen_fam,majorGroup','/',assignedFamilyText,'/',genus,'/')
WHEN rank='genus' AND assignedFamilyText IS NULL THEN CONCAT('$base_url_general_search',genus)
WHEN rank IN ('species','variety','subspecies','forma') THEN  
CONCAT('$base_url_species',IFNULL(t1id,''))
ELSE NULL
END,
NULL
FROM $tbl_names_raw
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Renaming tables...";
$tbl_names_raw_verbatim = $tbl_names_raw . "_verbatim";
$sql="
RENAME TABLE $tbl_names_raw TO $tbl_names_raw_verbatim;
RENAME TABLE $tbl_names_raw_dwc TO $tbl_names_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>