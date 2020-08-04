<?php

///////////////////////////////////////////////////////////////
// Populate metadata table
///////////////////////////////////////////////////////////////

echo "Populating metadata table:\r\n";

echo "  Clearing table...";
$sql="
TRUNCATE meta
";
$msg_error="Failed to truncate table `meta`!";
if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));

echo "  Inserting verision information...";
$sql="
INSERT INTO meta (
db_version,
code_version,
build_date
)
VALUES (
'$DB_VERSION',
'$CODE_VERSION',
CURRENT_DATE()
)
";
$msg_error="Failed to populate table `meta`!";
if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));

?>