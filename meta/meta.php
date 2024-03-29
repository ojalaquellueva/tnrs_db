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
app_version,
db_version,
build_date,
db_code_version,
code_version,
api_version,
citation,
publication,
logo_path
)
VALUES (
'$APP_VERSION',
'$DB_VERSION',
CURRENT_DATE(),
'$DB_CODE_VERSION',
'$CODE_VERSION',
'$API_VERSION',
NULL,
NULL,
'$APP_LOGO_PATH'
)
";
$msg_error="Failed to populate table `meta`!";
if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));

// Populate literature citations from bibtex files
include 'add_source_citation.inc';

?>