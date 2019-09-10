<?php

/////////////////////////////////////////////////////
// Corrects source-specific errors
/////////////////////////////////////////////////////

echo "Correcting source-specific errors...";
$sql="
UPDATE $tbl_names_raw
SET
infraspecificRank='var.',
infraspecificEpithet='schneideri'
WHERE infraspecificRank='var. schneideri'
;
UPDATE $tbl_names_raw
SET
assignedFamilyText='Dryopteridaceae'
WHERE assignedFamilyText='Dryopteridacae'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>