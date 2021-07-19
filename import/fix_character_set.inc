<?php

/////////////////////////////////////////////////////////////
// Fix non-ascii characters, setting to UTF-8
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// This is a source-specific correction. To save time, set 
// parameter $fld_array to include only fields which can
// contain non-ascii characters
/////////////////////////////////////////////////////////////

///////////////////////////////////
// Parameters
///////////////////////////////////


// Set fields to correct
// List all fields that could possibly contain
// non-ascii characters, including hybrid '×'
$fix_chars_fld_array=array(
	"scientificName",
	"scientificNameAuthorship",
	"specificEpithet",
	"infraspecificEpithet"
);

///////////////////////////////////
// Main
///////////////////////////////////

if ($fix_chars_curr_source==true) {
	echo "Converting to utf8:\r\n";
	$tbl = $tbl_names_raw; 

	foreach ($fix_chars_fld_array as $fld) {
		convert_fld_utf8($dbh,$tbl,$fld);
	}
}

?>