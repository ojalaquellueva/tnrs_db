<?php

////////////////////////////////////////////////////////
// Apply Tropicos-specific fixes to completed database
//
// This is a stand-alone version. Nop art of pipeline.
// Uses options set params_standalone.inc
////////////////////////////////////////////////////////

// Parameters
// Everything you need to set is here and in global_params.inc
include "params_standalone.inc";	

// Connect to MySQL
$dbh = mysqli_connect($HOST,$USER,$PWD,FALSE,128);
if (!$dbh) die("\r\nCould not connect to MySQL!\r\n");

$sql="USE `$DB`";
sql_execute_multiple($dbh, $sql);

// Retrieve sourceID for tropicos
$sql="
SELECT sourceID
FROM source
WHERE sourceName='tropicos'
;
";
$tropicosSourceID=sql_get_first_result($dbh, $sql,'sourceID');
if ($tropicosSourceID=='' || $tropicosSourceID===false) die("$msg_err");

$msg_confirm="
Repair problems with source 'tropicos' (sourceID=$tropicosSourceID) in TNRS database version $DB? \r\nEnter 'Yes' to proceed, or 'No' to cancel: ";

// Confirm operation 
$proceed=responseYesNoDie($msg_confirm);
if ($proceed===false) die("\r\nOperation cancelled\r\n");

// Check for required files
include_once "check_required_files.inc";

// Start timer and connect to mysql
echo "\r\n********* Begin operation *********\r\n\r\n";
include $timer_on;


echo "Applying Tropicos-specific fixes:\r\n";

///////////////////////////////////////
// Populate acceptedNameID for some
// synonymous names wrongly labeled as
// "No Opinion" by Computed Acceptance
//
// Requires as input the result
// of a manual download obtained by a 
// Tropicos insider! See required
// file in directory data/
///////////////////////////////////////

if ($apply_tropicos_fix_noOpNames) {
	echo "  Populating missing accepted name links for no-opinion names:\r\n";
	include_once "noOpNames_import.inc";
	include_once "noOpNames_prepare.inc";
	include_once "noOpName_update.inc";
}

///////////////////////////////////////
// Transfer taxonomic status and links to 
// accepted name for species belonging to
// a non-accepted genus but wrongly labeled
// by ComputedAcceptance as "Accepted"
///////////////////////////////////////
if ($apply_tropicos_fix_link_to_acceptedNames) {
	echo "  Correcting taxonomic status of species linked to invalid genera:\r\n";
	include_once "link_to_acceptedNames.inc";
}

//////////////////////////////////////////////////////////////////
// Close connection and report total time elapsed 
//////////////////////////////////////////////////////////////////

mysqli_close($dbh, $dbh);
include $timer_off;
$msg = "\r\nTotal time elapsed: " . $tsecs . " seconds.\r\n"; 
$msg = $msg . "********* Operation completed " . $curr_time . " *********";
echo $msg . "\r\n\r\n"; 

?>