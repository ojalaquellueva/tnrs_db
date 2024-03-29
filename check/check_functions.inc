<?php
///////////////////////////////////////////////////////
// Checks for required MySQL functions in database
// Installs if missing
///////////////////////////////////////////////////////

// check that function strSplit exists in target database
$sql="
	SELECT COUNT(*) AS strSplitExists
	FROM information_schema.ROUTINES 
	WHERE ROUTINE_TYPE='FUNCTION' AND SPECIFIC_NAME='strSplit'
	AND ROUTINE_SCHEMA='".$DB."';
";
$strSplitExists=sql_get_first_result($dbh, $sql,'strSplitExists');

if(!$strSplitExists) {
	// install the missing function:
	echo "Installing required MySQL function 'strSplit'...";
	
	// set database, just in case
	$sql="USE `".$DB."`;";
	sql_execute_multiple($dbh, $sql);
	
	// create function in current database
	$sql = "
		CREATE FUNCTION `strSplit`(str varchar(255), delim varchar(12), tokenNo int)  
		RETURNS varchar(255) CHARSET utf8
		NO SQL
		DETERMINISTIC
		RETURN replace(SUBSTRING(SUBSTRING_INDEX(str, delim, tokenNo), LENGTH(SUBSTRING_INDEX(str, delim, tokenNo - 1)) + 1), delim, '')
		;
	";
	$exec_query=mysqli_query($dbh, $sql);
	$msg_error="Failed to install function 'strSplit'!\r\n" . mysqli_error($dbh ) . "\r\n";
	if (!$exec_query) die($msg_error);
	echo "done\r\n";
}

?>