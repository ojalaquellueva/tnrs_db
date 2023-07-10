<?php

echo "Dropping previous tables...";
$sql = "create_tnrs_core/drop_tables.sql";
//$command = "mysql --login-path=local -D $DB < $sql";
$command = "mysql --login-path=$LOGINPATH -D $DB < $sql";
system($command);
echo $msg_success;

echo "Creating tables...";
$sql = "create_tnrs_core/create_tables.sql";
//$command = "mysql --login-path=local -D $DB < $sql";
$command = "mysql --login-path=$LOGINPATH -D $DB < $sql";
system($command);
echo $msg_success;

echo "Creating data dictionary...";
$sql = "create_tnrs_core/data_dictionary.sql";
$command = "mysql --login-path=$LOGINPATH -D $DB < $sql";
system($command);
echo $msg_success;


?>
