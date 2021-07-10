<?php

include "params.inc";	

////////////// Import raw data file //////////////////////

// create empty import table
include "create_raw_data_tables.inc";

// import text files to raw data tables
include "import.inc";

//Add integer nameID and acceptedNameID
include "alter_raw_data_table.inc";

// Populate acceptedNameID
include "update_raw.inc";

// create empty import table
include "create_tnrs_tables.inc";



exit("STOPPING...\n");

// create empty import table
include "prepare_tnrs_submitted.inc";



// add fields to raw names table to support
// integer nameID, parentNameID and acceptedNameID
include "alter_raw_dwc.inc";

// Populate integer parentNameID and acceptedNameID
include "update_raw_data_table.inc";

// Standardize source-specific values in column `acceptance`
include "standardize_acceptance.inc";

// Create staging table
include "create_staging_table.inc";

// Add names & synonymy to staging table
include "add_names_to_staging.inc";

//////////////////////////////////////////////////////////


?>
