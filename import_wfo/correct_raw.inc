<?php

/////////////////////////////////////////////////////
// Corrects source-specific errors
/////////////////////////////////////////////////////

echo "Correcting source-specific errors...";
$sql="
-- Bad entry, no children so deleting won't hurt
DELETE FROM $tbl_names_raw
WHERE scientificName='Hymenophyllum racib.'
;
-- Purge non-ascii character in 'Microtea subg.Â Schollera'
-- Only one record using wildcard search
UPDATE $tbl_names_raw
SET scientificName='Microtea subg. Schollera'
WHERE scientificName like 'Microtea subg.%Schollera'
;

UPDATE $tbl_names_raw
SET scientificName='Asplenicystopteris'
WHERE scientificName like '%Asplenicystopteris'
;

";
sql_execute_multiple($dbh, $sql);
echo $done;

?>