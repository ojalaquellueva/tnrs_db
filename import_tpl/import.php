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

// Populate integer parentNameID and acceptedNameID
include "update_raw_data_table.inc";

// Standardize source-specific values in column `acceptance`
include "standardize_acceptance.inc";

// Extract families and genera from lower taxa
include "insert_higher_taxa.inc";

// Extract families and genera from lower taxa
include "infer_parent.inc";

// Form name search url for any new taxa added
include "make_url.inc";

//die("\r\nEXITING...\r\n");

// Create staging table
include "create_staging_table.inc";

// Add names & synonymy to staging table
include "add_names_to_staging.inc";

//////////////////////////////////////////////////////////

?>