<?php

/////////////////////////////////////////////////////////////////
// Standardize rank names and indicators
/////////////////////////////////////////////////////////////////

echo "Standardizing rank names:\r\n";

echo "  Setting lower case...";
$sql="
UPDATE `$tbl_names_raw` 
SET `rank`=LOWER(`rank`)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Standardizing rank names...";
$sql="
UPDATE `$tbl_names_raw` 
SET `rank`=
CASE
WHEN `rank`='sp.' THEN 'species'
WHEN `rank`='subsp.' OR `rank`='subsp' THEN 'subspecies'
WHEN `rank`='var.' OR `rank`='var' THEN 'variety'
WHEN `rank`='f.' OR `rank`='form' THEN 'forma'
WHEN `rank`='form' OR `rank`='form' THEN 'forma'
WHEN `rank`='subform' THEN 'subforma'
WHEN `rank`='notoform' THEN 'notoforma'
WHEN `rank`='infraspecificname' THEN 'other infraspecific'
WHEN `rank`='section bot.' THEN 'section'
WHEN `rank`='subsection bot.' THEN 'subsection'
WHEN `rank`='species aggregate' THEN 'species complex'
ELSE `rank`
END
;	
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Populating rank indicators for explicit ranks...";
// ELSE not needed as rankIndicator starts our NULL
$sql="
UPDATE `$tbl_names_raw` 
SET infraspecificRank=
CASE
WHEN `rank`='subspecies' THEN 'subsp.'
WHEN `rank`='variety' THEN 'var.'
WHEN `rank`='subvariety' THEN 'subvar.'
WHEN `rank`='forma' THEN 'fo.'
WHEN `rank`='subforma' THEN 'subfo.'
ELSE NULL
END
;	
";
sql_execute_multiple($dbh, $sql);
echo $done;

/* NOT NEEDED FOR THIS SOURCE
echo "Parsing rank indicators for 'other infraspecific':\r\n";

echo "  Hybrids...";
// ELSE not needed as rankIndicator starts our NULL
$sql="
UPDATE `$tbl_names_raw` 
SET infraspecificRank=strSplit(scientificName, ' ', 4)
WHERE `rank`='other infraspecific'
AND (
speciesHybridMarker IS NOT NULL OR genusHybridMarker IS NOT NULL
)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Non-hybrids...";
$sql="
UPDATE `$tbl_names_raw` 
SET infraspecificRank=strSplit(scientificName, ' ', 3)
WHERE `rank`='other infraspecific' 
AND infraspecificRank IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Standardizing rank indicators:\r\n";

echo "  Column `infraspecificRank`...";
$sql="
-- Atomic rank indicator
-- Rank indicators for taxa above rank of subspecies set to NULL
UPDATE `$tbl_names_raw` 
SET infraspecificRank=
CASE
WHEN infraspecificRank='sect.' THEN NULL
WHEN infraspecificRank='subg.' THEN NULL
WHEN infraspecificRank='sp.' THEN NULL
WHEN infraspecificRank='var' THEN 'var.'
WHEN infraspecificRank='nothosubsp' THEN 'nothosubsp.'
WHEN infraspecificRank='f.' THEN 'fo.'
WHEN infraspecificRank='nothof.' THEN 'nothofo.'
WHEN infraspecificRank='subf.' THEN 'subfo.'
WHEN infraspecificRank='cultivar.' THEN 'cv.'
ELSE infraspecificRank
END
;	
UPDATE `$tbl_names_raw` 
SET `rank`='nothospecies',
infraspecificRank=NULL
WHERE infraspecificRank='nothospecies'
;
-- Next one catches special cases such as species 'Orobanche mutelii f.'
UPDATE `$tbl_names_raw` 
SET infraspecificRank=NULL,
infraspecificEpithet=NULL
WHERE `rank` IN (
'family','genus','nothospecies','order','phylum','section','species','subgenus'
)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;
*/

// IMPORTANT!
// All infraspecific rank indicators standardized in the previous 
// step MUST be standardized here as well
// ALSO: Recommend searching for all distinct tokens containing 
// period ('.') in case other abbreviations not listed in column
// infraspecificRank are embedded in full scientific names 
//echo "  Rank indicators in scientific names...";
echo "Standardizing rank indicators inside scientific names...";
$sql="
UPDATE `$tbl_names_raw`
SET scientificName=REPLACE(scientificName,' var ',' var. ')
WHERE scientificName LIKE '% var %'
;
UPDATE `$tbl_names_raw`
SET scientificName=REPLACE(scientificName,' f. ',' fo. ')
WHERE scientificName LIKE '% f. %'
;
UPDATE `$tbl_names_raw`
SET scientificName=REPLACE(scientificName,' subf. ',' subfo. ')
WHERE scientificName LIKE '% subf. %'
;
UPDATE `$tbl_names_raw`
SET scientificName=REPLACE(scientificName,' cultivar. ',' cv. ')
WHERE scientificName LIKE '% cultivar. %'
;
UPDATE `$tbl_names_raw` 
SET scientificName=REPLACE(scientificName,' nothosubsp ',' nothosubsp. '),
infraspecificRank='nothosubsp.'
WHERE infraspecificRank='nothosubsp'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Populating missing infraspecificRank...";
$sql="
UPDATE `$tbl_names_raw` 
SET infraspecificRank='subsp.'
WHERE `rank`='subspecies' and infraspecificRank is null
;
UPDATE `$tbl_names_raw` 
SET infraspecificRank='fo.'
WHERE `rank`='forma' and infraspecificRank is null
;
UPDATE `$tbl_names_raw` 
SET infraspecificRank='var.'
WHERE `rank`='variety' and infraspecificRank is null
;
UPDATE `$tbl_names_raw` 
SET infraspecificRank='subvar.'
WHERE `rank`='subvariety' and infraspecificRank is null
;

";
sql_execute_multiple($dbh, $sql);
echo $done;

?>