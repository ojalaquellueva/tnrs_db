<?php

/////////////////////////////////////////////////////
// Transfers contents of the verbatim raw table
// to a simplified darwin core table and renames
// tables. This allows the DwC table to processed
// by existing sDwC import scripts
/////////////////////////////////////////////////////

echo "Transferring raw data to Simplified Darwin Core...";

$msg_error="failed to create table!\r\n";
$sql="
INSERT INTO `$tbl_names_raw_dwc` (
nameID_char,
parentNameID_char,
rank,
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
`kew_id`,
`parent_kew_id`,
`rank`,
`family`,
`taxon_name`,
`authors`,
NULL,
`genus`,
NULL,
`species`,
NULL,
`infraspecies`,
NULL,
NULL,
`taxonomic_status`,
`accepted_kew_id`,
CONCAT('$base_url_species',IFNULL(`kew_id`,'')),
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