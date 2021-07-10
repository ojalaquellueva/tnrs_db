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

// Primary information url for this source (e.g. home page)
$sourceUrl="https://www.tropicos.org/";	

// Short single paragraph description of this source, for display on 
// TNRS website on Source page.
// No quotes! If you must include apostrophes (plain single quote) then 
// double them up to avoid crashing the api (e.g., world''s)
$description="The Missouri Botanical Garden\'s Tropicos database links over 1.33M scientific names with over 4.87M specimens and over 685K digital images. The data includes over 150K references from over 52.6K publications offered as a free service to the world\'s scientific community.";

// Url where data was obtained, if applicable (e.g., download or api base url)
$dataUrl="http://services.tropicos.org/";	

// Url where logo for this source can be directly accessed
// For display on TNRS website
$logoUrl="https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2020/10/TropicosLogo.gif";	

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

//$namesfile = "tropicos_api_pinaceae_example.csv";
$namesfile = "tropicos_names_20210418.csv";
$namesfile = "tropicos_names_20210418_sample.csv";
$namesfile = "tropicos_names_20210418_sample_small.csv";

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
