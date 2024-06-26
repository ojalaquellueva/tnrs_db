<?php

//////////////////////////////////////////////////
//////////////////////////////////////////////////
// Loading scripts for TNRS core database
//
// By: Brad Boyle
// Contact: bboyle@arizona.edu
// TNRS website: https://tnrs.biendata.org
//  
// Everything you need to set is here and in 
// params.inc files in each import directory
//
// Read the README.md files in this directory and 
// all main subdirectories!
//////////////////////////////////////////////////
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// Appliction metadata
// Added to table meta, along with today's date
// If not known, set to empty string ('') and update later
// after DB build complete
//////////////////////////////////////////////////

// Full application version
// Encompasses base code, api code, db code, db content, web app code
// Version number is incremented whenever any of these change
// This is version number displayed on TNRS website
// Assigned manually
$APP_VERSION="5.2";

// Database content version
// Assigned manually
$DB_VERSION="4.4";

// Database code version
// From git
$DB_CODE_VERSION="4.4";

// TNRS application code version
// From git
$CODE_VERSION="5.1";

// API code git version
// From git
$API_VERSION="5.1";

/* Load from bibtex file in tnrs data directory instead
// Bibtex-formatted citation of application url
$APP_CITATION="@misc{tnrs, author = {Boyle, B. L. and Matasci, N. and Mozzherin, D. and Rees, T. and Barbosa, G. C. and Kumar Sajja, R. and Enquist, B. J.}, journal = {Botanical Information and Ecology Network}, title = {Taxonomic Name Resolution Service, version " . $CODE_VERSION . "}, year = {2021}, url = {https://tnrs.biendata.org/}, note = {Accessed <date_of_access>} }";

// Bibtex-formatted citation of application publication, if any
$APP_PUBLICATION="@article{tnrspub, author = {Boyle, B. and Hopkins, N. and Lu, Z. and Garay, J. A. R. and Mozzherin, D. and Rees, T. and Matasci, N. and Narro, M. L. and Piel, W. H. and McKay, S. J. and Lowry, S. and Freeland, C. and Peet, R. K. and Enquist, B. J.}, journal = {BMC Bioinformatics}, number = {1}, pages = {16}, title = {The taxonomic name resolution service: an online tool for automated standardization of plant names}, volume = {14}, year = {2013}, doi = {10.1186/1471-2105-14-16} ";
 */

// Location of main app url on filesystem, if any
$APP_LOGO_PATH="";

//////////////////////////////////////////////////
// Taxonomy sources
//
// CRITICAL!!!
// Include in this array the name of every source
// you will be importing into the TNRS database
// Import scripts and data for each source MUST
// be their own directory called "import_[$sourceName]",
// for example, "import_tropicos". Source names 
// below MUST match the parameter $sourceName 
// as specified in params.inc in import subdirectory
// for that source. 
//
// Sources load in order listed; order of loading
// determines order of display in 
// "Edit settings" > "Sources" in the TNRS web UI. 
// List a source first, below, if you want it to 
// display at the top of the list in the UI.
//////////////////////////////////////////////////

// Production TNRS db
// List sources in the order you want them to appear
// in the online menu of sources
$src_array=array(
	"wfo",
	"wcvp",
	"cact"
);

//////////////////////////////////////////////////
// Populate left and right tree traversal indices?
// Set to true for production. Set to false as
// a temporary measure for troubleshooting only. 
// If false, classification table will be empty
// and some higher taxa may be missing
//////////////////////////////////////////////////

$use_lr_indexes=false;

//////////////////////////////////////////////////
// Paths to required functions and utilities
//
// If desired, $local_utilities_path and $global_utilities_path
// can be the same. I keep them separate to distinguish between
// TNRS-related functions and universal functions used by all
// PHP applications. Up to you.
//////////////////////////////////////////////////

$local_utilities_path="functions/";
$global_utilities_path="php_utilities/";

//////////////////////////////////////////////////
// Path and name of database configuration file
// Absolute path or relative to this file
// Should be outide this repository!
//////////////////////////////////////////////////

$DB_CONFIG_FILE="../config/db_config_tnrs_db.php";

//////////////////////////////////////////////////
// Data directory
// Set this parameter if keep taxonomic source
// data outside main application source code
// directory & repo (recommended). 
// Data for each source should be inside this 
// directory, in its own directory with the same 
// unique $src code, as in $src_array, above.
// Omit trailing slash
//////////////////////////////////////////////////

