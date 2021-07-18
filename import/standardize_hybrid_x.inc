<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Changes hybrid x from "x" to plain ascii "x"
/////////////////////////////////////////////////////////////////

echo "Standardizing hybrid 'x'...";
$sql="
UPDATE `$tbl_names_raw` 
SET scientificName=REPLACE(scientificName, '×', 'x')
WHERE scientificName like '%×%' 
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>