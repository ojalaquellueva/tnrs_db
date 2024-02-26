<?php

/////////////////////////////////////////////////////////////////////////////
// Parameters specific to importing raw data from this source,
// used only by import scripts. See also global_params.inc for 
// parameters used by other scripts as well
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// Taxonomy source parameters
//////////////////////////////////////////////////

// Name which uniquely identifies this source within database
// Many operations, including table names, depend on this parameter
// REQUIRED
// MUST BE UNIQUE
// NO SPACES
// MAX 50 characters
$sourceName=$src;

// Longer, more descriptive name for source
// Can have spaces; not used in any scripts
// after adding to table `source`
$sourceNameFull="World Checklist of Vascular Plants";

// Primary url for this source (optional)
$sourceUrl="https://wcvp.science.kew.org/";	

// Geographic scope of this source
// Values: global|regional
$geographic_scope="global";	

// Taxonomic scope of this source
// Value: APGIV name of lowest phylogenetic node of this source
$taxonomic_scope="Tracheophyta";	

// General designation of scope
// Values: global|limited
// Limited is <global scope OR higher node than Vascular plants (e.g., a family)
$scope="global"

// Short single paragraph description of this source, for display on 
// TNRS website on Source page.
// No quotes! If you must include apostrophes (plain single quote) then 
// double them up to avoid crashing the api (e.g., world''s)
$description="The World Checklist of Vascular Plants is based on Kew’s names and taxonomic backbone which has been created by reconciling the names from the International Plant Names Index (IPNI) with the taxonomy from the World Checklist of Selected Plant Families (WCSP). This Beta version therefore only displays names that are in both IPNI and WCVP. It contains both families that have been completed and peer reviewed by both external and internal experts on the relevant families as well as families that are in the process of being edited and reviewed. Some of the original data which WCSP built upon came from our generous collaborators listed in the acknowledgements. WCVP aims to represent a global consensus view of current plant taxonomy by reflecting the latest published taxonomies while incorporating the opinions of taxonomists based around the world.";

// Url where data was obtained, if applicable (e.g., download or api base url)
// Do not include filename if this is a single file, just the directory
$dataUrl="http://sftp.kew.org/pub/data-repositories/WCVP";	

// The full data url, including fill if applicable
// Not currently displayed
$dataUrl="http://sftp.kew.org/pub/data-repositories/WCVP/wcvp.zip";	

// Url where logo for this source can be directly accessed
// For display on TNRS website
$logoUrl="https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2021/07/kew_logo.png";	

// base url for species and infraspecies
$base_url_species="https://powo.science.kew.org/taxon/urn:lsid:ipni.org:names:";

// base url for families and genera with known families
$base_url_gen_fam = "";

// base url for general searches and unassessed genera without families
$base_url_general_search = "https://wcvp.science.kew.org/search?q=";

// date of access of raw data
// MUST by MySQL format date: yyyy-mm-dd
$dateAccessed="2024-01-08";	

// Version for this data source, as assigned by original data provider
// Set to empty string ("") if unavailable or not applicable
$sourceVersion="12";

// Version release date
// Date of release of this source by the original provider
// MUST use MySQL date format: yyyy-mm-dd
// Set to empty string ("") if unavailable or not applicable
$sourceReleaseDate="2023-09-28";

// NO LONGER USED
// KEEP FOR NOW UNTIL I REMOVE THIS COLUMN AND ALL REFERENCES FROM DB
// Use as default classification for building taxamatch tables
// If you set this to true, all other sources will be
// set to false
$is_default=false;	

// Set to 1 if there are any issues/warnings associated with this database
// For now the further details of the warning are handled by the ui; may
// eventually add those details to the db
$source_warning=0;

// Use this source as higher classification for all names in database?
// If true, all names in database will be joined by genus (or failing genus, by family)
// to higher taxonomic categories (genus and above) for this source
// Core database can hold multiple higher classifications;
// therefore will not affect existing classification systems.
$is_higher_classification=true;

// If true, for infraspecific taxa without a parent species,
// will extract distinct species names from genus 
// and specificEpithet columns and add as separate taxa,
// linking orphan infraspecific taxa to the species. 
// Set to false if genera are already present in raw data as
// separate rows.
$extract_species=true;

