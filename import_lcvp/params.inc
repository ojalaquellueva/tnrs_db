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
$sourceName="lcvp";

// Longer, more descriptive name for source
// Can have spaces; not used in any scripts
// after adding to table `source`
$sourceNameFull="Leipzig Catalogue of Vascular Plants";

// Primary url for this source (optional)
$sourceUrl="https://www.nature.com/articles/s41597-020-00702-z";	

// Short single paragraph description of this source, for display on 
// TNRS website on Source page. Escape (\) embedded quotes!
$description="The Leipzig Catalogue of Vascular Plants (LCVP) is as far as we know the most updated and resolved list of plant names and their synonyms of all known vascular plant species on this planet.";

// Url where data was obtained, if applicable (e.g., download or api base url)
$dataUrl="https://idata.idiv.de/ddm/Data/ShowData/1806";	

// Url where logo for this source can be directly accessed
// For display on TNRS website
$logoUrl="";	

// date of access of raw data
// MUST by MySQL format date: yyyy-mm-dd
$dateAccessed="2021-04-26";	

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
// Set to false only if certain raw data contain only utf8 characters
$fix_chars=false;

// set true to delete the raw data tables when finished
$remove_raw_tables=true;

/////////////////////////////////////////////////////////////////////////////
// Path and name(s) of raw data file(s)
// Recommend you use subdirectory data/ in this directory
/////////////////////////////////////////////////////////////////////////////

// Path to data file
$filepath = $DATA_DIR."/".$src."/";	// data outside app/repo directory
$path = $filepath;	// Keeping this for backward compatibility


// Name of data file you will be importing
$namesfile = "LCVP_1.02.utf8.txt";
//$namesfile = "LCVP_1.02.utf8_sample.txt";
// $namesfile = "LCVP_1.02.utf8_sample_small.txt";

// path + file
$namesfileandpath = $filepath.$namesfile;

// names of destination mysql table
$tbl_names_raw=$sourceName."_raw";
$tbl_names_raw_dwc=$sourceName."_raw_dwc";

/////////////////////////////////////////////////////////////////////////////
// MySQL LOAD DATA INFILE parameters
// Set any variable to empty string to remove entirely
/////////////////////////////////////////////////////////////////////////////

// Local keyword; essential if importing file on localhost
$local = " LOCAL ";

// Field separator(s)
//$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
$fields_terminated_by = " FIELDS TERMINATED BY '\t' ";

// Is text optional surrounded by quotes, etc?
$optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  
//$optionally_enclosed_by = "";

$escaped_by = "";

// Line terminator
$lines_terminated_by = " LINES TERMINATED BY '\n' ";

// Set to ignore header line if present
$ignore_lines = " IGNORE 1 LINES ";	// Ignore header line?

?>
