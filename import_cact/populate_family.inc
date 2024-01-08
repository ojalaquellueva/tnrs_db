<?php

/////////////////////////////////////////////////////
// Simple for this source: all Cactaceae
/////////////////////////////////////////////////////

echo "Populating family...";
$sql="
UPDATE $tbl_names_raw
SET family='Cactaceae'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>