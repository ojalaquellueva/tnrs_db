<?php

/////////////////////////////////////////////////////
// Corrects source-specific errors
/////////////////////////////////////////////////////

echo "Correcting source-specific errors:\r\n";

echo "  Removing concatenated author from scientificName...";
$sql="
-- Remove concatenated author from scientificName when present
UPDATE $tbl_names_raw
SET scientificName=TRIM(REPLACE(scientificName,TRIM(scientificNameAuthorship),''))
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Populating missing concatenated scientific names...";
$sql="
-- No idea how this couold possibly happen!
UPDATE $tbl_names_raw
SET scientificName=TRIM(CONCAT_WS(' ',
IFNULL(genericName,''),
IFNULL(specificEpithet,''),
IFNULL(verbatimTaxonRank,''),
IFNULL(infraspecificEpithet,'')
))
WHERE scientificName IS NULL OR TRIM(scientificName)=''
;
";
sql_execute_multiple($dbh, $sql);
echo $done;



?>