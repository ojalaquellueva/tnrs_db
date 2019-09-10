<?php

////////////////////////////////////////////////
// Corrections specific to this source
////////////////////////////////////////////////

echo "Fixing source-specific errors...";
$sql="
-- Four records are corrupted due to frame shift
-- This takes them out
-- No time to troubleshoot the cause
-- but frame shift is definitely in original file
DELETE FROM $tbl_names_raw
WHERE family IS NULL OR family=''
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>