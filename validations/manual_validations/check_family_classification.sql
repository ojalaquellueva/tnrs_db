-- ---------------------------------------------------
-- Check family classifications for each name source 
-- and classification source
-- ---------------------------------------------------

-- Count names per source
SELECT sourceID, COUNT(DISTINCT n.nameID) AS names
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
GROUP BY sourceID
ORDER BY sourceID
;


-- Display a sample of name classifications
SELECT c.family, n.scientificName
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
LEFT JOIN higherClassification c
ON n.nameID=c.nameID
WHERE ns.sourceID=1
AND c.classificationSourceID=1
limit 12
;

-- Display count of names under each family
-- Check especially for null family
-- Adjust values of sourceID and classificationSourceID as needed
SELECT `source`, classificationSource, family, count(*) FROM (
SELECT s.sourceName as `source`, s2.sourceName as classificationSource, c.family, n.scientificName
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN source s
ON ns.sourceID=s.sourceID
LEFT JOIN higherClassification c
ON n.nameID=c.nameID
LEFT JOIN source s2
ON c.classificationSourceID=s2.sourceID
WHERE ns.sourceID=3
AND c.classificationSourceID=2
) a
GROUP BY `source`, classificationSource, family
ORDER BY `source`, classificationSource, family
;

-- Just check NULL family
SELECT `source`, classificationSource, family, count(*) FROM (
SELECT s.sourceName as `source`, s2.sourceName as classificationSource, c.family, n.scientificName
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN source s
ON ns.sourceID=s.sourceID
LEFT JOIN higherClassification c
ON n.nameID=c.nameID
LEFT JOIN source s2
ON c.classificationSourceID=s2.sourceID
WHERE ns.sourceID=2
AND c.classificationSourceID=2
) a
WHERE family IS NULL
GROUP BY `source`, classificationSource, family
ORDER BY `source`, classificationSource, family
;

-- Show examples where family is null
SELECT c.family, n.scientificName, n.scientificNameAuthorship as author
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
LEFT JOIN higherClassification c
ON n.nameID=c.nameID
WHERE ns.sourceID=1
AND c.classificationSourceID=1
AND family IS NULL
limit 12
;

--
-- Use classification table instead to check NULL family
--
SELECT `source`, family, count(*) FROM (
SELECT s.sourceName as `source`, c.family, n.scientificName
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN source s
ON ns.sourceID=s.sourceID
LEFT JOIN classification c
ON n.nameID=c.nameID AND ns.sourceID=c.sourceID
WHERE ns.sourceID=3
) a
WHERE family IS NULL
GROUP BY `source`, family
ORDER BY `source`, family
;



-- Get accepted name and ID of synonym names without families
SELECT h.family, n.scientificName, n.scientificNameAuthorship as author, syn.acceptance, syn.acceptedNameID
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN synonym syn
ON ns.nameID=syn.nameID AND ns.sourceID=syn.sourceID
LEFT JOIN higherClassification h
ON n.nameID=h.nameID
WHERE ns.sourceID=1
AND h.classificationSourceID=1
AND family IS NULL
AND syn.acceptance='Synonym'
limit 12
;
-- Get accepted name and ID of synonym names without families
SELECT syn.acceptance, COUNT(*) AS names_with_null_family
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN synonym syn
ON ns.nameID=syn.nameID AND ns.sourceID=syn.sourceID
LEFT JOIN higherClassification h
ON n.nameID=h.nameID
WHERE ns.sourceID=1
AND h.classificationSourceID=1
AND family IS NULL
GROUP BY syn.acceptance
;

-- Check accepted family of synonym names without family
SELECT hsyn.family, n.scientificName, n.scientificNameAuthorship as author, syn.acceptance, syn.acceptedNameID, hacc.family
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN synonym syn
ON ns.nameID=syn.nameID AND ns.sourceID=syn.sourceID
LEFT JOIN higherClassification hsyn
ON n.nameID=hsyn.nameID
LEFT JOIN higherClassification hacc
ON syn.acceptedNameID=hacc.nameID 
WHERE ns.sourceID=1
AND hsyn.classificationSourceID=1
AND hsyn.family IS NULL
AND syn.acceptance='Synonym'
limit 12
;






