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
if (sql_execute($sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

echo "Updating parentNameID...";
$sql="
	UPDATE `$tbl_names_raw` child JOIN  `$tbl_names_raw` parent
	ON child.parentNameID_char=parent.nameID_char
	SET child.parentNameID=parent.nameID;
";
if (sql_execute($sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

// Extract genera from column `genus` and add them to as separate 
// taxa. Only do this if you are sure genera are not already
// in the classification. This may be a bad idea if the 
// source database contains homonym genera.
if ($extract_genera) {
	echo "Extracting genera...";
	$sql="
		INSERT INTO `$tbl_names_raw` (
		family,
		scientificName,
		genus,
		rank,
		taxonomicStatus
		)
		SELECT DISTINCT
		NULL,
		genus,
		genus,
		'genus',
		'Accepted'
		FROM `$tbl_names_raw`
		WHERE genus IS NOT NULL;
	";
	if (sql_execute($sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));
	
	echo "Linking orphan species to genera...";
	$sql="
		UPDATE `$tbl_names_raw` s JOIN `$tbl_names_raw` g
		ON s.genus=g.scientificName
		SET s.parentNameID=g.nameID
		WHERE s.rank='species' 
			AND g.rank='genus' 
			AND (s.parentNameID IS NULL OR s.parentNameID=s.nameID) 
		;
	";
	if (sql_execute($sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));
}

// Extract family from the column "family" and add them to as 
// separate taxa
// Only do this if you are sure families are not already
// in the classification. May get weird results if taxa between
// the ranks of genus and family area included. This is also a 
// bad idea if the source database contains homonym families (unlikely)
if ($extract_families) {
	echo "Extracting families...";
	$sql="
		INSERT INTO `$tbl_names_raw` (
		family,
		scientificName,
		rank,
		taxonomicStatus
		)
		SELECT DISTINCT
		family,
		family,
		'family',
		'Accepted'
		FROM `$tbl_names_raw`
		WHERE family IS NOT NULL;
	";
	if (sql_execute($sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

	echo "Linking orphan genera to families...";
	$sql="
		UPDATE `$tbl_names_raw` g JOIN `$tbl_names_raw` f
		ON g.family=f.scientificName
		SET g.parentNameID=f.nameID
		WHERE g.rank='genus' 
			AND f.rank='family' 
			AND (g.parentNameID IS NULL OR g.parentNameID=g.nameID) ;
	";
	if (sql_execute($sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));
}

?>
