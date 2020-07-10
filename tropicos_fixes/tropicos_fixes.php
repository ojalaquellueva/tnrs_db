<?php

////////////////////////////////////////////////////////
// Apply Tropicos-specific fixes to completed database
//
// Options $apply_tropicos_fix_noOpNames and 
// $apply_tropicos_fix_link_to_acceptedNames are set in 
// global_params.inc. If both are set to false,
// this file does nothing
////////////////////////////////////////////////////////

if ($apply_tropicos_fix_noOpNames || $apply_tropicos_fix_link_to_acceptedNames) {
	include "params.inc";
	include_once "check_required_files.inc";
	echo "Applying Tropicos-specific fixes:\r\n";
	
	// Retrieve sourceID for tropicos
	$sql="
	SELECT sourceID
	FROM source
	WHERE sourceName='tropicos'
	;
	";
	$tropicosSourceID=sql_get_first_result($dbh, $sql,'sourceID');
	$msg_err = "\r\nFailed to retrieve sourceID for Tropicos!\r\n";
	if ($tropicosSourceID=='' || $tropicosSourceID===false) die("$msg_err");

	////////////////////////////////////////////////////////
	// Populate acceptedNameID for some synonymous names 
	// wrongly labeled as "No Opinion" by Computed Acceptance
	//
	// Requires as input the result of a manual download 
	// obtained by a Tropicos insider! See required file in 
	// directory data/
	////////////////////////////////////////////////////////

	if ($apply_tropicos_fix_noOpNames) {
		echo "  Populating missing accepted name links for no-opinion names:\r\n";
		include_once "noOpNames_import.inc";
		include_once "noOpNames_prepare.inc";
		include_once "noOpName_update.inc";
	}

	////////////////////////////////////////////////////////
	// Transfer taxonomic status and links to accepted name 
	// for species belonging to a non-accepted genus but 
	// wrongly labeled by ComputedAcceptance as "Accepted"
	////////////////////////////////////////////////////////
	if ($apply_tropicos_fix_link_to_acceptedNames) {
		echo "  Correcting taxonomic status of species linked to invalid genera:\r\n";
		include_once "link_to_acceptedNames.inc";
	}
}

?>