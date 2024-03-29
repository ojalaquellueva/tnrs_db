-- -----------------------------------------------------------------------------
-- general counts of records by source
-- -----------------------------------------------------------------------------

-- visually inspect sources
SELECT * 
FROM source;

-- count names per source
SELECT s.sourceID, sourceName, COUNT(*) as names
FROM source s join name_source ns
ON s.sourceID=ns.sourceID
GROUP BY s.sourceID, s.sourceID;

-- count classification events by source
-- should be same as number of names
SELECT sourceID, COUNT(*) as names
FROM classification 
GROUP BY sourceID;

-- count taxonomic opinions
-- these numbers will be <= # of names per source
SELECT sourceID, COUNT(*) as names
FROM synonym 
GROUP BY sourceID;

-- Check for names without entries in table name_source 
-- There shouldn't be any
SELECT COUNT(*) AS names_not_in_name_source
FROM (
SELECT DISTINCT n.nameID
FROM name n LEFT JOIN name_source ns
ON n.nameID=ns.nameID
WHERE ns.nameID IS NULL
) AS a
;

-- ----------------------------------------------------------------------------
-- Check table higherClassification
-- * Gives family classification for each name, according to one or more 
--   sources flagged $is_higher_classification=true in source params file
-- ----------------------------------------------------------------------------

-- Number of classified names by classification source
-- Only sources also listed as classification source should appear here
SELECT s.sourceID, s.sourceName, COUNT(h.nameID) AS names_classified
FROM source s JOIN higherClassification h
ON s.sourceID=h.classificationSourceID
GROUP BY s.sourceID, s.sourceName
;

-- Get counts of unique families
SELECT family, COUNT(*) AS names 
FROM higherClassification
GROUP BY family
ORDER BY family
;

-- Counts of family vs no family
SELECT IF(family IS NULL, "No family", "Has family"),
COUNT(*) AS names 
FROM higherClassification
GROUP BY IF(family IS NULL, "No family", "Has family")
;

-- Browse names without families
-- OK as long as the names are of rank family or higher
SELECT h.classificationSourceID, s.sourceID, s.sourceName, n.scientificName, n.nameRank
FROM source s JOIN higherClassification h
ON s.sourceID=h.classificationSourceID
JOIN name n
ON h.nameID=n.nameID
WHERE h.family IS NULL
LIMIT 25
;

-- List ranks of names with no families
SELECT n.nameRank, COUNT(*) AS names_without_families
FROM source s JOIN higherClassification h
ON s.sourceID=h.classificationSourceID
JOIN name n
ON h.nameID=n.nameID
WHERE h.family IS NULL
GROUP BY n.nameRank
ORDER BY n.nameRank
;

-- List names that should have families
SELECT h.classificationSourceID, s.sourceID, s.sourceName, h.family,
n.nameID, n.scientificName, n.nameRank
FROM source s JOIN higherClassification h
ON s.sourceID=h.classificationSourceID
JOIN name n
ON h.nameID=n.nameID
WHERE h.family IS NULL
AND n.nameRank IN ('forma','genus','Genus','species','subspecies','variety')
ORDER BY n.scientificName
LIMIT 25
;
-- Same, unique genera only
SELECT DISTINCT(n.genus)
FROM source s JOIN higherClassification h
ON s.sourceID=h.classificationSourceID
JOIN name n
ON h.nameID=n.nameID
WHERE h.family IS NULL
AND n.nameRank IN ('forma','genus','Genus','species','subspecies','variety')
ORDER BY n.genus
;

-- Get possible families
SELECT DISTINCT(n.genus), gf.family
FROM source s JOIN higherClassification h
ON s.sourceID=h.classificationSourceID
JOIN name n
ON h.nameID=n.nameID
JOIN gf_lookup gf
ON n.genus=gf.genus
WHERE h.family IS NULL
AND n.nameRank IN ('forma','genus','Genus','species','subspecies','variety')
AND gf.unambiguous=1
ORDER BY n.genus
;

-- Check if any names with families lack family nameID
SELECT COUNT(*) FROM higherClassification
WHERE family IS NOT NULL AND familyNameID IS NULL
;

-- Browse examples of names with family but no family nameID
SELECT * FROM higherClassification
WHERE family IS NOT NULL AND familyNameID IS NULL
LIMIT 25
;

-- List distinct family names where family nameID missing
SELECT classificationSourceID, family, COUNT(*)
FROM higherClassification
WHERE family IS NOT NULL AND familyNameID IS NULL
GROUP BY classificationSourceID, family
;

