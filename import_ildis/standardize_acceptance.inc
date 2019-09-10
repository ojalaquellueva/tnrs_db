<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Standardizes taxonomic status codes
/////////////////////////////////////////////////////////////////

echo "Standardizing column `taxonomicStatus`...";
$sql="
UPDATE `$tbl_names_raw`
SET taxonomicStatus=
CASE
WHEN taxonomicStatus LIKE '%accepted%' THEN 'Accepted'
WHEN taxonomicStatus LIKE '%misapplied%' THEN 'Misapplied'
WHEN taxonomicStatus LIKE '%synonym%' THEN 'Synonym'
WHEN taxonomicStatus IS NULL THEN 'Unresolved'
ELSE taxonomicStatus
END
;
";
$msg_error="failed to set value='Synonym'!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));

?>