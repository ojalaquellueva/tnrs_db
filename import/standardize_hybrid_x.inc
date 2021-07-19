<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// This version changes hybrid x from "x" to plain ascii "x".
// Not appropriate for sources that use regular 'x', although
// these generally don't need correcting as they follow the same
// convention as TNRS. TNRS uses plain x followed by space in 
// all cases.
// This standardization inserts space after the hybrid 'x' to
// avoid confusion with genus or epithet string starting 
// with 'x'.
/////////////////////////////////////////////////////////////////

echo "Standardizing hybrid 'x'...";
$sql="
-- Put space after '×' not followed by space
UPDATE `$tbl_names_raw` 
SET scientificName=REPLACE(scientificName, '×', '× ')
WHERE scientificName LIKE '%×%' AND scientificName NOT LIKE '%× %'
;

-- The next two remove double spaces if any
UPDATE `$tbl_names_raw` 
SET scientificName=REPLACE(scientificName, '  ', ' ')
WHERE scientificName LIKE '%  %' 
;
UPDATE `$tbl_names_raw` 
SET scientificName=REPLACE(scientificName, '  ', ' ')
WHERE scientificName LIKE '%  %' 
;

-- Substitute 'x' for '×'
UPDATE `$tbl_names_raw` 
SET scientificName=REPLACE(scientificName, '×', 'x')
WHERE scientificName LIKE '%×%' 
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>