<?php

//////////////////////////////////////////////////
// This is the parameters file used by the 
// stand-alone version of the tropicos fixes
// script, tropicos_fixes_standalone.php
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// Main options. If both are set to false, this
// script does nothing
//////////////////////////////////////////////////

$apply_tropicos_fix_noOpNames = true;
$apply_tropicos_fix_link_to_acceptedNames = true;

//////////////////////////////////////////////////
// Include paths and filenames
//////////////////////////////////////////////////

$local_utilities_path="../functions/";
$global_utilities_path="../../global_utilities/";

include $global_utilities_path."functions.inc";
include $global_utilities_path."taxon_functions.inc";
include $global_utilities_path."sql_functions.inc";
$timer_on=$global_utilities_path."timer_on.inc";
$timer_off=$global_utilities_path."timer_off.inc";

//////////////////////////////////////////////////
// Db connection info
//////////////////////////////////////////////////

$HOST = "localhost";
// Explicit host name for display at runtime
$HOST=="localhost"?$HOSTNAME=exec('hostname -f'):$HOSTNAME=$HOST;
$USER = "admin";
$PWD = "lae5eiNa";
$DB = "tnrs4";

//////////////////////////////////////////////////
// Application parameters
//////////////////////////////////////////////////

// Required input file
$dataDir = "data/";
$noOpNamesFile="noOpNamesResults.txt";

$done="done\r\n";

?>