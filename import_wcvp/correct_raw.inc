<?php

/////////////////////////////////////////////////////
// Corrects source-specific errors
// Set $sql to "" if no corrections
/////////////////////////////////////////////////////

echo "Correcting source-specific errors...";
$sql="
UPDATE $tbl_names_raw
SET 
taxon_name='Hieracium doronicifolium subsp. arpillense',
`rank`='Subspecies'
WHERE taxon_name='Hieracium doronicifolium subso, arpillense'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>