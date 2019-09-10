<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Standardizes values in column `acceptance`. 
// Currently, allowed values for `acceptance` are:
// Accepted, Synonymy, Invalid, Illegitimate, 'Rejected name' or NULL
/////////////////////////////////////////////////////////////////

echo "Standardizing column `acceptance`...";
$sql="
	UPDATE `$tbl_names_raw`
	SET acceptance='Synonym'
	WHERE acceptance='S';
";
$msg_error="failed to set acceptance='Synonym'!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));

$sql="
	UPDATE `$tbl_names_raw`
	SET acceptance='Accepted'
	WHERE acceptance='A';
";
$msg_error="failed to set acceptance='Accepted'!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));

$sql="
	UPDATE `$tbl_names_raw`
	SET acceptance=NomenclatureStatusName
	WHERE acceptance IS NULL 
	AND NomenclatureStatusName IN ('Illegitimate','Invalid');
";
$msg_error="failed to transfer NomenclatureStatusName to acceptance field'!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));

$sql="
	UPDATE `$tbl_names_raw`
	SET acceptance='Rejected name'
	WHERE acceptance IS NULL 
	AND NomenclatureStatusName='nom. rej.';
";
$msg_error="failed to update acceptance field for 'nom. rej.' names!";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));


?>
