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
$sourceNameFull="World Flora Online";

// Primary url for this source (optional)
$sourceUrl="http://www.worldfloraonline.org/";	

// Short single paragraph description of this source, for display on 
// TNRS website on Source page.
// No quotes! If you must include apostrophes (plain single quote) then 
// double them up to avoid crashing the api (e.g., world''s)
$description="The World Flora Online will be an open-access, Web-based compendium of the world’s plant species. It will be a collaborative, international project, building upon existing knowledge and published floras, checklists and revisions but will also require the collection and generation of new information on poorly know plant groups and plants in unexplored regions.";

// Url where data was obtained, if applicable (e.g., download or api base url)
$dataUrl="http://104.198.143.165/files/WFO_Backbone/_WFOCompleteBackbone/WFO_Backbone.zip";	

// Url where logo for this source can be directly accessed
// For display on TNRS website
$logoUrl="https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2021/07/wfo_logo.jpeg";	
$logoUrlFull="https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2021/07/wfo_logo_full.png";

// base url for species and infraspecies
$base_url_species="http://www.worldfloraonline.org/taxon/";

// base url for families and genera with known families
$base_url_gen_fam = "http://www.worldfloraonline.org/taxon/";

// base url for general searches and unassessed genera without families
$base_url_general_search = "http://www.worldfloraonline.org/search?query=";

// date of access of raw data
// MUST by MySQL format date: yyyy-mm-dd
$dateAccessed="2021-07-07";	

// Version for this data source, as assigned by original data provider
// Set to empty string ("") if unavailable or not applicable
$sourceVersion="v.2019.05";

// Version release date
// Date of release of this source by the original provider
// MUST by MySQL format date: yyyy-mm-dd
// Set to empty string ("") if unavailable or not applicable
$sourceReleaseDate="2019-05-17";

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
$extract_families=false;

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
$fix_chars=true;

// set true to delete raw data tables when finished
$remove_raw_tables=false;

/////////////////////////////////////////////////////////////////////////////
// Path and name(s) of raw data file(s)
// Recommend you use subdirectory data/ in this directory
// Variable $src_dir set in load_tnrs.php
/////////////////////////////////////////////////////////////////////////////

// Path to data file
$filepath = $src_dir."data/";	// old version; data inside app/repo directory
$filepath = $DATA_DIR."/".$src."/";	// data outside app/repo directory

// Name of raw data files you will be importing
$namesfile = "classification.txt";
$namesfile = "classification_sample.txt";

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
$fields_terminated_by = " FIELDS TERMINATED BY '\t' ";

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
