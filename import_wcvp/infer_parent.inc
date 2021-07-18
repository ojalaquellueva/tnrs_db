<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Infer missing parent-child links
/////////////////////////////////////////////////////////////////

echo "Inferring parent-child links for infraspecific taxa...";

// The following will arbitrarily link to a parent species if
// >1 parent. This ensures that the name gets assigned
// to a hierarchy of species, genus, family, while ignoring
// authors: essential for building the fuzzy matching (taxamatch)
// tables. This is OK because the TNRS does not expose the 
// authorities of higher taxa
$sql="
-- infraspecific taxa with a family
UPDATE $tbl_names_raw AS a JOIN $tbl_names_raw AS b
ON a.family=b.family AND a.genus=b.genus AND a.specificEpithet=b.specificEpithet
SET a.parentNameID=b.nameID
WHERE a.parentNameID IS NULL
AND a.rank IN ('forma','subspecies','variety')
AND b.rank='species'
$SQL_WHERE_INFER_PARENT_POLICY_WITH_ALIAS
;

-- infraspecific taxa not assigned to family
UPDATE $tbl_names_raw AS a JOIN $tbl_names_raw AS b
ON a.genus=b.genus AND a.specificEpithet=b.specificEpithet
SET a.parentNameID=b.nameID
WHERE a.parentNameID IS NULL
AND a.rank IN ('forma','subspecies','variety')
AND b.rank='species'
AND a.family IS NULL AND b.family IS NULL
$SQL_WHERE_INFER_PARENT_POLICY_WITH_ALIAS
;

-- the remainder, joining to accepted species
UPDATE $tbl_names_raw AS a JOIN $tbl_names_raw AS b
ON a.genus=b.genus AND a.specificEpithet=b.specificEpithet
SET a.parentNameID=b.nameID
WHERE a.parentNameID IS NULL
AND a.rank IN ('forma','subspecies','variety')
AND b.rank='species'
AND b.taxonomicStatus='Accepted'
$SQL_WHERE_INFER_PARENT_POLICY_WITH_ALIAS
;

-- the remainder, joining to accepted species 
UPDATE $tbl_names_raw AS a JOIN $tbl_names_raw AS b
ON a.genus=b.genus AND a.specificEpithet=b.specificEpithet
SET a.parentNameID=b.nameID
WHERE a.parentNameID IS NULL
AND a.rank IN ('forma','subspecies','variety')
AND b.rank='species'
AND b.taxonomicStatus='Synonym'
$SQL_WHERE_INFER_PARENT_POLICY_WITH_ALIAS
;

-- the remainder, joining to Misapplied 
UPDATE $tbl_names_raw AS a JOIN $tbl_names_raw AS b
ON a.genus=b.genus AND a.specificEpithet=b.specificEpithet
SET a.parentNameID=b.nameID
WHERE a.parentNameID IS NULL
AND a.rank IN ('forma','subspecies','variety')
AND b.rank='species'
AND b.taxonomicStatus='Misapplied'
$SQL_WHERE_INFER_PARENT_POLICY_WITH_ALIAS
;

-- the remainder, joining to 'No opinion'/Unassessed species 
UPDATE $tbl_names_raw AS a JOIN $tbl_names_raw AS b
ON a.genus=b.genus AND a.specificEpithet=b.specificEpithet
SET a.parentNameID=b.nameID
WHERE a.parentNameID IS NULL
AND a.rank IN ('forma','subspecies','variety')
AND b.rank='species'
AND (b.taxonomicStatus='No opinion')
$SQL_WHERE_INFER_PARENT_POLICY_WITH_ALIAS
;

";
sql_execute_multiple($dbh, $sql);
echo $done;	

?>