-- List matches in classification source to families without IDs in
-- higherClassification table
-- Adjust sourceID as needed
SELECT ns.sourceID, n.nameID, 
scientificName AS family, scientificNameAuthorship as author, 
s.acceptance
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN synonym s 
ON n.nameID=s.nameID
WHERE scientificName IN (
SELECT DISTINCT family FROM higherClassification
WHERE family IS NOT NULL AND familyNameID IS NULL
AND classificationSourceID=1
) 
AND ns.sourceID=1
AND s.sourceID=1
ORDER BY scientificName, s.acceptance
;

-- As above, plus accepted family as applicable
SELECT a.sourceID, a.nameID, a.family, a.author as author, a.acceptance, 
n_acc.nameID AS accepted_family_nameID, n_acc.scientificName AS accepted_family, 
n_acc.scientificNameAuthorship as accepted_family_author
FROM (
SELECT ns.sourceID, n.nameID, 
scientificName AS family, scientificNameAuthorship as author, 
s.acceptance, s.acceptedNameID
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN synonym s 
ON n.nameID=s.nameID
WHERE scientificName IN (
SELECT DISTINCT family FROM higherClassification
WHERE family IS NOT NULL AND familyNameID IS NULL
AND classificationSourceID=1
) 
AND ns.sourceID=1
AND s.sourceID=1
) AS a 
LEFT JOIN name n_acc
ON a.acceptedNameID=n_acc.nameID
ORDER BY a.family, a.acceptance
;

-- As above, plus accepted family as applicable
-- Use this to develop update query to fix issue in higherClassification
SELECT a.sourceID, a.nameID, a.family, a.author as author, a.acceptance, 
a.acc_family_nameID, a.acc_family, a.acc_family_author,
IF(acceptance='Accepted', a.nameID, a.acc_family_nameID) AS acc_nameID_final,
IF(acceptance='Accepted', a.family, a.acc_family) AS acc_family_final,
IF(acceptance='Accepted', a.author, a.acc_family_author) AS acc_author_final
FROM (
SELECT a.sourceID, a.nameID, a.family, a.author as author, a.acceptance, 
n_acc.nameID AS acc_family_nameID, n_acc.scientificName AS acc_family, 
n_acc.scientificNameAuthorship as acc_family_author
FROM (
SELECT ns.sourceID, n.nameID, 
scientificName AS family, scientificNameAuthorship as author, 
s.acceptance, s.acceptedNameID
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN synonym s 
ON n.nameID=s.nameID
WHERE scientificName IN (
SELECT DISTINCT family FROM higherClassification
WHERE family IS NOT NULL AND familyNameID IS NULL
AND classificationSourceID=1
) 
AND ns.sourceID=1
AND s.sourceID=1
) AS a 
LEFT JOIN name n_acc
ON a.acceptedNameID=n_acc.nameID
) AS a
ORDER BY a.family, a.acceptance
;


-- ----------------------------------------------------------------------------
-- check for null family in table classification
-- ----------------------------------------------------------------------------

-- check family field in table classification
SELECT IF(family IS NULL,'NULL','Not NULL') AS famIsNull, COUNT(*)
FROM classification c JOIN name n 
ON c.nameID=n.nameID
WHERE nameRank NOT IN ('root','family','class','division','kingdom','order','phylum','subclass','subdivision','subkingdom','suborder','subphylum','superclass','superdivision','superfamily','superorder')
GROUP BY famIsNull;

-- show ranks of name with null family
-- at ranks below family
SELECT nameRank, COUNT(DISTINCT n.nameID) as namesNoFamily
FROM classification c JOIN name n 
ON c.nameID=n.nameID
WHERE c.family IS NULL AND nameRank NOT IN ('root','family','class','division','kingdom','order','phylum','subclass','subdivision','subkingdom','suborder','subphylum','superclass','superdivision','superfamily','superorder')
GROUP BY nameRank;

-- Count names by ranks and source with null family
SELECT sourceName, nameRank, COUNT(DISTINCT n.nameID) as namesNoFamily
FROM classification c JOIN name n JOIN name_source ns JOIN source s
ON c.nameID=n.nameID AND n.nameID=ns.nameID AND ns.sourceID=s.sourceID
WHERE c.family IS NULL AND nameRank NOT IN ('root','family','class','division','kingdom','order','phylum','subclass','subdivision','subkingdom','suborder','subphylum','superclass','superdivision','superfamily','superorder')
AND c.sourceID=s.sourceID
GROUP BY sourceName, nameRank;

