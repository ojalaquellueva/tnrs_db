<?php

include "params.inc";	

////////////// Import raw data file //////////////////////

// create empty import table
include "create_raw_data_tables.inc";

// replaces 'NULL' with '\N' in the raw file
include "fix_nulls_raw.inc";

// import text files to raw data tables
include "import.inc";

// Source-specific corrections best done on the raw data
include "correct_raw.inc";

// Transfer contents of original raw data table to
// simplified DwC table ([sourcename]_dwc), add 
// "_verbatim" suffix to original table 
// ([sourcename]_raw_verbatim) and rename DwC 
// table to [sourcename]_raw.
include "load_dwc.inc";

// add fields to raw names table to support
// integer nameID, parentNameID and acceptedNameID
include "alter_raw_data_table.inc";

// Update non-ascii characters to UTF-8
include "fix_character_set.inc";

// Populate integer parentNameID and acceptedNameID
include "update_raw_data_table.inc";

// Standardize source-specific values in column `acceptance`
include "standardize_acceptance.inc";

// Standardize hybrid 'x'
include "standardize_hybrid_x.inc";

// Extract families from lower taxa
if ($extract_families==TRUE) {
	include "extract_families.inc";
}

// Extract families and genera from lower taxa
if ($infer_parent_this_source==TRUE) {
	include "infer_parent.inc";
}

// Form name search url for any new taxa added
include "make_url.inc";

// Create staging table
include "create_staging_table.inc";

// Add names & synonymy to staging table
include "add_names_to_staging.inc";

// exit("STOPPING...\r\n");

//////////////////////////////////////////////////////////

?>