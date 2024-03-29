<?php
// alter params.inc to turn this on
// should convert any improper characters sets  to utf-8
// To save time, works only on the author column, which 
// is the only field likely to contain extended characters
// Will skip this step if characters already converted for
// during raw data standardization (in which case, parameter
// $fix_chars_curr_source will be TRUE).

if ($fix_chars==true && $fix_chars_curr_source==false) {
	echo "  Converting utf8 & ascii codes:\r\n";
 	
 	$tbl = $tbl_staging; 
 
 	// Just fix author unless set otherwise in 
 	// source-specific parameters
 	if (!isset($fix_chars_auth_only)) $fix_chars_auth_only=true;
	
	if ($fix_chars_auth_only) {
		$fld_array = array(
			'scientificNameAuthorship'
		);
	} else {
		$fld_array = array(
			'scientificName',
			'scientificNameAuthorship',
			'nameRank',
			'rankIndicator'			
		);
	}

	foreach ($fld_array as $fld) {
		convert_fld_utf8($dbh, $tbl,$fld);
	}
}

?>