-- count names in each source than have no default family under Tropicos
SELECT sourceName, COUNT(DISTINCT n.nameID) AS names
FROM source s JOIN name_source ns JOIN name n JOIN higherClassification h
ON s.sourceID=ns.sourceID AND ns.nameID=n.nameID AND n.nameID=h.nameID
WHERE h.family IS NULL AND h.classificationSourceID=4
AND nameRank NOT IN ('root','family','class','division','kingdom','order','phylum','subclass','subdivision','subkingdom','suborder','subphylum','superclass','superdivision','superfamily','superorder')
GROUP BY sourceName;

-- ----------------------------------------------------------------------------
-- check acceptance codes
-- ----------------------------------------------------------------------------

-- Check acceptance codes
SELECT acceptance, count(*) 
FROM synonym
GROUP BY acceptance;

-- show source and count of names for which no opinion provided
-- in synonym table
-- WARNING will be slow due to left join
SELECT sourceName, COUNT(DISTINCT n.nameID) AS names
FROM source s JOIN name_source ns JOIN name n 
ON s.sourceID=ns.sourceID AND ns.nameID=n.nameID
LEFT JOIN synonym sy
ON n.nameID=sy.nameID
WHERE sy.nameID IS NULL
GROUP BY sourceName;

-- ----------------------------------------------------------------------------
-- check for missing parsed name components
-- ----------------------------------------------------------------------------

-- Check for missing genus
-- ignoring hybrids
SELECT COUNT(*)
FROM name
WHERE genus IS NULL and nameRank='genus'
AND (isHybrid=0 OR isHybrid IS NULL);

-- Check for missing specific epithets
-- ignoring hybrids
SELECT COUNT(*)
FROM name
WHERE specificEpithet IS NULL and nameRank='species'
AND (isHybrid=0 OR isHybrid IS NULL);

-- Check for missing trinomial epithets
-- ignoring hybrids
SELECT COUNT(*)
FROM name
WHERE nameRank<>'species'
AND infraspecificEpithet IS NULL AND scientificName LIKE "% % % %"
AND (isHybrid=0 OR isHybrid IS NULL);

-- Check for missing quadrinomial epithets
-- ignoring hybrids
SELECT COUNT(*)
FROM name
WHERE nameRank<>'species'
AND infraspecificEpithet2 IS NULL AND scientificName LIKE "% % % % % %"
AND (isHybrid=0 OR isHybrid IS NULL);

-- count by source the number of names with missing name components
SELECT sourceName AS source, COUNT(DISTINCT n.nameID) AS names
FROM name n JOIN name_source ns JOIN source s
ON n.nameID=ns.nameID AND ns.sourceID=s.sourceID
WHERE (
(nameRank='genus' AND genus IS NULL) 
OR (nameRank='species' AND (genus IS NULL OR specificEpithet IS NULL)) 
OR (scientificName LIKE "% % % %" AND nameRank<>'species' AND (genus IS NULL OR specificEpithet IS NULL 
OR infraspecificEpithet IS NULL)) 
OR (scientificName LIKE "% % % % % %" AND nameRank<>'species' AND (genus IS NULL OR specificEpithet IS NULL 
OR infraspecificEpithet IS NULL OR infraspecificEpithet2 IS NULL))
) AND 
(isHybrid=0 OR isHybrid IS NULL)
GROUP BY sourceName;

-- ----------------------------------------------------------------------------
-- Check for missing parents in taxamatch tables
-- ----------------------------------------------------------------------------

-- the Poa annua check
-- Poa annua on tropicos has an intervening infrageneric taxon between it and
-- the genus Poa. An error was preventing such species from laoding.
SELECT species_id, genus_id, genus_species 
FROM splist_genlist_combined 
WHERE genus_species LIKE 'Poa ann%';

-- A more detailed check
-- should return same number of records as above
-- Checks species where species source and genus source are the same
SELECT s.sourceName AS speciesSourceName, species_id, genus_id, genus_species, 
s2.sourceName AS genusSourceName 
FROM source s JOIN name_source ns JOIN splist_genlist_combined sg
JOIN name_source ns2 JOIN source s2
ON s.sourceID=ns.sourceID AND ns.nameID=sg.species_id 
AND sg.genus_id=ns2.nameID AND ns2.sourceID=s2.sourceID
AND s.sourceID=s2.sourceID
WHERE genus_species LIKE 'Poa ann%'
ORDER BY s.sourceID;

