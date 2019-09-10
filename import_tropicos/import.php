<?php
// Imports raw dump of names & synonymy from single source MySQL tables

include "params.inc";	// everything you need to set is here and in global_params.inc

////////////// Import raw data file //////////////////////

// create empty import table
include "create_raw_data_tables.inc";

// import text files to raw data tables
include "import.inc";

// standardize acceptance codes
include "standardize_acceptance.inc";

// Create staging table
include "create_staging_table.inc";

// Add names & synonymy to staging table
include "add_names.inc";

//////////////////////////////////////////////////////////


?>
