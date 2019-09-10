<?php
// Links quadrinomials to trinomials by populating infra_id column

// Populate infra_id with nameIDs of trinomials having 
// exactly 1 entry in table `name` (i.e., no homonyms)
// Infraspecific taxa with >1 entry are retrieved using 
// the slower left/right index method below. Infraspecific 
// taxa with 0 entries are more complex, will require adding 
// new species to core db; NOT YET IMPLEMENTED
echo "Linking quadrinomials to non-homonym trinomials...";
$msg_error = "error!";

// update links to trinomials with exactly 1 record
$sql = "
	UPDATE `$tbl_infra2` AS q INNER JOIN 
	(
		SELECT scientificName AS infrasp, count(nameID) as records
		FROM name
		WHERE nameParts=3 
		AND (isHybrid=0 OR isHybrid IS NULL)
		GROUP BY scientificName
		HAVING records=1
	) AS t
	INNER JOIN name AS n
	ON q.infra1_orig=t.infrasp AND t.infrasp=n.scientificName
	SET q.infra1_id=n.nameID
	WHERE n.nameParts=3 
	AND (n.isHybrid=0 OR n.isHybrid IS NULL);
	";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Mop up remaining unlinked quadrinomials using left and right indices
// Slow, but thorough & safe
echo "Linking remaining quadrinomials:\r\n";

// Get sourceID of default classification
// This isn't really required, as these variables are set in the 
// first link_*.inc script.
// For debugging only, allows running of this step alone
// without repeating earlier steps
$sql="SELECT sourceID FROM source WHERE isDefault=1";
$sourceID=sql_get_first_result($dbh, $sql,'sourceID');
If ($sourceID===false or $sourceID==NULL) die("failed retrieve 'sourceID' from table `source`");

// Update for default source
echo "  Updating `$tbl_infra2`.infra1_id for names linked to default classification...";
$msg_error = "Failed!";
$sql="
	UPDATE `$tbl_infra2` AS infra2, 
	(	
		SELECT DISTINCT s.infra2_id, t.rightIndex, t.leftIndex
		FROM `$tbl_infra2` s INNER JOIN (
			SELECT n.nameID, rightIndex, leftIndex
			FROM name AS n INNER JOIN classification as c
			ON n.nameID=c.nameID
			WHERE c.sourceID=$sourceID
		) AS t
		ON s.infra2_id=t.nameID
		WHERE s.infra2_id IS NULL 
	) as i2,
	(
		SELECT n.nameID AS infra1ID, c.leftIndex, c.rightIndex
		FROM name AS n INNER JOIN classification AS c
		ON n.nameID=c.nameID
		WHERE c.sourceID=$sourceID AND n.nameParts=3 AND (n.isHybrid=0 OR n.isHybrid IS NULL)
	) as infra1
	SET infra2.infra1_id=infra1.infra1ID
	WHERE infra2.infra2_id=i2.infra2_id
	AND infra1.leftIndex < i2.leftIndex AND infra1.rightIndex > i2.rightIndex
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Update for remaining names
echo "  Updating `$tbl_infra2`.infra1_id for remaining names...";
$msg_error = "Failed!";
$sql="
	UPDATE `$tbl_infra2` AS infra2, 
	(	
		SELECT DISTINCT s.infra2_id, t.rightIndex, t.leftIndex
		FROM `$tbl_infra2` s INNER JOIN (
			SELECT n.nameID, rightIndex, leftIndex
			FROM name AS n INNER JOIN classification as c
			ON n.nameID=c.nameID
			WHERE c.sourceID<>$sourceID 
			AND c.sourceID=n.originalSourceID
			AND (n.nameParts=4 OR n.nameParts IS NULL)
		) AS t
		ON s.infra2_id=t.nameID
		WHERE s.infra2_id IS NULL 
	) as i2,
	(
		SELECT n.nameID AS infra1ID, c.leftIndex, c.rightIndex
		FROM name AS n INNER JOIN classification AS c
		ON n.nameID=c.nameID
		WHERE c.sourceID<>$sourceID 
		AND c.sourceID=n.originalSourceID 
		AND n.nameParts=3 
		AND (n.isHybrid=0 OR n.isHybrid IS NULL)
	) as infra1
	SET infra2.infra1_id=infra1.infra1ID
	WHERE infra2.infra2_id=i2.infra2_id
	AND infra1.leftIndex < i2.leftIndex AND infra1.rightIndex > i2.rightIndex
	AND infra2.infra1_id IS NULL
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

?>
