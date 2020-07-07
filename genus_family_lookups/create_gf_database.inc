<?php

/////////////////////////////////////////////////////////////////////
// Purpose:
// Create new temporary database
/////////////////////////////////////////////////////////////////////

// Create database
echo "Creating database...";
$sql = "CREATE DATABASE `$DB_NEW`";
$retval = mysqli_query($dbh,  $sql );
if($retval) {
	echo $msg_success;
}else{
	die('Could not create database: ' . mysqli_error($dbh ));
}

?>
