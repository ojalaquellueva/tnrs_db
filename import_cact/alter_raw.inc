<?php

/////////////////////////////////////////////////////
// Add colummns parentNameID & taxonomicStatus
/////////////////////////////////////////////////////

echo "Adding column parentNameID to table $tbl_names_raw...";
$sql="
ALTER TABLE $tbl_names_raw
ADD COLUMN parentNameID VARCHAR(250) DEFAULT NULL,
ADD COLUMN parentTreeIndex VARCHAR(250) DEFAULT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>