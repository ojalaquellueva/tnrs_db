<?php

/////////////////////////////////////////////////////
// Corrects source-specific errors
/////////////////////////////////////////////////////

echo "Correcting source-specific errors...";
$sql="

-- Update conserved families
-- e.g., 'Compositae' --> 'Asteraceae'
-- In family field only, scientificName is correct
-- Remove publication information as possibly not 
-- application to this name
UPDATE $tbl_names_raw
SET family=scientificName,
scientificNameAuthorship=NULL,
namePublishedIn=NULL,
`references`=NULL
WHERE taxonRank='family' AND scientificName<>family
;

-- Bad entry, no children so deleting won't hurt
DELETE FROM $tbl_names_raw
WHERE scientificName='Hymenophyllum racib.'
;

-- Purge non-ascii character in 'Microtea subg.Â Schollera'
-- Only one record using wildcard search
UPDATE $tbl_names_raw
SET scientificName='Microtea subg. Schollera'
WHERE scientificName like 'Microtea subg.%Schollera'
;

-- Replace double space with one space
UPDATE $tbl_names_raw
SET scientificName=REPLACE(scientificName,'  ',' ')
WHERE scientificName like '%  %'
;

";
sql_execute_multiple($dbh, $sql);
echo $done;

?>