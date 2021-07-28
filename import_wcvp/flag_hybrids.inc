<?php

/////////////////////////////////////////////////////////////////
// Flags hybrids by populating columns genusHybridMarker and
// speciesHybridMarker based on scientificName
// Handles hybrid symbols utf8 character 195 or plain ascii 'x'
/////////////////////////////////////////////////////////////////

echo "Flagging hybrids:\n";

echo "  Hybrid genera...";
$sql="
UPDATE `$tbl_names_raw`
SET genusHybridMarker='x'
WHERE ascii(strSplit(scientificName,' ',1))=195
OR scientificName LIKE 'x %'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Hybrid species...";
$sql="
UPDATE `$tbl_names_raw`
SET speciesHybridMarker='x'
WHERE ascii(strSplit(scientificName,' ',2))=195
OR scientificName LIKE '% x %'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>