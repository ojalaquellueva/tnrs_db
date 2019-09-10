<?php
// Imports raw text file to mysql
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

// Import names
echo "Importing file '$namesfile'...";
if (stristr($namesfile,' ')) die("ERROR: whitespace in file name, please rename!\r\n");
$msg_error = "Failed!\r\n";
$sql = "LOAD DATA $local INFILE '$namesfileandpath' 
	INTO TABLE $tbl_names_raw 
	$fields_terminated_by 
	$optionally_enclosed_by 
	$escaped_by
	$lines_terminated_by 
	$ignore_lines;
	";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

echo "Validating import...";
if ($error=sql_check_import_errors($dbh,$namesfile,$filepath,$tbl_names_raw)) {
	echo "$error\r\n";
} else {
	echo $done;
}

//die("\r\n\r\nExiting...\r\n\r\n");

// Standardize NULLS
echo "Converting empty strings to NULL...";
//echo "WARNING: skipping this step...";
if (!(empty_string_to_null($dbh, $tbl_names_raw))) die("Error\r\n.");
echo "done\r\n";

?>