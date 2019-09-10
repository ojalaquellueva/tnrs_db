<?php

//////////////////////////////////////////////
// Populates name url for any new taxa added
//////////////////////////////////////////////

echo "Populating name urls...";
$sql="
UPDATE `$tbl_names_raw` 
SET taxonUri=
CASE
WHEN rank='family' THEN CONCAT('$base_url_general_search',family)
WHEN rank='genus' THEN CONCAT('$base_url_general_search',genus)
WHEN rank IN ('species','subspecies','variety','forma') THEN CONCAT('$base_url_general_search',genus,'+',specificEpithet)
ELSE NULL
END
WHERE taxonUri IS NULL;
";
sql_execute_multiple($dbh, $sql);
echo $done;


?>