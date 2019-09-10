<?php
// Links trinomials to species by populating species_id column

echo "Setting species_id=NULL...";
$msg_error = "error!";
$sql = "UPDATE `$tbl_infra1` 
	SET species_id=NULL;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Populate species_id with nameIDs of species having exactly 1 entry in table `name` (i.e., no homonyms)
// Species with >1 entry are retrieved using the slower left/right index method below
// Species with 0 entries (value in `species` field in `name` table does not have its own entry as `scientificName`)
// are more complex, will require adding new species to core db; NOT YET IMPLEMENTED
echo "Linking trinomials to non-homonym species...";
$msg_error = "error!";

$sql = "
	UPDATE `$tbl_infra1` AS i INNER JOIN 
	(
		SELECT scientificName AS sp, count(nameID) as records
		FROM name
		WHERE nameRank='species'
		GROUP BY scientificName
		HAVING records=1
	) AS s
	INNER JOIN name AS n
	ON i.species_orig=s.sp AND s.sp=n.scientificName
	SET i.species_id=n.nameID
	WHERE n.nameRank='species';
	";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Mop up remaining unlinked trinomials using left and right indices
// Slow, but thorough & safe
echo "Linking remaining trinomials:\r\n";

// Get sourceID of default classification
$sql="SELECT sourceID FROM source WHERE isDefault=1";
$sourceID=sql_get_first_result($dbh, $sql,'sourceID');
If ($sourceID===false or $sourceID==NULL) die("failed retrieve 'sourceID' from table `source`");

/*
if(exists_index($dbh, $tbl_infra1,'infra1list_species_id')==true) {
	// Remove index on species_id to speed things up 
	echo "  Dropping index on `$tbl_infra1`.species_id...";
	$msg_error = "failed!";
	$sql = "ALTER TABLE `$tbl_infra1` DROP INDEX `infra1list_species_id`;";
	if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));
}
*/

echo "  Updating `$tbl_infra1`.species_id for names linked to default classification...";
$msg_error = "failed!";
$sql="
	UPDATE `$tbl_infra1` AS infra1, 
	(
		SELECT DISTINCT s.infra1_id, t.rightIndex, t.leftIndex
		FROM `$tbl_infra1` s INNER JOIN 
		(
			SELECT n.nameID, rightIndex, leftIndex
			FROM name AS n INNER JOIN classification as c
			ON n.nameID=c.nameID
			WHERE c.sourceID=$sourceID
			AND n.nameRank<>'species'
			AND (n.nameParts>2 OR n.nameParts IS NULL)
		) AS t
		ON s.infra1_id=t.nameID
		WHERE s.species_id IS NULL 
	) AS i,
	(
		SELECT n.nameID AS speciesID, c.leftIndex, c.rightIndex
		FROM name AS n INNER JOIN classification AS c
		ON n.nameID=c.nameID
		WHERE c.sourceID=$sourceID AND n.nameRank='species'
	) AS s
	SET infra1.species_id=s.speciesID
	WHERE 
	infra1.infra1_id=i.infra1_id 
	AND s.leftIndex < i.leftIndex AND s.rightIndex > i.rightIndex 
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

echo "  Updating `$tbl_infra1`.species_id for remaining names...";
$msg_error = "failed!";
$sql="
	UPDATE `$tbl_infra1` AS infra1, 
	(
		SELECT DISTINCT s.infra1_id, t.rightIndex, t.leftIndex
		FROM `$tbl_infra1` s INNER JOIN 
		(
			SELECT n.nameID, rightIndex, leftIndex
			FROM name AS n INNER JOIN classification as c
			ON n.nameID=c.nameID
			WHERE c.sourceID<>$sourceID 
			AND c.sourceID=n.originalSourceID
			AND n.nameRank<>'species'
			AND (n.nameParts>2 OR n.nameParts IS NULL)
		) AS t
		ON s.infra1_id=t.nameID
		WHERE s.species_id IS NULL 
	) AS i,
	(
		SELECT n.nameID AS speciesID, c.leftIndex, c.rightIndex
		FROM name AS n INNER JOIN classification AS c
		ON n.nameID=c.nameID
		WHERE c.sourceID<>$sourceID AND c.sourceID=n.originalSourceID AND n.nameRank='species'
	) AS s
	SET infra1.species_id=s.speciesID
	WHERE 
	infra1.infra1_id=i.infra1_id 
	AND
	s.leftIndex < i.leftIndex AND s.rightIndex > i.rightIndex 
	AND infra1.species_id IS NULL
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

if(exists_index($dbh, $tbl_infra1,'infra1list_species_id')==false) {
	echo "  Restoring index...";
	$msg_error = "failed!";
	$sql = "ALTER TABLE `$tbl_infra1` ADD INDEX `infra1list_species_id`(`species_id`);";
	if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));
}


?>
