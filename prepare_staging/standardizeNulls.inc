<?php

// Delete records where scientificName is an empty string. 
// Prevents fatal error in the next step, as scientificName 
// can't be null. 
// No idea how this could happen at this late stage in 
// the pipeline, but it did.
echo "  Deleting records with missing scientificName...";
$msg_error = "Failed!\r\n";
$sql="
	DELETE FROM `$tbl_staging`
	WHERE TRIM(scientificName)=''
	;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

echo "  Converting empty strings to NULL...";
if (!(empty_string_to_null($dbh, $tbl_staging))) die("Error\r\n.");
echo "  done\r\n";

?>
