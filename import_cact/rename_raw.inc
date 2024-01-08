<?php

/////////////////////////////////////////////////////
// Rename $tbl_names_raw TO $tbl_names_raw_verbatim
// and tbl_names_raw_dwc TO $tbl_names_raw
// From this point on, all import operations are performed
// on the new (DWC) $tbl_names_raw. No further use is made
// of $tbl_names_raw_verbatim, aside from archiving in 
// staging schema, if requested in parameters
/////////////////////////////////////////////////////

echo "Renaming tables...";
$tbl_names_raw_verbatim = $tbl_names_raw . "_verbatim";
$sql="
RENAME TABLE $tbl_names_raw TO $tbl_names_raw_verbatim;
RENAME TABLE $tbl_names_raw_dwc TO $tbl_names_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>