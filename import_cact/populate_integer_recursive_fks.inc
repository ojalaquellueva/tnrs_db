<?php

/////////////////////////////////////////////////////////////////
// Populate integer acceptedNameID and parentNameID 
/////////////////////////////////////////////////////////////////

echo "Populating recursive foreign keys:\r\n";

echo "  Column `acceptedNameID`...";
$sql="
UPDATE `$tbl_names_raw` syn JOIN  `$tbl_names_raw` acc
ON syn.acceptedNameID_char=acc.nameID_char
SET syn.acceptedNameID=acc.nameID
WHERE syn.acceptedNameID_char<>syn.nameID_char
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Column `parentNameID`...";
$sql="
UPDATE `$tbl_names_raw` child JOIN  `$tbl_names_raw` parent
ON child.parentNameID_char=parent.nameID_char
SET child.parentNameID=parent.nameID
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

