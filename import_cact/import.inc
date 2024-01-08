<?php

// Custom import script because two raw files, not one
// $local, $fields_terminated_by, $optionally_enclosed_by, $lines_terminated_by and $ignore_lines
// are set in parameters file

// Import names
$namesfile=$namesfile_acc;
$namesfileandpath = $filepath.$namesfile;
echo "Importing file '$namesfile' to table `$tbl_names_acc_raw`...";
if (stristr($namesfile,' ')) die("ERROR: whitespace in file name, please rename!\r\n");
$msg_error = "Failed!\r\n";
$sql = "LOAD DATA $local INFILE '$namesfileandpath' 
	INTO TABLE $tbl_names_acc_raw 
	$fields_terminated_by 
	$optionally_enclosed_by 
	$escaped_by
	$lines_terminated_by 
	$ignore_lines;
	";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

echo "  Validating import...";
if ($error=sql_check_import_errors($dbh,$namesfile,$filepath,$tbl_names_acc_raw)) {
	echo "$error\r\n";
} else {
	echo $done;
}

echo "  Converting empty strings to NULL...";
if (!(empty_string_to_null($dbh, $tbl_names_acc_raw))) die("Error\r\n.");
echo "done\r\n";


$namesfile=$namesfile_syn;
$namesfileandpath = $filepath.$namesfile;
echo "Importing file '$namesfile' to table `$tbl_names_syn_raw`...";
if (stristr($namesfile,' ')) die("ERROR: whitespace in file name, please rename!\r\n");
$msg_error = "Failed!\r\n";
$sql = "LOAD DATA $local INFILE '$namesfileandpath' 
	INTO TABLE $tbl_names_syn_raw 
	$fields_terminated_by 
	$optionally_enclosed_by 
	$escaped_by
	$lines_terminated_by 
	$ignore_lines;
	";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

echo "  Validating import...";
if ($error=sql_check_import_errors($dbh,$namesfile,$filepath,$tbl_names_syn_raw)) {
	echo "$error\r\n";
} else {
	echo $done;
}

echo "  Converting empty strings to NULL...";
if (!(empty_string_to_null($dbh, $tbl_names_syn_raw))) die("Error\r\n.");
echo "done\r\n";

?>