$DATA_DIR="../data/db";

// Full path to TNRS data directory
// Contains bibtex files with citations for TNRS:
// TNRS_publication.bib, TNRS_website.bib
$TNRS_DATA_DIR = $DATA_DIR . "/tnrs/";

// Full path to collaborators data directory
// Only contents should be file "collaborators.csv"
$COLLABORATORS_DATA_DIR = $DATA_DIR . "/collaborators/";

//////////////////////////////////////////////////
//////////////////////////////////////////////////
// IN MOST CASES YOU WILL NOT NEED TO CHANGE
// THE REMAINING PARAMETERS
//////////////////////////////////////////////////
//////////////////////////////////////////////////

//////////////////////////////////////////////////
// Replace database? (true/false)
//
// Set to true to replace core database entirely
// all tables will be dropped and replaced with new,
// empty tables. Application will automatically prompt
// for confirmation if this option is set to true.
//
// Set to false keep existing database and
// add (if new) or replace (if already present) only
// the source(s) listed in $src_array.
//
// WARNING: Recommend keeping $replace_db=true and
// rebuilding entire database, even if only refreshing
// an individual data source or adding new sources to 
// the existing database. The option to update individual
// sources within an existing existing database has not
// been tested recently and may introduce anomalies. 
//////////////////////////////////////////////////

$replace_db = true;

//////////////////////////////////////////////////
// Adjust available memory
//////////////////////////////////////////////////

// Temporary PHP memory limit
// Increase this amount if scripts in taxamatch_tables/ 
// subdirectory trigger memory overflow error
// Comment out if not needed
ini_set("memory_limit","3000M");

//////////////////////////////////////////////////
// Load functions and utilities
//////////////////////////////////////////////////

include $global_utilities_path."functions.inc";
include $global_utilities_path."taxon_functions.inc";
include $global_utilities_path."sql_functions.inc";
$timer_on=$global_utilities_path."timer_on.inc";
$timer_off=$global_utilities_path."timer_off.inc";

// Taxamatch utilities
require_once $local_utilities_path."class.nearmatch.php";
require_once $local_utilities_path."class.normalize.php";

//////////////////////////////////////////////////
// Backup options
//////////////////////////////////////////////////

// Load database parameters first
include $DB_CONFIG_FILE;

// Save intermediate tables to separate backup database?
// This will save copies of raw data tables
// and staging tables (if requested; see below)
// to database $DB_BACKUP
// A useful option for troubleshooting and validation
$use_db_backup=true;

// The following database will be used to store backup
// copies of raw data tables and staging. If database 
// does not exist, it will be created; if it does exist, 
// it will be replaced.  
// This is *not* a backup of the completed TNRS database, 
// but rather the raw data that went into it
$DB_BACKUP = $DB."_staging";

// Save a backup copy of staging table? This 
// prevents staging table for current source
// from being lost when a new source is loaded
// If set=true, be sure to set the name of the
// backup staging table, $tbl_staging_bak
// (see below)
$backup_staging=true;

// Save a mysqldump of entire database after loading each source?
// Will be saved to $BACKUP_DIR 
// Name of all sources in db are appended to
// mysqldump file, plus '.sql' suffix
$backup_by_source = true;

// directory, relative to this script, for saving database backups
$BACKUP_DIR = "../backups/";

//////////////////////////////////////////////////
// Error-reporting & runtime behavior
//////////////////////////////////////////////////

// echos error messages to screen
$echo_on = true;		

// aborts entire script on error
$die_on_fail = true;		

// default success and fail messages
$msg_success = "done\r\n";
$done = $msg_success; 
$msg_fail = "failed!\r\n";

//////////////////////////////////////////////////
// Higher taxon parameters
//////////////////////////////////////////////////

// Column separated array of higher taxa represented by denormalized 
// columns in table `name`. One column is added for EACH source flagged 
// isHigherClassification=true. Name of column is formed as follows:
// [higher taxon rank]_[higher classification source name]. E.g., 
// family_tropicos.
$higher_taxon_array=array(
	"family"
);

//////////////////////////////////////////////////
// Tropicos-specific fixes
// Performed on completed database after all 
// other steps complete. See readme in directory
// tropicos_fixes.
//////////////////////////////////////////////////

$apply_tropicos_fix_noOpNames = true;
$apply_tropicos_fix_link_to_acceptedNames = true;