// If true, will extract distinct genus names from genus column
// and add as separate taxa and link species to the genera. 
// Set to false if genera are already present in raw data as
// separate rows. 
$extract_genera=false;

// If true, will extract distinct family names from family column
// and add as separate taxa and link genera to familes.
// Set to false if family are already present in raw data as
// separate rows.
$extract_families=true;

// Replace previous records for this source?
// VERY IMPORTANT
// Set=true to replace all previous records for this source.
// Set=false to keep existing records (name+author) and add new records only.
$replace=true;

// Repair extended character codes, converting to utf8?
// Set=true if authority field contains extended character set (accented) 
// characters that are not being rendered correctly.
// Only set to false if you are sure this data source contains only 
// utf8 characters
// WFO: note response to unix file command:
// classification.txt: UTF-8 Unicode text, with very long lines, with CRLF line terminators
// However, accents are not being rendered correctly in MySQL UTF-8
// tables. Investigate...
$fix_chars=false;

// set true to delete raw data tables when finished
$remove_raw_tables=true;

// Set to true to convert characters to UTF-8 for this source, else false.
// Normally this is done in staging table, but set this param to true
// if need UTF-8 conversion to perform source-specific corrections
// Setting this param to false will turn off conversion in staging table
// Corrections are performed on DWC-format raw data table
// See script 'fix_character_set.inc'
$fix_chars_curr_source=false;

// IMPORTANT!
// Set to TRUE to infer immediate parent taxon of names with no parentID
$infer_parent_this_source=TRUE;

// IMPORTANT!
// SQL WHERE clause for filtering out taxa for which you do NOT want to infer
// higher taxa. If you want to infer higher taxa for all names missing a 
// parent taxon, then set this value to empty string ("").
// Otherwise, include values of taxonomicStatus which you wishe to exclude,
// and begin with " AND ". For example:
// " AND taxonomicStatus='synonym' "
// Only used if $infer_parent_this_source=TRUE;
$SQL_WHERE_INFER_PARENT_POLICY=" AND taxonomicStatus NOT IN ('Unplaced', 'Synonym', 'Illegitimate', 'Invalid') ";
// As above, but table to be updated has alias 'a'
$SQL_WHERE_INFER_PARENT_POLICY_WITH_ALIAS=" AND a.taxonomicStatus NOT IN ('Unplaced', 'Synonym', 'Illegitimate', 'Invalid') ";

$SQL_WHERE_INFER_PARENT_POLICY="";
// As above, but table to be updated has alias 'a'
$SQL_WHERE_INFER_PARENT_POLICY_WITH_ALIAS="";


/////////////////////////////////////////////////////////////////////////////
// Path and name(s) of raw data file(s)
// Recommend you use subdirectory data/ in this directory
// Variable $src_dir set in load_tnrs.php
/////////////////////////////////////////////////////////////////////////////

// Path to data file
$filepath = $src_dir."data/";	// old version; data inside app/repo directory
$filepath = $DATA_DIR."/".$src."/";	// data outside app/repo directory

// Name of raw data files you will be importing
$namesfile = "wcvp_names.csv";
//$namesfile = "wcvp_names_sample.csv";

// path + file
$namesfileandpath = $filepath.$namesfile;

// names of destination mysql table
$tbl_names_raw=$src . '_raw';

/////////////////////////////////////////////////////////////////////////////
// MySQL LOAD DATA INFILE parameters
// Set any variable to empty string to remove entirely
/////////////////////////////////////////////////////////////////////////////

// Local keyword; essential if importing file on localhost
$local = " LOCAL ";

// Field separator(s)
//$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
$fields_terminated_by = " FIELDS TERMINATED BY '|' ";

// Is text optional surrounded by quotes, etc?
//$optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  
$optionally_enclosed_by = "";

$escaped_by = '';	// Generally this is what you want if CSV
//$escaped_by = " ESCAPED BY '' ";	// double quotes indicated by doubled-double quotes

// Line terminator
//$lines_terminated_by = " LINES TERMINATED BY '\n' ";		// unix
//$lines_terminated_by = " LINES TERMINATED BY '\r' ";		// legacy mac
$lines_terminated_by = " LINES TERMINATED BY '\r\n' ";	// windows

// Set to ignore header line if present
$ignore_lines = " IGNORE 1 LINES ";	// Ignore header line?
//$ignore_lines = " ";	// Ignore header line?

?>
