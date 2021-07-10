<?php

/////////////////////////////////////////////////////////////////
// Purpose: Add integer PK to raw data
/////////////////////////////////////////////////////////////////

echo "Altering raw data table...";
$sql="
	ALTER TABLE `$tbl_names_raw`
	ADD COLUMN nameID INT PRIMARY KEY AUTO_INCREMENT FIRST,
	ADD COLUMN accNameID INT DEFAULT NULL AFTER nameID,
	ADD COLUMN inputSpecies VARCHAR(100) DEFAULT NULL,
	ADD COLUMN inputSpeciesRows INTEGER DEFAULT NULL,
	ADD COLUMN updateMethod VARCHAR(250) DEFAULT NULL,
	ADD INDEX (inputSpecies),
	ADD INDEX (inputSpeciesRows),
	ADD INDEX (accNameID),
	ADD INDEX (updateMethod)
	;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

?>