//////////////////////////////////////////////////
// Name resolution parameters
//////////////////////////////////////////////////

// Set fuzzy_match=true to resolve source names using tnrs.
// Requires file of results of matching source names against
// the TNRS database itself.
// Currently, this option only results in population of 
// the field `fuzzyMatchNameID` in table `name`. 
// Names matching *exactly* to names already
// in database are indexed rather than added. All other names are 
// added. In future, may find a way of indexing rather than adding
// fuzzy-matched names; however, this is dangerous as it disrupts
// child-parent adjacency among source names.
// Currently, to use this option you need to select all distinct
// names in source and submit to TNRS; csv results file should be
// made available to this script. In future, will automate
// entire process using web service. 
// If you set fuzzy_match=true, you MUST set the name and 
// path of the results file, below. 
// Setting fuzzy_match=false will skip import and normalization
// of the tnrs_results file, and leave column `fuzzyMatchNameID` NULL.
// The remaining name resolution parameters will be ignored.
// If you set fuzzy_match=true, you must set the remaining name
// resolution parameters
$fuzzy_match=false;

// name of csv file containing results of 
// processing source names using tnrs
$tnrs_results_file="tnrs_results.csv";	// made up example; your file name here

// path relative to load_core_db/, where 
// scripts accessing this file run:
$tnrs_results_path="tnrs_results_raw/";

// name of mysql table:
$tnrs_results="tnrs_results";

// Minimum overall match score required for name to be considered a match
$tnrs_overall_score_min=0.9;	

// Minimum score for author part of name (only applies to submitted names with authors)
$tnrs_author_score_min=0.6; 
	
// Import parameters for tnrs_results file
// To remove an option entirely, set it=" ",
// do not just delete the variable entirely
$tr_local = " LOCAL ";	// LOCAL keyword
$tr_fields_terminated_by = " FIELDS TERMINATED BY ',' ";
//$tr_optionally_enclosed_by = " ";
$tr_optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  // use if text surrounded by quotes
//tr_lines_terminated_by = " LINES TERMINATED BY '\n' ";
$tr_ignore_lines = " IGNORE 1 LINES ";	// set 1 to ignore header line

//////////////////////////////////////////////////
// Name resolution parameters
//////////////////////////////////////////////////

// Set fuzzy_match=true to resolve source names using tnrs.
// Requires file of results of matching source names against
// the TNRS database itself.
// Currently, this option only results in population of 
// the field `fuzzyMatchNameID` in table `name`. 
// Names matching *exactly* to names already
// in database are indexed rather than added. All other names are 
// added. In future, may find a way of indexing rather than adding
// fuzzy-matched names; however, this is dangerous as it disrupts
// child-parent adjacency among source names.
// Currently, to use this option you need to select all distinct
// names in source and submit to TNRS; csv results file should be
// made available to this script. In future, will automate
// entire process using web service. 
// If you set resolve_names=true, you MUST set the name and 
// path of the results file, below. 
// Setting fuzzy_match=false will skip import and normalization
// of the tnrs_results file, and leave column `fuzzyMatchNameID` NULL.
// The remaining name resolution parameters will be ignored.
// If you set fuzzy_match=true, you must set the remaining name
// resolution parameters
$fuzzy_match=false;

// name of csv file containing results of 
// processing source names using tnrs
$tnrs_results_file="tnrs_results.csv";	// made up example; your file name here

// path relative to load_core_db/, where 
// scripts accessing this file run:
$tnrs_results_path="tnrs_results_raw/";

// name of mysql table:
$tnrs_results="tnrs_results";

// Minimum overall match score required for name to be considered a match
$tnrs_overall_score_min=0.9;	

// Minimum score for author part of name (only applies to submitted names with authors)
$tnrs_author_score_min=0.6; 	

// Import parameters for tnrs_results file
// To remove an option entirely, set it=" ",
// do not just delete the variable entirely
$tr_local = " LOCAL ";	// LOCAL keyword
$tr_fields_terminated_by = " FIELDS TERMINATED BY ',' ";
//$tr_optionally_enclosed_by = " ";
$tr_optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  // use if text surrounded by quotes
//tr_lines_terminated_by = " LINES TERMINATED BY '\n' ";
$tr_ignore_lines = " IGNORE 1 LINES ";	// set 1 to ignore header line

