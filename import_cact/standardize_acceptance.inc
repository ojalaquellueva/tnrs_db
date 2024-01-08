<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Fixes value "Unplaced" in column `acceptance`. "Unplaced"
// has nothing to do with taxonomic acceptance, but means only
// that the name has not been placed at the tribe level.
// The value should be set to either "Accepted", "Synonym"
// or NULL, depending on the value in the acceptedNameID column
// Note: currently, allowed values for `acceptance` are:
// Accepted, Synonymy, Invalid, Illegitimate, or NULL
/////////////////////////////////////////////////////////////////

echo "Standardizing column `taxonomicStatus`:\n";

echo "  'Unresolved' --> 'No opinion'...";
// I prefer "unresolved", but keeping for backward compatibility with TNRS code
$sql="
UPDATE `$tbl_names_raw`
SET taxonomicStatus='No opinion'
WHERE LOWER(taxonomicStatus)='unresolved' OR taxonomicStatus IS NULL
;
";
$msg_error="ERROR!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$done,$msg_error));

/* NOT NEEDED FOR THIS SOURCE
echo "  Unchecked --> 'No opinion'...";
$sql="
UPDATE `$tbl_names_raw`
SET taxonomicStatus='No opinion'
WHERE taxonomicStatus='Unchecked'
;
";
$msg_error="failed to set  Unchecked --> 'No opinion'!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$done,$msg_error));

echo "  Unplaced --> 'No opinion'...";
$sql="
UPDATE `$tbl_names_raw`
SET taxonomicStatus='No opinion'
WHERE taxonomicStatus='Unplaced'
;
";
$msg_error="failed to set  Unchecked --> 'No opinion'!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$done,$msg_error));

echo "  ambiguous --> 'No opinion'...";
$sql="
UPDATE `$tbl_names_raw`
SET taxonomicStatus='No opinion'
WHERE taxonomicStatus='ambiguous'
;
";
$msg_error="failed to set  ambiguous --> 'No opinion'!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$done,$msg_error));

echo "  NULL --> 'No opinion'...";
$sql="
UPDATE `$tbl_names_raw`
SET taxonomicStatus='No opinion'
WHERE taxonomicStatus IS NULL
;
";
$msg_error="failed to set NULL --> 'No opinion'!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$done,$msg_error));

echo "  'Artificial Hybrid' --> 'Accepted'...";
$sql="
UPDATE `$tbl_names_raw`
SET taxonomicStatus='Accepted'
WHERE taxonomicStatus='Artificial Hybrid'
;
";
$msg_error="failed to set 'Artificial Hybrid' --> 'Accepted'!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$done,$msg_error));
*/

?>