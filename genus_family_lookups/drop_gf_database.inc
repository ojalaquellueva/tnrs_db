<?php

/////////////////////////////////////////////////////////////////////
// Purpose:
// Drop temporary database, if it exists
// This is why I used the specific variable name DB_NEW
// Too dangerous to use the generic 'DB'
/////////////////////////////////////////////////////////////////////

echo "Dropping database '$DB_NEW'...";
$sql = "DROP DATABASE IF EXISTS `$DB_NEW`";
$retval = mysqli_query($dbh,  $sql );
if($retval) {
	echo $msg_success;
} else {
	die('Could not delete database: ' . mysqli_error($dbh ));
}

?>