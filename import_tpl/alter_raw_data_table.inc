<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Indexes key fields and adds the following fields to the raw names table:
// nameID, parentNameID, acceptance, acceptedNameID
// These are needed to provide integer equivalents to the
// character ID fields used in the original
/////////////////////////////////////////////////////////////////

echo "Altering raw data table...";
$sql="
	ALTER TABLE `$tbl_names_raw`
	ADD COLUMN nameID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT FIRST,
	ADD COLUMN parentNameID INTEGER UNSIGNED DEFAULT NULL AFTER parentNameID_char,
	ADD COLUMN acceptedNameID INTEGER UNSIGNED DEFAULT NULL AFTER acceptedNameID_char,
	ADD INDEX `".$tbl_names_raw."_nameID`(nameID),
	ADD INDEX `".$tbl_names_raw."_parentNameID`(parentNameID),
	ADD INDEX `".$tbl_names_raw."_acceptedNameID`(acceptedNameID),
	ADD INDEX (nameID_char),
	ADD INDEX (parentNameID_char),
	ADD INDEX (rank),
	ADD INDEX (family),
	ADD INDEX (scientificName),
	ADD INDEX (genus),
	ADD INDEX (specificEpithet),
	ADD INDEX (infraspecificRank),
	ADD INDEX (infraspecificEpithet),
	ADD INDEX (infraspecificRank2),
	ADD INDEX (infraspecificEpithet2),
	ADD INDEX (taxonomicStatus),
	ADD INDEX (acceptedNameID_char)
	;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

?>
