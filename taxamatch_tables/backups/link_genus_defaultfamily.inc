<?php

// Links genus to default family by populating DEFAULT_FAMILY_ID column
// Core db field name `$fld_default_family` is set in file params.inc

/*
// For testing only
$msg_error = "Failed to clear previous family values!";
$sql = "UPDATE `$tbl_gen` SET DEFAULT_FAMILY_ID=NULL, DEFAULT_FAMILY=NULL;
	";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));
 */

// Populate DEFAULT_FAMILY_ID, DEFAULT_FAMILY for genera linked to families 
// having exactly 1 entry in table `name` (i.e., no homonyms)
// Families with >1 entry are retrieved using the slower left/right index method below
// Families with 0 entries (value in `defaultFamily` field in `name` table does not 
// have its own entry as `scientificName`)
// are more complex, will require adding new family to core db; NOT YET IMPLEMENTED
echo "Populating DEFAULT_FAMILY_ID for genera linked to non-homonym families...";
$msg_error = "Failed to populate DEFAULT_FAMILY_ID for non-homonym families!";

$sql = "UPDATE `$tbl_gen` AS g INNER JOIN name AS g2 INNER JOIN (
	SELECT scientificName AS fam, count(nameID) as records
	FROM name
	WHERE nameRank='family'
	GROUP BY scientificName
	HAVING records=1
	) AS f
	INNER JOIN name AS f2
	ON g.GENUS_ID=g2.nameID AND g2.$fld_default_family=f.fam AND f.fam=f2.scientificName
	SET 
	g.DEFAULT_FAMILY_ID=f2.nameID, g.DEFAULT_FAMILY=f2.scientificName
	WHERE g2.nameRank='genus' AND f2.nameRank='family';
	";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Mop up remaining unlinked genera using left and right indices
// Slow, but thorough & safe
echo "Linking genera to families using left & right indices:\r\n";

// Get sourceID of default classification
$sql="SELECT sourceID FROM source WHERE isDefault=1";
$sourceID=sql_get_first_result($dbh, $sql,'sourceID');
If ($sourceID===false or $sourceID==NULL) die("failed retrieve 'sourceID' from table `source`");

// Update for default source
echo "  Updating DEFAULT_FAMILY_ID for names linked to default classification...";
$msg_error = "Failed!";
$sql="
	UPDATE `$tbl_gen` AS gen,
	(
		SELECT g.GENUS_ID, t.rightIndex, t.leftIndex
		FROM `$tbl_gen` g INNER JOIN (
			SELECT n.nameID, rightIndex, leftIndex
			FROM name AS n INNER JOIN classification as c
			ON n.nameID=c.nameID
			WHERE c.sourceID=$sourceID
		) AS t
		ON g.GENUS_ID=t.nameID
		WHERE g.DEFAULT_FAMILY_ID IS NULL 
	) AS g,
	(
		SELECT n.nameID AS familyID, n.scientificName as family, c.leftIndex, c.rightIndex
		FROM name AS n INNER JOIN classification AS c
		ON n.nameID=c.nameID
		WHERE c.sourceID=$sourceID AND n.nameRank='family'

	) AS f
	SET gen.DEFAULT_FAMILY_ID=f.familyID, gen.DEFAULT_FAMILY=f.family
	WHERE gen.GENUS_ID=g.GENUS_ID
	AND f.leftIndex < g.leftIndex AND f.rightIndex > g.rightIndex
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Update for remaining names
echo "  Updating DEFAULT_FAMILY_ID for remaining names...";
$msg_error = "Failed!";
$sql="
	UPDATE `$tbl_gen` AS gen,
	(
		SELECT g.GENUS_ID, t.rightIndex, t.leftIndex
		FROM `$tbl_gen` g INNER JOIN (
			SELECT n.nameID, rightIndex, leftIndex
			FROM name AS n INNER JOIN classification as c
			ON n.nameID=c.nameID
			WHERE c.sourceID<>$sourceID AND c.sourceID=n.originalSourceID
		) AS t
		ON g.GENUS_ID=t.nameID
		WHERE g.DEFAULT_FAMILY_ID IS NULL AND t.leftIndex IS NOT NULL and t.rightIndex IS NOT NULL
	) AS g,
	(
		SELECT n.nameID AS familyID, n.scientificName as family, c.leftIndex, c.rightIndex
		FROM name AS n INNER JOIN classification AS c
		ON n.nameID=c.nameID
		WHERE c.sourceID<>$sourceID AND c.sourceID=n.originalSourceID AND n.nameRank='family'

	) AS f
	SET gen.DEFAULT_FAMILY_ID=f.familyID, gen.DEFAULT_FAMILY=f.family
	WHERE gen.GENUS_ID=g.GENUS_ID
	AND f.leftIndex < g.leftIndex AND f.rightIndex > g.rightIndex
	AND gen.DEFAULT_FAMILY_ID IS NULL;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

?>
