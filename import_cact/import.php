<?php

include "params.inc";	

////////////// Import raw data file //////////////////////

// create empty import table
include "create_raw.inc";
include "import/create_dwc_raw.inc";

// replaces 'NULL' with '\N' in the raw data files
// This version updated to support separate acc & syn files
include "import/fix_nulls_raw_acc_syn.inc";

// Import raw data
// This version adapted to import separate files for accepted names and synonyms
include "import.inc";

# Merge separate accepted and synonym raw tables into single raw data table
/*
IMPORTANT NOTES: 
* Raw tables are immediately loaded to dwc_raw after merge
* Raw tables are then renamed with suffix _verbatim and archived
* dwc_raw table is rename to <src>_raw
* All subsequent import operations are performed on <src>_raw
* No further use is made of verbatim tables (except move to backup staging schema)
*/
include "merge_raw.inc";

// Add columns parentNameID & taxonomicStatus
include "alter_raw.inc";

// Populate column parentNameID based on values in treeIndex
include "extract_parentNameID.inc";

// Update taxonomicStatus to reflect status of stupid subfamilial "pseudo-taxa"
include "adjust_taxonomicStatus.inc";

// Remove sub-Cactaceae non-taxonomic groups and reset parent to root (=Cactaceae)
include "remove_pseudotaxa.inc";

// Transfer contents of original raw data table to
// simplified DwC table ([sourcename]_dwc)
include "load_dwc.inc";

// Add "_verbatim" suffix to original table 
// ([sourcename]_raw_verbatim) and rename DwC 
// table to [sourcename]_raw.
include "rename_raw.inc";

// Update non-ascii characters to UTF-8
include "import/fix_character_set.inc";

// Add column parentNameID and populate from values in treeIndex
include "import/alter_dwc_raw.inc";

// Source-specific data corrections to raw names table
include "correct_raw.inc";

// Populate hybrid symbol fields
// This MJST come before next step
include "flag_hybrids.inc";

// Populate integer parentNameID and acceptedNameID
include "populate_integer_recursive_fks.inc";

// Standardize ranks and rank indicators
include "standardize_rank.inc";

// Standardize source-specific values in column `acceptance`
// Source-specific
include "standardize_acceptance.inc";

// Standardize hybrid 'x'
include "import/standardize_hybrid_x.inc";

// Extract families from lower taxa
/* 
if ($extract_families==TRUE) {
	include "import/extract_families.inc";
}
 */
// Species method this source only: all Cactaceae!
include "populate_family.inc";

// Extract families and genera from lower taxa
if ($infer_parent_this_source==TRUE) {
	include "import/infer_parent.inc";
}

// Form name search url for any new taxa added
// Source-specific
include "make_url.inc";

// Create staging table
include "import/create_staging_table.inc";

// Add names & synonymy to staging table
include "load_staging.inc";

//////////////////////////////////////////////////////////

?>