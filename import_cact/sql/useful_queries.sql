-- Queries on cact_raw before conversion to dwc

SELECT 
CONCAT(LEFT(nameID,5), '[...]', RIGHT(nameID,5)) AS nameID, 
CONCAT(LEFT(accNameID,5), '[...]', RIGHT(accNameID,5)) AS accNameID, 
CONCAT(LEFT(parentNameID,5), '[...]', RIGHT(parentNameID,5)) AS parentNameID, 
REPLACE(treeIndex, '#t42#33819#33820#33837#', 'root#') AS treeIndex,
LEFT(name,25) as name, LEFT(author,24) as auth, `rank`, taxonomicStatus as status 
FROM cact_raw 
WHERE treeIndex LIKE '#t42#33819#33820#33837#33839#136#%' 
ORDER BY treeIndex 
LIMIT 45 
OFFSET 15
;


SELECT 
CONCAT(LEFT(nameID,5), '[...]', RIGHT(nameID,5)) AS nameID, 
CONCAT(LEFT(accNameID,5), '[...]', RIGHT(accNameID,5)) AS accNameID, 
CONCAT(LEFT(parentNameID,5), '[...]', RIGHT(parentNameID,5)) AS parentNameID, 
treeIndex,
parentTreeIndex,
LEFT(name,25) as name, LEFT(author,24) as auth, `rank`, taxonomicStatus as status 
FROM cact_raw 
LIMIT 12
;


SELECT 
CONCAT(LEFT(nameID,5), '[...]', RIGHT(nameID,5)) AS nameID, 
CONCAT(LEFT(accNameID,5), '[...]', RIGHT(accNameID,5)) AS accNameID, 
CONCAT(LEFT(parentNameID,5), '[...]', RIGHT(parentNameID,5)) AS parentNameID, 
treeIndex,
parentTreeIndex,
LEFT(name,25) as name, LEFT(author,24) as auth, `rank`, taxonomicStatus as status 
FROM cact_raw 
WHERE treeIndex LIKE 'root#33839#136#%' 
ORDER BY treeIndex 
LIMIT 45 
OFFSET 15
;

-- Queries on cact_raw after conversion to dwc
SELECT 
CONCAT(LEFT(nameID_char,5), '[...]', RIGHT(nameID,5)) AS nameID_char, 
CONCAT(LEFT(acceptedNameID_char,5), '[...]', RIGHT(acceptedNameID_char,5)) AS acceptedNameID_char, 
CONCAT(LEFT(parentNameID_char,5), '[...]', RIGHT(parentNameID_char,5)) AS parentNameID_char, 
LEFT(scientificName,25) as scientificName, 
LEFT(scientificNameAuthorship,24) as auth, 
`rank`, 
taxonomicStatus as status 
FROM cact_raw 
LIMIT 12
;

SELECT 
nameID,
acceptedNameID,
parentNameID,
CONCAT(LEFT(nameID_char,5), '[...]', RIGHT(nameID,5)) AS nameID_char, 
CONCAT(LEFT(acceptedNameID_char,5), '[...]', RIGHT(acceptedNameID_char,5)) AS acceptedNameID_char, 
CONCAT(LEFT(parentNameID_char,5), '[...]', RIGHT(parentNameID_char,5)) AS parentNameID_char, 
LEFT(scientificName,25) as scientificName, 
LEFT(scientificNameAuthorship,24) as auth, 
`rank`, 
taxonomicStatus as status 
FROM cact_raw 
LIMIT 12
;

SELECT 
nameID,
acceptedNameID,
parentNameID,
CONCAT(LEFT(nameID_char,5), '[...]', RIGHT(nameID,5)) AS nameID_char, 
CONCAT(LEFT(acceptedNameID_char,5), '[...]', RIGHT(acceptedNameID_char,5)) AS acceptedNameID_char, 
CONCAT(LEFT(parentNameID_char,5), '[...]', RIGHT(parentNameID_char,5)) AS parentNameID_char, 
LEFT(scientificName,25) as scientificName, 
LEFT(scientificNameAuthorship,24) as auth, 
`rank`, 
taxonomicStatus as status 
FROM cact_raw 
LIMIT 12
OFFSET 500
;

