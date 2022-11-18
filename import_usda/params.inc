<?php

/////////////////////////////////////////////////////////////////////////////
// Parameters specific to importing raw data from this source,
// used only by import scripts. See also global_params.inc for 
// parameters used by other scripts as well
/////////////////////////////////////////////////////////////////////////////

// Name which uniquely identifies this source within database
// Many operations, including table names, depend on this parameter
// REQUIRED
// MUST BE UNIQUE
// NO SPACES
// MAX 50 characters
$sourceName="usda";

// Longer, more descriptive name for source
// Can have spaces; not used in any scripts
// after adding to table `source`
$sourceNameFull="USDA Plants";

// Primary url for this source (optional)
$sourceUrl="https://plants.sc.egov.usda.gov/java/";

// Short single paragraph description of this source, for display on 
// TNRS website on Source page.
// No quotes! If you must include apostrophes (plain single quote) then 
// double them up to avoid crashing the api (e.g., world''s)
$description="The PLANTS Database provides standardized information about the vascular plants, mosses, liverworts, hornworts, and lichens of the U.S. and its territories.";

// Url where data was obtained, if applicable (e.g., download or api base url)
$dataUrl="http://plants.usda.gov/adv_search.html";	

// Url where logo for this source can be directly accessed
// For display on TNRS website
$logoUrl="";	

// date of access of raw data
// MUST by MySQL format date: yyyy-mm-dd
$dateAccessed="2020-04-25";

// Version for this data source, as assigned by original data provider
// Set to empty string ("") if unavailable or not applicable
$sourceVersion="";

// Version release date
// Date of release of this source by the original provider
// MUST by MySQL format date: yyyy-mm-dd
// Set to empty string ("") if unavailable or not applicable
$sourceReleaseDate="";

// NOT LONGER USED
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
$is_higher_classification=false;

// Replace previous records for this source?
// VERY IMPORTANT
// Set=true to replace all previous records for this source.
// Set=false to keep existing records (name+author) and add new records only.
$replace=true;

// Repair extended character codes, converting to utf8?
// Set=true if authority field contains extended character set (accented) characters
// Only set to false if you are sure this data source contains only utf8 characters
$fix_chars=true;

// set true to delete the raw data tables when finished
$remove_raw_tables=true;

// Set to true to convert characters to UTF-8 for this source, else false.
// Normally this is done in staging table, but set this param to true
// if need UTF-8 conversion to perform source-specific corrections
// Setting this param to false will turn off conversion in staging table
// Corrections are performed on DWC-format raw data table
// See script 'fix_character_set.inc'
$fix_chars_curr_source=false;

/////////////////////////////////////////////////////////////////////////////
// Path and name(s) of raw data file(s)
// Recommend you use subdirectory data/ in this directory
/////////////////////////////////////////////////////////////////////////////

$filepath = $src_dir."data/";	// old version; data inside app/repo directory
$filepath = $DATA_DIR."/".$src."/";	// data outside app/repo directory
$path = $filepath;	// Keeping this for backward compatibility

// Names of files you will be importing
$namesfile = "usda_plants_20210425.csv";
//$namesfile = "usda_plants_20210425_sample_small.csv";
//$namesfile = "usda_plants_20210425_sample.csv";

$namesfileandpath = $filepath.$namesfile;

// names of destination mysql table
$tbl_names_raw=$sourceName."_raw";

// base name search url
// Need to add the taxon symbol 
$name_url_base="https://plants.sc.egov.usda.gov/home/plantProfile?symbol=";

// default url supplied if no symbol for a taxon
$name_url_bad="https://plants.sc.egov.usda.gov/home";

/////////////////////////////////////////////////////////////////////////////
// MySQL LOAD DATA INFILE parameters
// Set any variable to empty string to remove entirely
/////////////////////////////////////////////////////////////////////////////

// Local keyword; essential if importing file on localhost
$local = " LOCAL ";

// Field separator(s)
$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
// $fields_terminated_by = " FIELDS TERMINATED BY '\t' ";

// Is text optional surrounded by quotes, etc?
$optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  
//$optionally_enclosed_by = "";

$escaped_by = "";

// Line terminator
$lines_terminated_by = " LINES TERMINATED BY '\n' ";

// Set to ignore header line if present
$ignore_lines = " IGNORE 1 LINES ";	// Ignore header line?

?>
