<?php

//////////////////////////////////////////////
// Populates name url for any new taxa added
//////////////////////////////////////////////

echo "Populating name urls...";

/*
$sql="
UPDATE `$tbl_names_raw` 
SET taxonUri=
CONCAT('$base_url_species',IFNULL(`nameID_char`,''))
WHERE nameID_char IS NOT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;
*/
echo "...already done by load_dwc.inc"

?>