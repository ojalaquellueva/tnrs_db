<?php

//////////////////////////////////////////////
// Populates name url for any new taxa added
//////////////////////////////////////////////

echo "Populating name urls...";
$sql="
UPDATE `$tbl_names_raw` 
SET taxonUri=
CASE
WHEN `taxonomicStatus` IN ('Accepted','Invalid','No opinion') THEN CONCAT(
	'$base_url_species', `nameID_char`
	)
WHEN `taxonomicStatus`='Synonym' THEN CONCAT(
	'$base_url_species', `acceptedNameID_char`, 
	'$base_url_syn_pt1', `nameID_char`, 
	'$base_url_syn_pt2', `nameID_char`, 
	'$base_url_syn_pt3', `nameID_char`
	)
ELSE NULL
END
WHERE nameID_char IS NOT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>