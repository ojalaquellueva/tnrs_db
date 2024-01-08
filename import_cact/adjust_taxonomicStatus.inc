<?php

/////////////////////////////////////////////////////
// Adjust taxonomicStatus after populating 
// parentNameID to reflect status of sub-familial
// pseudo-taxa which are actually name groupings
// according to taxonomic status (go figure...)
/////////////////////////////////////////////////////

echo "Adjusting taxonomicStatus:\r\n";

echo "  '__Cactaceae_3_names_of_uncertain_application': Accepted --> Unresolved...";
$sql="
UPDATE $tbl_names_raw
SET taxonomicStatus='Unresolved'
WHERE treeIndex LIKE 'root#11499#%'
AND taxonomicStatus='Accepted'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

/* LEAVE THESE AS IS. ALL ARE ALREADY MARKED ACCEPTED OR SYNONYM
echo "  '__Cactaceae_4_unplaced_taxa': Accepted --> Unresolved...";
$sql="
UPDATE $tbl_names_raw
SET taxonomicStatus='Unresolved'
WHERE treeIndex LIKE 'root#28697#%'
AND taxonomicStatus='Accepted'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;
*/

echo "  '__Cactaceae_5_unresolved_names': Accepted --> Unresolved...";
$sql="
UPDATE $tbl_names_raw
SET taxonomicStatus='Unresolved'
WHERE treeIndex LIKE 'root#11495#%'
AND taxonomicStatus='Accepted'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


echo "  '__Cactaceae_6_excluded_names': (all) --> Invalid...";
$sql="
UPDATE $tbl_names_raw
SET taxonomicStatus='Invalid'
WHERE treeIndex LIKE 'root#28799#%'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


?>