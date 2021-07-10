<?php

///////////////////////////////////////////////////////////////////////
// Create TNRS tables:
//	tnrs_submitted_${src}:	raw names submitted to TNRS
//	tnrs_parsed_${src}:  raw names parsed by TNRS	
///////////////////////////////////////////////////////////////////////

// Set table names
$tnrs_submitted = "tnrs_submitted_" . $src;
$tnrs_parsed = "tnrs_parsed_" . $src;

echo "Creating TNRS tables:\n";

echo "  `$tnrs_submitted`...";
$msg_error="failed to drop previous table!";
$sql="DROP TABLE IF EXISTS `$tnrs_submitted`;";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));
$msg_error="failed to create table!\r\n";
$sql="
CREATE TABLE `$tnrs_submitted` (
nameID INTEGER NOT NULL,
nameSubmitted VARCHAR(250) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Create DwC format data table
echo "  `$tnrs_parsed`...";
$msg_error="failed to drop previous table!";
$sql="DROP TABLE IF EXISTS `$tnrs_parsed`;";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));
$msg_error="failed to create table!\r\n";
$sql="
CREATE TABLE `$tnrs_parsed` (
id INTEGER DEFAULT NULL,
nameSubmitted VARCHAR(250) DEFAULT NULL,
family VARCHAR(50) DEFAULT NULL,
genus VARCHAR(50) DEFAULT NULL,
specificEpithet VARCHAR(50) DEFAULT NULL,
infraspecificRank VARCHAR(50) DEFAULT NULL,
infraspecificEpithet VARCHAR(50) DEFAULT NULL,
infraspecificRank2 VARCHAR(50) DEFAULT NULL,
infraspecificEpithet2 VARCHAR(50) DEFAULT NULL,
author VARCHAR(250) DEFAULT NULL,
annotations VARCHAR(50) DEFAULT NULL,
unmatchedTerms VARCHAR(250) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));
	
?>

