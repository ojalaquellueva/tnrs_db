<?php

/////////////////////////////////////////////////////////////////
// Parse names using TNRS API
/////////////////////////////////////////////////////////////////

echo "Parsing names with TNRS:";
echo "  Reading names into array...";
mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);
$sql = new mysqli($config['host'], $config['user'], $config['pass'], $config['db_name']);

$query = "SELECT domain FROM services";
$result = $sql->query($query);
$rows = [];
while($row = $result->fetch_row()) {
    $rows[] = $row;
}
return $rows;






$sql="
	UPDATE `$tbl_names_raw` syn JOIN `$tbl_names_raw` acc
	ON syn.outputTaxon=acc.inputTaxon
	SET syn.accNameID=acc.nameID
	WHERE syn.status='synonym'
	;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

?>
