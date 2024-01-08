<?php

/////////////////////////////////////////////////////
// Extract parentNameID from field treeIndex
/////////////////////////////////////////////////////

echo "Populating parentNameID based on treeIndex:\r\n";

/////////////////////////////
// Modify treeIndex 
/////////////////////////////

echo "  Modifying treeIndex:\r\n";

echo "    Trimming leading/trailing whitespace, if any...";
$sql="
UPDATE $tbl_names_raw
SET treeIndex=TRIM(treeIndex)
WHERE treeIndex IS NOT NULL
;
 ";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Renaming base index to 'root'...";
$sql="
UPDATE $tbl_names_raw
SET treeIndex=REPLACE(treeIndex, '#t42#33819#33820#33837#', 'root#')
;
 ";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Validating...";
$sql="
SELECT COUNT(*) AS rootmissing
FROM cact_raw 
WHERE LEFT(treeIndex,5)<>'root#'
;
";
$rootmissing=sql_get_first_result($dbh, $sql,'rootmissing');
if ($rootmissing>0) {
	die('FAIL: treeIndex basename not set to root for one or more names!\r\n');
} else {
	echo "passed\r\n";
}

echo "    Removing trailing delimiter...";
$sql="
UPDATE $tbl_names_raw
SET treeIndex=LEFT(treeIndex, LENGTH(treeIndex)-1)
WHERE RIGHT(treeIndex,1)='#'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


/////////////////////////////
// Prepare parentTreeIndex
/////////////////////////////

echo "  Populating parentTreeIndex...";
$sql="
UPDATE $tbl_names_raw
SET parentTreeIndex=REPLACE(treeIndex, strSplit(
treeIndex,'#',
LENGTH(treeIndex) - LENGTH(REPLACE(treeIndex, '#', '')) + 1
),''
)
;
-- Remove trailing delimiter, if any
UPDATE $tbl_names_raw
SET parentTreeIndex=LEFT(parentTreeIndex, LENGTH(parentTreeIndex)-1)
WHERE RIGHT(parentTreeIndex,1)='#'
;
-- Set empty string to NULL
UPDATE $tbl_names_raw
SET parentTreeIndex=NULL
WHERE TRIM(parentTreeIndex)=''
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Validating...";
$sql="
SELECT COUNT(*) AS parentmissing
FROM $tbl_names_raw 
WHERE parentTreeIndex IS NULL 
AND treeIndex<>'root'
;
";
$parentmissing=sql_get_first_result($dbh, $sql,'parentmissing');
if ($parentmissing>0) {
	die('FAIL: treeIndex basename not set to root for one or more names!\r\n');
} else {
	echo "passed\r\n";
}



echo "  Populating parentNameID:\r\n";

echo "    Creating indexes...";
$sql="
CREATE INDEX cact_raw_treeIndex_idx ON cact_raw (treeIndex);
CREATE INDEX cact_raw_parentTreeIndex_idx ON cact_raw (parentTreeIndex);
CREATE INDEX cact_raw_taxonomicStatus_idx ON cact_raw (taxonomicStatus);
";
sql_execute_multiple($dbh, $sql);
echo $done;

/////////////////////////////
// Synonyms
/////////////////////////////

echo "    Synonyms: setting parentNameID to accNameID...";
$sql="
UPDATE $tbl_names_raw
SET parentNameID=accNameID
WHERE taxonomicStatus='Synonym'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Validating...";
$sql="
SELECT COUNT(*) AS parentmissing
FROM $tbl_names_raw
WHERE parentNameID IS NULL AND taxonomicStatus='Synonym'
;
";
$parentmissing=sql_get_first_result($dbh, $sql,'parentmissing');
if ($parentmissing>0) {
	die('FAIL: one or more synonym names not assigned value of parentNameID!\r\n');
} else {
	echo "passed\r\n";
}

/////////////////////////////
// Accepted names
/////////////////////////////

echo "    Accepted names: setting parentNameID to nameID of treeIndex parent...";
$sql="
UPDATE $tbl_names_raw child JOIN $tbl_names_raw parent
ON child.parentTreeIndex=parent.treeIndex
SET child.parentNameID=parent.nameID
WHERE child.taxonomicStatus='Accepted' AND parent.taxonomicStatus='Accepted'
AND child.parentNameID IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


echo "    Validating...";
$sql="
SELECT COUNT(*) AS parentmissing
FROM $tbl_names_raw 
WHERE parentNameID IS NULL 
AND taxonomicStatus='Accepted'
AND treeIndex<>'root'
;
";
$parentmissing=sql_get_first_result($dbh, $sql,'parentmissing');
if ($parentmissing>0) {
	die('FAIL: one or more accepted names not assigned value of parentNameID!\r\n');
} else {
	echo "passed\r\n";
}

?>