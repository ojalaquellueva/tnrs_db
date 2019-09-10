<?php

//////////////////////////////////////////////////////////////
// Populates missing families
//
// These probably arise because families are assigned
// according the one of the two classification source
// (tropicos or ncbi) by joining on genus. If a genus
// is missing from either or both of the sources, it
// will not be assigned a family
// The approach used here is to assign the family used by
// the original source
//////////////////////////////////////////////////////////////

echo "Assigning missing families:\r\n";

echo "  tpl...";
$sql="
UPDATE source s JOIN name_source ns JOIN name n JOIN higherClassification h
ON s.sourceID=ns.sourceID AND ns.nameID=n.nameID AND n.nameID=h.nameID
SET h.family='Fabaceae'
WHERE s.sourceName='ildis' 
;

UPDATE source s JOIN name_source ns JOIN name n JOIN higherClassification h
ON s.sourceID=ns.sourceID AND ns.nameID=n.nameID AND n.nameID=h.nameID
SET h.family='Asteraceae'
WHERE s.sourceName='gcc' 
;

";
sql_execute_multiple($dbh, $sql);
echo $done;







?>