-- ----------------------------------------------------------------------------
-- Check for names from one source linked only to accepted name in different source
-- Note: this will be very slow for large, multi-source database
-- ----------------------------------------------------------------------------

SELECT syn.sourceName, COUNT(DISTINCT syn.nameID) AS mislinkedNames
FROM 
(
SELECT syn.nameID, syn.sourceID, sourceName
FROM synonym syn JOIN source s
ON syn.sourceID=s.sourceID
WHERE syn.acceptedNameID IS NOT NULL
) AS syn
LEFT JOIN
(
SELECT syn.nameID AS synNameID, syn.sourceID AS synSourceID,
acc.nameID AS accNameID, s.sourceID AS accSourceID, sourceName AS accNameSource
FROM synonym syn JOIN synonym acc JOIN name_source ns JOIN source s
ON syn.acceptedNameID=acc.nameID AND acc.nameID=ns.nameID AND ns.sourceID=s.sourceID
) AS acc
ON syn.nameID=acc.synNameID AND syn.sourceID=acc.synSourceID
WHERE syn.nameID IS NULL;

-- ----------------------------------------------------------------------------
-- Checks for missing parsed name components, as well as anomalies
-- in the column 'nameParts'
-- ----------------------------------------------------------------------------

-- Check nameParts for species
-- Should always=2, never NULL
SELECT nameParts, COUNT(*) AS names
FROM name
WHERE nameRank='species' 
GROUP BY nameParts;

-- Display value(s) of namePart for trinomials
SELECT nameParts, COUNT(*) AS names
FROM name
WHERE (scientificName LIKE "% % % %" AND scientificName NOT LIKE "% % % % % %")
AND nameRank<>'species'
AND (isHybrid=0 OR isHybrid IS NULL) 
GROUP BY nameParts;

-- Display value(s) of namePart for quadrinomials
SELECT nameParts, COUNT(*) AS names
FROM name
WHERE (scientificName LIKE "% % % % % %")
AND nameRank<>'species'
AND (isHybrid=0 OR isHybrid IS NULL) 
GROUP BY nameParts;

-- count trinomials with incorrect nameParts values by sources
SELECT sourceName, COUNT(*) AS trinomials
FROM name n JOIN name_source ns JOIN source s
ON n.nameID=ns.nameID AND ns.sourceID=s.sourceID
WHERE (scientificName LIKE "% % % %" AND scientificName NOT LIKE "% % % % % %")
AND nameRank<>'species'
AND (isHybrid=0 OR isHybrid IS NULL) 
AND nameParts<>3
GROUP BY sourceName
LIMIT 25;

-- count quadrinomials with incorrect nameParts values by sources
SELECT sourceName, COUNT(*) AS quadrinomials
FROM name n JOIN name_source ns JOIN source s
ON n.nameID=ns.nameID AND ns.sourceID=s.sourceID
WHERE (scientificName LIKE "% % % % % %")
AND nameRank<>'species'
AND (isHybrid=0 OR isHybrid IS NULL) 
AND nameParts<>4
GROUP BY sourceName
LIMIT 25;

-- ----------------------------------------------------------------------------
-- Check for duplicate names
-- ----------------------------------------------------------------------------

-- Check for duplicate names by source
-- NOTE: use next version instead
SELECT sourceName, COUNT(*) AS duplicateNames
FROM 
(
SELECT sourceName, nameRank, scientificName, scientificNameAuthorship, COUNT(*) AS names
FROM name n JOIN name_source ns JOIN source s
ON n.nameID=ns.nameID AND ns.sourceID=s.sourceID
GROUP BY sourceName, nameRank, scientificName, scientificNameAuthorship
HAVING names>1
) AS n
GROUP BY sourceName
;

-- As above, but non-null author only
-- This is more appropriate version, as TNRS DB code 
-- Adds canonical name (no author) for each name+author combination
SELECT sourceName, COUNT(*) AS duplicateNames
FROM 
(
SELECT sourceName, nameRank, scientificName, scientificNameAuthorship, COUNT(*) AS names
FROM name n JOIN name_source ns JOIN source s
ON n.nameID=ns.nameID AND ns.sourceID=s.sourceID
WHERE scientificNameAuthorship IS NOT NULL
GROUP BY sourceName, nameRank, scientificName, scientificNameAuthorship
HAVING names>1
) AS n
GROUP BY sourceName
;