//////////////////////////////////////////////////
// Tree traversal parameters
//////////////////////////////////////////////////

// These parameters affect population of left and right indices
// used for ancestor/descendent searches

// name of root
$root_name = "root";		

// name of root rank
$root_rank = "root";	

// Set FALSE if table already contains root record
$add_root = TRUE;		

// Adds temporary node above root during indexing
// Must set=TRUE if any taxa lack parentID in 
// original data ("orphan taxa") otherwise 
// traversal will fail
$preroot = true;	

//////////////////////////////////////////////////
// Table & column names
//////////////////////////////////////////////////

// In general, should not need to change these
// I just made them variables because I kept changing 
// my mind about what they should be called. Also
// for some reason I find it easier to spell a variable 
// consistently than a column or table name. Go figure.
// Eventually will change to using actual names throughout
// and eliminate this section

// Staging table 
$tbl = "nameStaging";			// staging table
$tbl_staging=$tbl;				// alternative name used by some scripts (will standardize eventually...)

$tbl_syn = "synonymStaging";			// temporary staging table for synonymy only
						// Used only if synonyms in separate table
						// from names in raw data

$id_fld = "nameID";				// name of ID field (PK) for this table

$nomenclaturalCode_fld = "nomenclaturalCode";	// code governing this name; default
						// value set in import parameters for the source being loaded

$parent_id_fld = "parentNameID";	// name of parentID field
$id_fld_orig = 'nameID_orig';		// field containing original name ID
$source_url_fld="nameUri";			// field containing source url for name
$lsid_fld="lsid";					// LSID field
$rank_fld = "nameRank";				// taxonomic rank field
$name_fld = "scientificName";		// field containing taxon name
$author_fld = "scientificNameAuthorship";	// field containing authority
$nameAuthor_fld = "scientificNameWithAuthor";	// taxon name with authority concatenated
$subclass_fld="subclass";
$family_fld="family";
$genus_fld="genus";
$specific_epithet_fld="specificEpithet";
$rank_ind_fld="rankIndicator";			// Abbreviated rank indicator of trinomial
$infraepithet_fld="infraspecificEpithet";	// Trinomial epithet
$rank_ind_fld2="rankIndicator2";		// Quadrinomial rank indicator
$infraepithet_fld2="infraspecificEpithet2";	// Quadrinomial epithet
$otherEpithet_fld="otherEpithet";		// epithets of tribes, sections, etc.
$subclass_fld="subclass";			// holds family, if provided by source
$family_fld="family";				// holds subclass, if provided by source
$is_hybrid="isHybrid";				// 0,1 (NOT NULL) flag field for hybrid
$left_index_fld = "leftIndex";			// left index field
$right_index_fld = "rightIndex";		// right index field
$fk_fld = "FK_nameID";				// FK linking to name table in core db
$parent_fk_fld="FK_parentNameID";		// FK linking parent name in name table
$null_parent_fld = "isNullParentID";		// Temporary field for flagging null parentTaxonIDs

// The following two column names used for both main staging
// table and synonym staging table (if any)
$acceptance_fld="acceptance";			// name of acceptance/taxonomic status field
$accepted_id_fld="acceptedNameID";		// name of accepted name ID field

// Error table 
$error_tbl ="error_table";
$srcTbl="source_table";
$has_errors="has_errors";
$is_orphan_parentNameID="is_orphan_parentNameID";
$is_orphan_acceptedNameID="is_orphan_acceptedNameID";	
$is_orphan_synonym_nameID="is_orphan_synonym_nameID";	
$is_null_parentNameID="is_null_parentNameID";
$errmsg="error_message";	

// Taxamatch table names
$tbl_fam="famlist";
$tbl_gen="genlist";
$tbl_sp="splist";
$tbl_infra1="infra1list";
$tbl_infra2="infra2list";
$tbl_comb_fg="genlist_famlist_combined";
$tbl_comb_gs="splist_genlist_combined";
$tbl_comb_st="infra1list_splist_combined";
$tbl_comb_tq="infra2list_infra1list_combined";

//////////////////////////////////////////////////
// Default MySQL import parameters
// These can be over-ridden in the params.inc
// file for a particular source
//////////////////////////////////////////////////
$local = " LOCAL ";
$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
$optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  
$escaped_by = "";
$lines_terminated_by = " LINES TERMINATED BY '\n' ";
$ignore_lines = " IGNORE 1 LINES ";	

?>
