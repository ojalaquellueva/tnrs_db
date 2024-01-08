<?php

/////////////////////////////////////////////////////
// Remove pseudotaxa which are actually grouping
// of taxa sharing similar taxonomic status. Reset
// parent to root (=Cactaceae)
/////////////////////////////////////////////////////

echo "Removing pseudotaxa:\r\n";

echo "  Retrieving nameID of root ('Cactaceae')...";
$sql="
SELECT nameID AS rootNameID
FROM $tbl_names_raw 
WHERE treeIndex='root'
;
";
$rootNameID=sql_get_first_result($dbh, $sql,'rootNameID');
if ($rootNameID===false || is_null($rootNameID)) {
	die('ERROR: failed to retrieve nameID of root taxon!\r\n');
} else {
	echo $done;
}

// Check that all expected pseudotaxa are present and only one of each
// Will throw error if indexes or pseudotaxa have changed, in which case
// this script will need to be modified
echo "  Confirming counts, names and IDs of pseudotaxa...";
$sql="
SELECT SUM(count_correct) AS all_counts_correct FROM (
SELECT 1=(SELECT COUNT(*) FROM $tbl_names_raw WHERE treeIndex='root#33839') AS count_correct
UNION ALL
SELECT 1=(SELECT COUNT(*) FROM $tbl_names_raw WHERE treeIndex='root#23243') AS count_correct
UNION ALL
SELECT 1=(SELECT COUNT(*) FROM $tbl_names_raw WHERE treeIndex='root#11499') AS count_correct
UNION ALL
SELECT 1=(SELECT COUNT(*) FROM $tbl_names_raw WHERE treeIndex='root#28697') AS count_correct
UNION ALL
SELECT 1=(SELECT COUNT(*) FROM $tbl_names_raw WHERE treeIndex='root#11495') AS count_correct
UNION ALL
SELECT 1=(SELECT COUNT(*) FROM $tbl_names_raw WHERE treeIndex='root#28799') AS count_correct
) a
;
";
$all_counts_correct=sql_get_first_result($dbh, $sql,'all_counts_correct');
if ( !$all_counts_correct==1 ) {
	die('ERROR: pseudotaxa counts incorrect, please check script!\r\n');
} else {
	echo $done;
}

echo "  Deleting pseudotaxa...";
$sql="
DELETE FROM $tbl_names_raw
WHERE treeIndex IN (
'root#33839', 
'root#23243', 
'root#11499', 
'root#28697', 
'root#11495', 
'root#28799'
)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Updating treeIndex...";
$sql="
UPDATE $tbl_names_raw
SET treeIndex=
CASE
WHEN treeIndex LIKE 'root#33839%' THEN REPLACE(treeIndex, 'root#33839', 'root')
WHEN treeIndex LIKE 'root#23243%' THEN REPLACE(treeIndex, 'root#23243', 'root')
WHEN treeIndex LIKE 'root#11499%' THEN REPLACE(treeIndex, 'root#11499', 'root')
WHEN treeIndex LIKE 'root#28697%' THEN REPLACE(treeIndex, 'root#28697', 'root')
WHEN treeIndex LIKE 'root#11495%' THEN REPLACE(treeIndex, 'root#11495', 'root')
WHEN treeIndex LIKE 'root#28799%' THEN REPLACE(treeIndex, 'root#28799', 'root')
ELSE treeIndex
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Updating parentTreeIndex...";
$sql="
UPDATE $tbl_names_raw
SET parentTreeIndex='root'
WHERE parentTreeIndex IN (
'root#33839', 
'root#23243', 
'root#11499', 
'root#28697', 
'root#11495', 
'root#28799'
)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Updating parentNameID...";
$sql="
UPDATE $tbl_names_raw
SET parentNameID='$rootNameID'
WHERE parentTreeIndex='root'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>