-- Single source
-- Modify sourceID as needed
SELECT COUNT(*) AS duplicateNames
FROM 
(
SELECT scientificName, scientificNameAuthorship, COUNT(*) AS names
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
WHERE ns.sourceID=2 AND scientificNameAuthorship IS NOT NULL
GROUP BY scientificName, scientificNameAuthorship
HAVING names>1
) AS n
;


-- ----------------------------------------------------------------------------
-- More specific checks, if errors found by the above queries:
-- ----------------------------------------------------------------------------

-- show by source names with missing name components
SELECT n.nameID, nameRank, scientificName, genus, specificEpithet, infraspecificEpithet,  infraspecificEpithet2
FROM name n JOIN name_source ns JOIN source s
ON n.nameID=ns.nameID AND ns.sourceID=s.sourceID
WHERE (
(nameRank='genus' AND genus IS NULL) 
OR (nameRank='species' AND (genus IS NULL OR specificEpithet IS NULL)) 
OR (scientificName LIKE "% % % %" AND nameRank<>'species' AND (genus IS NULL OR specificEpithet IS NULL 
OR infraspecificEpithet IS NULL)) 
OR (scientificName LIKE "% % % % % %" AND nameRank<>'species' AND (genus IS NULL OR specificEpithet IS NULL 
OR infraspecificEpithet IS NULL OR infraspecificEpithet2 IS NULL))
) 
AND (isHybrid=0 OR isHybrid IS NULL)
AND sourceName="ncbi"
LIMIT 50;

-- inspect names from specific source
-- where family field is NULL in table classification
SELECT n.nameID, nameRank, scientificName
FROM source s JOIN classification c JOIN name n 
ON s.sourceID=c.sourceID AND c.nameID=n.nameID
WHERE family IS NULL AND sourceName='usda'
LIMIT 50;

-- display trinomials with incorrect nameParts by specific source
SELECT sourceName, nameRank, scientificName, genus, specificEpithet, infraspecificEpithet,
infraspecificEpithet2
FROM name n JOIN name_source ns JOIN source s
ON n.nameID=ns.nameID AND ns.sourceID=s.sourceID
WHERE (scientificName LIKE "% % % %" AND scientificName NOT LIKE "% % % % % %")
AND (isHybrid=0 OR isHybrid IS NULL) 
AND nameParts<>3
AND sourceName='ncbi'
LIMIT 20;

-- Examine original anomalous trinomials from tropicos
SELECT nameID, scientificName, genus, specificEpithet, otherEpithet
FROM tropicos_raw
WHERE (scientificName LIKE "% % %")
AND (isHybrid=0 OR isHybrid IS NULL) 
AND (scientificName NOT LIKE "% x" AND scientificName NOT LIKE "% x %")
AND (scientificName LIKE "% var. %" OR scientificName LIKE "% subsp. %")
AND nameRank='species'
LIMIT 25;

-- display quadrinomials with incorrect nameParts by specific source
SELECT sourceName, nameRank, scientificName, genus, specificEpithet, infraspecificEpithet, infraspecificEpithet2
FROM name n JOIN name_source ns JOIN source s
ON n.nameID=ns.nameID AND ns.sourceID=s.sourceID
WHERE (scientificName LIKE "% % % % % %")
AND (isHybrid=0 OR isHybrid IS NULL) 
AND nameParts<>4
AND sourceName='ncbi'
LIMIT 25;

-- search for particular name by genus in all sources
SELECT n.nameID, s.sourceID, sourceName, scientificName, scientificNameAuthorship
FROM source s join name_source ns join name n
ON s.sourceID=ns.sourceID AND ns.nameID=n.nameID
WHERE scientificName LIKE "Zea%"
ORDER BY scientificName, sourceName;

-- count species of Zea in tropicos
SELECT n.nameID, s.sourceID, sourceName, scientificName, scientificNameAuthorship
FROM source s join name_source ns join name n
ON s.sourceID=ns.sourceID AND ns.nameID=n.nameID
WHERE scientificName LIKE "Zea %" AND sourceName="tropicos" AND nameRank="species"
ORDER BY scientificName;

-- Inspect duplicate names
SELECT sourceName, nameRank, scientificName, scientificNameAuthorship, COUNT(*) AS names
FROM name n JOIN name_source ns JOIN source s
ON n.nameID=ns.nameID AND ns.sourceID=s.sourceID
WHERE sourceName='gcc'
GROUP BY sourceName, nameRank, scientificName, scientificNameAuthorship
HAVING names>1
ORDER BY sourceName, nameRank, scientificName, scientificNameAuthorship
LIMIT 12;

