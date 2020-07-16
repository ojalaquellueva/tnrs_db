<?php

//////////////////////////////////////////////////
// Taxonomy source parameters
//////////////////////////////////////////////////

// Name which uniquely identifies this source within database
// Many operations, including table names, depend on this parameter
// REQUIRED
// MUST BE UNIQUE
// NO SPACES
// MAX 50 characters
$sourceName="tropicos";

// Longer, more descriptive name for source
// Can have spaces; not used in any scripts
// after adding to table `source`
$sourceNameFull="Missouri Botanical Gardens Tropicos database";

// Primary url for this source (optional)
$sourceUrl="http://services.tropicos.org/";	

// date of access of raw data
// MUST by MySQL format date: yyyy-mm-dd
$dateAccessed="2014-12-19";
$dateAccessed="2020-05-30";

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
$is_default=true;	

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

//////////////////////////////////////////////////
// Raw data file parameters
//////////////////////////////////////////////////
// Names of files you will be importing
// Include path to file in name if not in same directory as this script

$filepath = $src_dir."data/";	// old version; data inside app/repo directory
$filepath = $DATA_DIR."/".$src."/";	// data outside app/repo directory
$path = $filepath;	// Keeping this for backward compatibility

//$namesfile = "mbg_name_20141219.csv";
$namesfile = "tropicos_names_20200530.csv";
//$namesfile = "tropicos_api_pinaceae_example.csv";
//$namesfile = "tropicos_names_20200530_sample.csv";
//$namesfile = "tropicos_names_20200530_sample_small.csv";

$namesfileandpath = $path.$namesfile;

// names of destination mysql table
$tbl_names_raw=$sourceName."_raw";

// Import parameters for text file
// Needed for 'LOAD DATA INFILE' statement
// Set any variable to empty string to remove entirely
$local = " LOCAL ";	// LOCAL keyword
$fields_terminated_by = " FIELDS TERMINATED BY ',' ";
// $fields_terminated_by = " FIELDS TERMINATED BY '\t' ";
$optionally_enclosed_by = " OPTIONALLY ENCLOSED BY '\"' ";  // use if text surrounded by quotes
//$optionally_enclosed_by = "";
$escaped_by = "";
$lines_terminated_by = " LINES TERMINATED BY '\n' ";
$ignore_lines = " IGNORE 1 LINES ";	// Ignore header line?

////////////////////////////////////////////////////////////////////////////////////


?>
