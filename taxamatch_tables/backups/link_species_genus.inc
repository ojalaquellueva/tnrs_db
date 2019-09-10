<?php

/////////////////////////////////////////////////////////////////////
// Purpose:
// Links species to genera by populating GENUS_ID column
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// Populate GENUS_ID with nameIDs of genera having exactly 
// 1 entry in table `name` (i.e., no homonyms). Genera with 
// >1 entry are retrieved using the slower left/right index 
// method below. Genera with 0 entries (value in `genus` field 
// in table `name`  does not have its own entry as `scientificName`)
// are more complex, will require adding new genus to core 
// db; NOT YET IMPLEMENTED
/////////////////////////////////////////////////////////////////////
echo "Populating genus nameID using `genus` field of species...";
$msg_error = "Failed to retrieve genus nameID using `genus` field!";
$sql = "
	UPDATE `splist` AS s INNER JOIN 
	(
		SELECT scientificName AS gen, count(nameID) as records
		FROM name
		WHERE nameRank='genus'
		GROUP BY scientificName
		HAVING records=1
	) AS g
	INNER JOIN name AS n
	ON s.GENUS_ORIG=g.gen AND g.gen=n.scientificName
	SET s.GENUS_ID=n.nameID
	WHERE n.nameRank='genus';
	";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Mop up remaining unlinked species using left and right indices
// Slow, but thorough & safe
echo "Linking species to genera using left and right indices:\r\n";

// Update for default source
echo "  Updating GENUS_ID for names linked to default classification...";
$msg_error = "Failed!";
$sql="
	UPDATE `splist` sp,
	(
		SELECT s.SPECIES_ID, s.GENUS_ID, t.rightIndex, t.leftIndex
		FROM `splist` s INNER JOIN (
			SELECT n.nameID, rightIndex, leftIndex
			FROM name AS n INNER JOIN classification as c
			ON n.nameID=c.nameID
			WHERE c.sourceID=$sourceID
			AND n.nameRank='species'
		) AS t
		ON s.SPECIES_ID=t.nameID
		WHERE s.GENUS_ID IS NULL
	) AS s, 
	(
		SELECT n.nameID AS genusID, c.leftIndex, c.rightIndex
		FROM name AS n INNER JOIN classification AS c
		ON n.nameID=c.nameID
		WHERE c.sourceID=$sourceID 
		AND n.nameRank='genus'
	) AS g
	SET sp.GENUS_ID=g.genusID
	WHERE sp.SPECIES_ID=s.SPECIES_ID 
	AND sp.GENUS_ID IS NULL
	AND g.leftIndex < s.leftIndex AND g.rightIndex > s.rightIndex
	;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Update for remaining names
echo "  Updating GENUS_ID for remaining names...";
$msg_error = "Failed!";
$sql="
	UPDATE `splist` sp,
	(
		SELECT s.SPECIES_ID, s.GENUS_ID, t.rightIndex, t.leftIndex
		FROM `splist` s INNER JOIN (
			SELECT n.nameID, rightIndex, leftIndex
			FROM name AS n INNER JOIN classification as c
			ON n.nameID=c.nameID
			WHERE c.sourceID<>$sourceID 
			AND c.sourceID=n.originalSourceID
			AND n.nameRank='species'
		) AS t
		ON s.SPECIES_ID=t.nameID
		WHERE s.GENUS_ID IS NULL
	) AS s, 
	(
		SELECT n.nameID AS genusID, c.leftIndex, c.rightIndex
		FROM name AS n INNER JOIN classification AS c
		ON n.nameID=c.nameID
		WHERE c.sourceID<>$sourceID AND c.sourceID=n.originalSourceID AND n.nameRank='genus'
	) AS g
	SET sp.GENUS_ID=g.genusID
	WHERE sp.SPECIES_ID=s.SPECIES_ID 
	AND g.leftIndex < s.leftIndex AND g.rightIndex > s.rightIndex
	AND sp.GENUS_ID IS NULL
	;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

if(exists_index($dbh, $tbl_sp,'splist_GENUS_ID')==false) {
	echo "  Restoring index...";
	$msg_error = "failed to restore index `splist`.`GENUS_ID`!";
	$sql = "ALTER TABLE `splist`
		ADD INDEX `splist_GENUS_ID`(`GENUS_ID`)
		;
	";
	if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));
}

?>
