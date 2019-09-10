<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Updates integer acceptedNameID and parentNameID 
// in raw names table
/////////////////////////////////////////////////////////////////

echo "Updating acceptedNameID...";
$sql="
	UPDATE `$tbl_names_raw` syn JOIN  `$tbl_names_raw` acc
	ON syn.acceptedNameID_char=acc.nameID_char
	SET syn.acceptedNameID=acc.nameID
	WHERE syn.acceptedNameID_char<>syn.nameID_char;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

echo "Updating parentNameID...";
$sql="
	UPDATE `$tbl_names_raw` child JOIN  `$tbl_names_raw` parent
	ON child.parentNameID_char=parent.nameID_char
	SET child.parentNameID=parent.nameID;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

echo "Standardizing ranks...";
$sql="
-- rank names
UPDATE `$tbl_names_raw` 
SET rank=
CASE
WHEN infraspecificRank='var.' THEN 'variety'
WHEN infraspecificRank='f.' THEN 'forma'
WHEN infraspecificRank='subsp.' THEN 'subspecies'
ELSE rank
END
;	

-- rank indicators
UPDATE `$tbl_names_raw` 
SET infraspecificRank='fo.'
WHERE infraspecificRank='f.'
;

-- Important to set rank indicator to empty 
-- string when not known
UPDATE `$tbl_names_raw` 
SET infraspecificRank=''
WHERE rank='infraspecies'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Adding higher taxon names to column scientificName...";
$sql="
-- family + taxonomic status
UPDATE `$tbl_names_raw` 
SET scientificName=family,
taxonomicStatus='Accepted'
WHERE rank='family'
;	

-- genus
UPDATE `$tbl_names_raw` 
SET scientificName=genus
WHERE rank='genus'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Adding missing values of family...";
$sql="
UPDATE `$tbl_names_raw` 
SET family='Fabaceae'
WHERE family IS NULL
;	
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Inferring genus taxonomic status...";
// The reasoning here is that one or more child species
// belonging to the same family+genus are explicity flagged
// as "Accepted", the the genus must be accepted as well
$sql="
UPDATE `$tbl_names_raw` g JOIN `$tbl_names_raw` s
ON g.genus=s.genus AND g.family=s.family
SET g.taxonomicStatus='Accepted'
WHERE g.rank='genus' AND s.rank='species'   
AND s.taxonomicStatus='Accepted'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;	

?>