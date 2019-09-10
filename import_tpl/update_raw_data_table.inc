<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Updates integer acceptedNameID and parentNameID 
// in raw names table, and standardize ranks
/////////////////////////////////////////////////////////////////

echo "Updating acceptedNameID...";
$sql="
	UPDATE `$tbl_names_raw` syn JOIN  `$tbl_names_raw` acc
	ON syn.acceptedNameID_char=acc.nameID_char
	SET syn.acceptedNameID=acc.nameID
	WHERE syn.acceptedNameID_char<>syn.nameID_char;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Updating parentNameID...";
$sql="
	UPDATE `$tbl_names_raw` child JOIN  `$tbl_names_raw` parent
	ON child.parentNameID_char=parent.nameID_char
	SET child.parentNameID=parent.nameID;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Standardizing rank names...";
$sql="
UPDATE `$tbl_names_raw` 
SET rank=
CASE
WHEN rank='sp.' THEN 'species'
WHEN rank='var.' OR rank='var' THEN 'variety'
WHEN rank='f.' THEN 'forma'
WHEN rank='subsp.' OR rank='subsp' THEN 'subspecies'
ELSE rank
END
;	
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Standardizing rank indicators...";
$sql="
-- Atomic rank indicator
UPDATE `$tbl_names_raw` 
SET infraspecificRank=
CASE
WHEN infraspecificRank='sp.' THEN NULL
WHEN infraspecificRank='var' THEN 'var.'
WHEN infraspecificRank='f.' THEN 'fo.'
ELSE infraspecificRank
END
;	
-- Rank indicator in full name
UPDATE `$tbl_names_raw`
SET scientificName=REPLACE(scientificName,' var ',' var. ')
WHERE scientificName LIKE ' var '
;
UPDATE `$tbl_names_raw`
SET scientificName=REPLACE(scientificName,' f. ',' fo. ')
WHERE scientificName LIKE ' f. '
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


?>
