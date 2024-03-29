<?php

/////////////////////////////////////////////////////
// Transfers contents of the merged verbatim raw table
// to simplified darwin core raw names table.
/////////////////////////////////////////////////////

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
`nameID`,
`parentNameID`,
`rank`,
NULL,
`name`,
`author`,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
NULL,
`taxonomicStatus`,
`accNameID`,
NULL, -- updated later in make.url.inc
NULL
FROM $tbl_names_raw
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>