-- List example names from a particular source with no default 
-- Tropicos family
-- count names in each source than have no default family under Tropicos
SELECT sourceName, nameRank, n.nameID, scientificName, scientificNameAuthorship
FROM source s JOIN name_source ns JOIN name n JOIN higherClassification h
ON s.sourceID=ns.sourceID AND ns.nameID=n.nameID AND n.nameID=h.nameID
WHERE h.family IS NULL AND h.classificationSourceID=4
AND nameRank NOT IN ('root','family','class','division','kingdom','order','phylum','subclass','subdivision','subkingdom','suborder','subphylum','superclass','superdivision','superfamily','superorder')
AND sourceName='tpl'
LIMIT 12;

-- Names without family by source and family classification source
SELECT COUNT(*) AS namesWithoutFamilies
FROM (
SELECT sourceName, nameRank, n.nameID, scientificName, scientificNameAuthorship
FROM source s JOIN name_source ns JOIN name n JOIN higherClassification h
ON s.sourceID=ns.sourceID AND ns.nameID=n.nameID AND n.nameID=h.nameID
WHERE h.family IS NULL AND h.classificationSourceID=1
AND nameRank IN ('variety','subspecies','forma','species')
AND sourceName='tpl'
) AS a;

SELECT nameRank, COUNT(*) AS namesWithoutFamilies
FROM (
SELECT nameRank, n.nameID
FROM source s JOIN name_source ns JOIN name n JOIN higherClassification h
ON s.sourceID=ns.sourceID AND ns.nameID=n.nameID AND n.nameID=h.nameID
WHERE h.family IS NULL AND h.classificationSourceID=1
AND nameRank IN ('variety','subspecies','forma','species')
AND sourceName='tpl'
) AS a
GROUP BY nameRank;

SELECT acceptance AS taxonomicStatus, COUNT(*) AS namesWithoutFamilies
FROM (
SELECT acceptance, n.nameID
FROM source s JOIN name_source ns JOIN name n JOIN higherClassification h
ON s.sourceID=ns.sourceID AND ns.nameID=n.nameID AND n.nameID=h.nameID
LEFT JOIN synonym sy
ON n.nameID=sy.nameID
WHERE h.family IS NULL AND h.classificationSourceID=1
AND nameRank IN ('variety','subspecies','forma','species')
AND s.sourceID=1 AND sy.sourceID=1
) AS a
GROUP BY acceptance;

--
-- Check resolution of Hyeronima/Hieronyma species in tropicos
--

SET @sourceid:=1;

SELECT n_orig.nameID, n_orig.scientificName, n_orig.author, n_orig.acceptance, 
n_acc.nameID AS acc_nameID, n_acc.scientificName AS acc_scientificName, 
n_acc.scientificNameAuthorship AS acc_author
FROM (
SELECT n.nameID, genus, scientificName, scientificNameAuthorship AS author,
acceptedNameID, acceptance
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN synonym s
ON n.nameID=s.nameID
WHERE ns.sourceID=@sourceid
AND s.sourceID=@sourceid
AND genus IN ('Hyeronima','Hyeronyma','Hieronyma','Hieronima')
) AS n_orig
LEFT JOIN name n_acc
ON n_orig.acceptedNameID=n_acc.nameID
ORDER BY n_orig.scientificName, n_orig.author
;


--
-- Check rank indicators are standardized
--

SELECT DISTINCT rankIndicator FROM name ORDER BY rankIndicator;
SELECT DISTINCT infraspecificRank2 FROM name ORDER BY infraspecificRank2

-- Check ranks are standardized 
SELECT DISTINCT nameRank FROM name ORDER BY nameRank;

-- Check for non-standard subspecies rank indicators
-- Pass: 0
SELECT EXISTS (
SELECT * FROM name 
WHERE rankIndicator IN ('ssp', 'ssp.', 'sbsp', 'sbsp.')
) AS nonStandardSubspecies
;

--
-- Check ranks
--

-- Check ranks all lower case
-- Pass: 1
SELECT NOT EXISTS (
SELECT DISTINCT nameRank 
FROM name 
WHERE LOWER(nameRank)<>nameRank COLLATE utf8_bin)
AS allRanksLower
;


