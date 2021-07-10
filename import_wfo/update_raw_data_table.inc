<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Updates integer acceptedNameID and parentNameID 
// in raw names table, and standardize ranks
/////////////////////////////////////////////////////////////////

echo "Populating recursive foreign keys:\r\n";

echo "  Column `acceptedNameID`...";
$sql="
	UPDATE `$tbl_names_raw` syn JOIN  `$tbl_names_raw` acc
	ON syn.acceptedNameID_char=acc.nameID_char
	SET syn.acceptedNameID=acc.nameID
	WHERE syn.acceptedNameID_char<>syn.nameID_char;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Column `parentNameID`...";
$sql="
	UPDATE `$tbl_names_raw` child JOIN  `$tbl_names_raw` parent
	ON child.parentNameID_char=parent.nameID_char
	SET child.parentNameID=parent.nameID;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Standardizing rank names:\r\n";

echo "  Setting lower case...";
$sql="
UPDATE `$tbl_names_raw` 
SET rank=LOWER(rank)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Standardizing names...";
$sql="
UPDATE `$tbl_names_raw` 
SET rank=
CASE
WHEN rank='sp.' THEN 'species'
WHEN rank='subsp.' OR rank='subsp' THEN 'subspecies'
WHEN rank='var.' OR rank='var' THEN 'variety'
WHEN rank='f.' OR rank='form' THEN 'forma'
WHEN rank='subform' THEN 'subforma'
ELSE rank
END
;	
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Standardizing rank indicators:\r\n";

echo "  Column `infraspecificRank`...";
$sql="
-- Atomic rank indicator
-- Rank indicators for taxa above rank of subspecies set to NULL
UPDATE `$tbl_names_raw` 
SET infraspecificRank=
CASE
WHEN infraspecificRank='sect.' THEN NULL
WHEN infraspecificRank='subg.' THEN NULL
WHEN infraspecificRank='sp.' THEN NULL
WHEN infraspecificRank='var' THEN 'var.'
WHEN infraspecificRank='f.' THEN 'fo.'
WHEN infraspecificRank='subf.' THEN 'subfo.'
WHEN infraspecificRank='cultivar.' THEN 'cv.'
ELSE infraspecificRank
END
;	
-- Next one catches special cases such as species 'Orobanche mutelii f.'
UPDATE `$tbl_names_raw` 
SET infraspecificRank=NULL
WHERE rank IN (
'family','genus','nothospecies','order','phylum','section','species','subgenus'
)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// IMPORTANT!
// All infraspecific rank indicators standardized in the previous 
// step MUST be standardized here as well
// ALSO: Recommend searching for all distinct tokens containing 
// period ('.') in case other abbreviations not listed in column
// infraspecificRank are embedded in full scientific names 
echo "  Rank indicators in scientific names...";
$sql="
UPDATE `$tbl_names_raw`
SET scientificName=REPLACE(scientificName,' var ',' fo. ')
WHERE scientificName LIKE '% var %'
;
UPDATE `$tbl_names_raw`
SET scientificName=REPLACE(scientificName,' f. ',' fo. ')
WHERE scientificName LIKE '% f. %'
;
UPDATE `$tbl_names_raw`
SET scientificName=REPLACE(scientificName,' subf. ',' subfo. ')
WHERE scientificName LIKE '% subf. %'
;
UPDATE `$tbl_names_raw`
SET scientificName=REPLACE(scientificName,' cultivar. ',' cv. ')
WHERE scientificName LIKE '% cultivar. %'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>