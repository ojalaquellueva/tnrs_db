<?php
// Populates synonym table

echo "  Populating table `synonym`...";
// Insert synonym records for this source linked to an
// accepted name
$sql="
	INSERT INTO `synonym` (
	acceptedNameID,
	sourceID,
	nameID,
	acceptance
	)
	SELECT 
	acc.FK_nameID,
	$sourceID,
	syn.FK_nameID,
	syn.acceptance
	FROM nameStaging syn JOIN nameStaging acc
	ON syn.acceptedNameID=acc.nameID;
";
if (sql_execute($dbh, $sql,TRUE,$echo_on,'',$msg_fail));

// Insert synonym records for this source NOT linked to
// an accepted name. These would either be accepted names
// or synonyms for which an accepted name not provided
$sql="
	INSERT INTO `synonym` (
	sourceID,
	nameID,
	acceptance
	)
	SELECT 
	$sourceID,
	FK_nameID,
	acceptance
	FROM nameStaging  
	WHERE FK_nameID IS NOT NULL AND acceptedNameID IS NULL AND acceptance IS NOT NULL;
";
if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_fail));

// Standardize acceptance codes
// Should have be done earlier, for each source, but am repeating here
// just in case.
echo "    Standardizing acceptance codes...";
$sql="
UPDATE `synonym` 
SET acceptance=
CASE
WHEN acceptance='A' THEN 'Accepted'
WHEN acceptance='S' THEN 'Synonym'
WHEN acceptance='Unresolved' THEN 'No opinion'
WHEN acceptance='Unassessed' THEN 'No opinion'
ELSE acceptance
END
;
";
$msg_error="ERROR!";
if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));

?>
