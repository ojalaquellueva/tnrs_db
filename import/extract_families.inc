<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Add families as rows and link genera to families
// Family MUST be present in separate column but not as rows
/////////////////////////////////////////////////////////////////


// Extract family from the column "family" and add them to as 
// separate taxa
// Only do this if you are sure families are not already
// in the classification. May get weird results if taxa between
// the ranks of genus and family area included. This is also a 
// bad idea if the source database contains homonym families (unlikely)

echo "Extracting families...";
$sql="
	-- Assume OK to flag all families as accepted for this source
	INSERT INTO `$tbl_names_raw` (
	family,
	scientificName,
	`rank`,
	taxonomicStatus,
	name_added
	)
	SELECT DISTINCT
	family,
	family,
	'family',
	'Accepted',
	1
	FROM `$tbl_names_raw`
	WHERE family IS NOT NULL;
";
sql_execute_multiple($dbh, $sql);
echo $done;	

echo "Linking genera to families...";
$sql="
	UPDATE `$tbl_names_raw` g JOIN `$tbl_names_raw` f
	ON g.family=f.scientificName
	SET g.parentNameID=f.nameID
	WHERE g.`rank`='genus' AND f.`rank`='family' 
";
sql_execute_multiple($dbh, $sql);
echo $done;	


?>
