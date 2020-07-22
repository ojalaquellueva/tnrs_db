-- Fixes to table higherClassification
-- DB version 4.1

-- ------------------------------------------------------------
-- Fix stupid Lardizabalaceae issue
-- ------------------------------------------------------------

UPDATE higherClassification
SET familyNameID=1319411
WHERE family='Lardizabalaceae'
AND familyNameID IS NULL
AND classificationSourceID=1
;


-- ------------------------------------------------------------
-- Change family='Unknown' to family=NULL
-- ------------------------------------------------------------

UPDATE higherClassification
SET family=NULL
WHERE TRIM(family) IN ('Unknown','unknown','[Unknown]','[unknown]')
;

-- ------------------------------------------------------------
-- Populate missing families
-- ------------------------------------------------------------

-- 
-- First, some queries to illustrate the issue
--

SELECT h.*, n.scientificName
FROM source s JOIN higherClassification h
ON s.sourceID=h.classificationSourceID
JOIN name n
ON h.nameID=n.nameID
WHERE h.family IS NULL
AND n.nameRank IN ('forma','genus','Genus','species','subspecies','variety')
ORDER BY n.scientificName
LIMIT 25
;

-- 
-- The fix: join by genus to genera linked to only one family name
--

-- Backup table higherClassification
DROP TABLE IF EXISTS higherClassification_bak;
CREATE TABLE higherClassification_bak LIKE higherClassification;
INSERT INTO higherClassification_bak SELECT * FROM higherClassification;

-- Add temporary genus column to speed up update
ALTER TABLE higherClassification
ADD COLUMN genus VARCHAR(250) DEFAULT NULL
;
UPDATE higherClassification h JOIN name n
ON h.nameID=n.nameID
SET h.genus=n.genus
WHERE n.genus IS NOT NULL
;

-- Create temporary table of names to update and their IDs
-- This is safer as you can inspect the intended updates first
-- IMPORTANT: Repeat entire sequence for each classification source, adjusting
-- parameter familysourceid as needed
SET @familysourceid:=1;

-- Make table of "safe" families for this classification source
DROP TABLE IF EXISTS temp_safe_genera;
CREATE TABLE temp_safe_genera AS
SELECT genus FROM (
SELECT gf.genus, COUNT(DISTINCT gf.familyNameID) as fams
FROM (
SELECT h.nameID, n.scientificName, h.genus, 
f.nameID AS familyNameID, f.scientificName AS family, 
f.scientificNameAuthorship AS fam_auth, sf.acceptance AS fam_acceptance
FROM higherClassification h JOIN name n
ON h.nameID=n.nameID
JOIN name g
ON n.genus=g.scientificName
JOIN name_source nsg 
ON g.nameID=nsg.nameID
JOIN classification cg
ON g.nameID=cg.nameID
JOIN name f
ON cg.family=f.scientificName
JOIN name_source nsf 
ON f.nameID=nsf.nameID
JOIN synonym sf
ON f.nameID=sf.nameID
WHERE h.classificationSourceID=@familysourceid
AND nsg.sourceID=@familysourceid
AND cg.sourceID=@familysourceid
AND nsf.sourceID=@familysourceid
AND sf.sourceID=@familysourceid
AND h.family IS NULL
AND n.nameRank IN ('forma','genus','Genus','species','subspecies','variety')
) AS gf
GROUP BY gf.genus
HAVING fams=1
) AS a
;

-- Create table of genera which can safely updated to a single family
DROP TABLE IF EXISTS temp_safe_families;
CREATE TABLE temp_safe_families AS
SELECT DISTINCT h.genus, 
f.nameID AS familyNameID, f.scientificName AS family, 
sf.acceptance AS fam_acceptance
FROM higherClassification h JOIN name n
ON h.nameID=n.nameID
JOIN name g
ON n.genus=g.scientificName
JOIN name_source nsg 
ON g.nameID=nsg.nameID
JOIN classification cg
ON g.nameID=cg.nameID
JOIN name f
ON cg.family=f.scientificName
JOIN name_source nsf 
ON f.nameID=nsf.nameID
JOIN synonym sf
ON f.nameID=sf.nameID
WHERE h.classificationSourceID=@familysourceid
AND nsg.sourceID=@familysourceid
AND cg.sourceID=@familysourceid
AND nsf.sourceID=@familysourceid
AND sf.sourceID=@familysourceid
AND h.family IS NULL
AND n.nameRank IN ('forma','genus','Genus','species','subspecies','variety')
AND h.genus IN (
SELECT genus FROM temp_safe_genera
)
;

-- Update any synonym families to accepted names, if applicable
UPDATE temp_safe_families f JOIN synonym s
ON f.familyNameID=s.nameID
JOIN synonym s_acc
ON s.acceptedNameID=s_acc.nameID
JOIN name nf
ON s_acc.nameID=nf.nameID
SET f.familyNameID=nf.nameID,
f.family=nf.scientificName,
f.fam_acceptance='Accepted'
WHERE f.fam_acceptance<>'Accepted'
AND s_acc.acceptance='Accepted'
AND s.sourceID=@familysourceid
AND s_acc.sourceID=@familysourceid
;

-- Add a column to target table to allow checking of updated records
ALTER TABLE higherClassification
ADD COLUMN updated INTEGER DEFAULT NULL
;

-- Add indexes
ALTER TABLE temp_safe_families
ADD INDEX(genus)
;
ALTER TABLE higherClassification
ADD INDEX(genus)
;

-- Run the update
UPDATE higherClassification h JOIN temp_safe_families f
ON h.genus=f.genus
SET 
h.familyNameID=f.familyNameID,
h.family=f.family,
h.joinMethod='genus',
h.updated=1
WHERE h.family IS NULL
AND h.classificationSourceID=@familysourceid
;

-- Inspect the results
SELECT * FROM higherClassification
WHERE updated=1
;

-- After checking the updates, drop the update column, delete temp tables
-- and remove session variable
ALTER TABLE higherClassification DROP COLUMN updated;
DROP TABLE temp_safe_genera;
DROP TABLE temp_safe_families;
DROP TABLE higherClassification_bak;
SET @familysourceid:=NULL;


-- ------------------------------------------------------------
-- Populate missing familyNameID
-- ------------------------------------------------------------

-- 
-- First, some queries to illustrate the issue
--

-- If not zero, you have a probem
SELECT COUNT(*) FROM higherClassification
WHERE family IS NOT NULL AND familyNameID IS NULL
;  

-- List families by source
SELECT classificationSourceID, family, COUNT(*)
FROM higherClassification
WHERE family IS NOT NULL AND familyNameID IS NULL
GROUP BY classificationSourceID, family
; 

-- List problem families for a single source
SET @familysourceid:=1;
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
AND classificationSourceID=@familysourceid
) 
AND ns.sourceID=@familysourceid
AND s.sourceID=@familysourceid
) AS a 
LEFT JOIN name n_acc
ON a.acceptedNameID=n_acc.nameID
ORDER BY a.family, a.acceptance
;

-- 
-- The fix
--

-- Backup table higherClassification
DROP TABLE IF EXISTS higherClassification_bak;
CREATE TABLE higherClassification_bak LIKE higherClassification;
INSERT INTO higherClassification_bak SELECT * FROM higherClassification;

-- Create temporary table of names to update and their IDs
-- This is safer as you can inspect the intended updates first
-- IMPORTANT: Repeat entire sequence for each classification source, adjusting
-- parameter familysourceid as needed
SET @familysourceid:=1;

DROP TABLE IF EXISTS temp_hc_update_familyNameID;

CREATE TABLE temp_hc_update_familyNameID AS
SELECT a.sourceID, a.family AS familyWithoutID, 
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
AND classificationSourceID=@familysourceid
) 
AND ns.sourceID=@familysourceid
AND s.sourceID=@familysourceid
) AS a 
LEFT JOIN name n_acc
ON a.acceptedNameID=n_acc.nameID
) AS a
WHERE IF(acceptance='Accepted', a.nameID, a.acc_family_nameID) IS NOT NULL
ORDER BY a.family
;

-- Inspect to make sure everything looks good
SELECT * FROM temp_hc_update_familyNameID;

-- Add a column to target table to allow checking of updated records
ALTER TABLE higherClassification
ADD COLUMN updated INTEGER DEFAULT NULL
;

-- Run the update
UPDATE higherClassification h JOIN temp_hc_update_familyNameID t
ON h.family=t.familyWithoutID
SET h.familyNameID=t.acc_nameID_final,
h.family=t.acc_family_final,
h.updated=1
WHERE family IS NOT NULL AND familyNameID IS NULL
AND h.classificationSourceID=@familysourceid
;


-- Inspect the results
SELECT * FROM higherClassification
WHERE updated=1
;
SELECT DISTINCT family, familyNameID
FROM higherClassification
WHERE updated=1
;

-- After checking the updates, drop the update column, delete temp tables
-- and remove session variable
ALTER TABLE higherClassification DROP COLUMN updated;
DROP TABLE temp_hc_update_familyNameID;
DROP TABLE higherClassification_bak;
SET @familysourceid:=NULL;

-- ------------------------------------------------------------
-- Populate missing families using raw tropicos table
-- 
-- Run after above as this is allows some errors
-- ------------------------------------------------------------

-- Backup table higherClassification
DROP TABLE IF EXISTS higherClassification_bak;
CREATE TABLE higherClassification_bak LIKE higherClassification;
INSERT INTO higherClassification_bak SELECT * FROM higherClassification;

-- Set parameter familysourceid
SET @familysourceid:=1;

-- Get initial count of missing families
SELECT COUNT(*) AS missing_families
FROM (
-- List fields in case want to use subquery for manual inspection
SELECT DISTINCT n.nameID, n.scientificName, n.scientificNameAuthorship
FROM name n JOIN higherClassification h
ON n.nameID=h.nameID
WHERE h.classificationSourceID=@familysourceid
AND h.family IS NULL
AND n.nameRank NOT IN (
'class',
'division',
'ecad',
'family',
'order',
'subclass',
'subdivision',
'subkingdom',
'suborder',
'superdivision',
'superfamily',
'superorder'
)
) AS a
;


--
-- Populate text family field first
--

-- Join by name + author
UPDATE higherClassification h JOIN name n
ON n.nameID=h.nameID
JOIN tnrs_staging.tropicos_raw t
ON n.scientificName=t.scientificName
AND n.scientificNameAuthorship=t.scientificNameAuthorship
SET h.family=t.family
WHERE h.classificationSourceID=@familysourceid
AND h.family IS NULL
AND t.family IS NOT NULL
AND n.nameRank NOT IN (
'class',
'division',
'ecad',
'family',
'order',
'subclass',
'subdivision',
'subkingdom',
'suborder',
'superdivision',
'superfamily',
'superorder'
)
;
 
-- Add new column to table name indicating name has homonyms
-- Don't count canonical names (no author)
ALTER TABLE name
ADD COLUMN has_homonyms INT(1) DEFAULT NULL
;

-- Create temp table of homonym-bearing names by source
-- Source group essential to avoid counting spelling variants
-- of the same author as different names
DROP TABLE IF EXISTS temp_homonym_names;
CREATE TABLE temp_homonym_names AS
SELECT sourceName, s.sourceID, scientificName, COUNT(*)-1 AS homonyms
FROM name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN source s
ON ns.sourceID=s.sourceID
WHERE scientificNameAuthorship IS NOT NULL
GROUP BY sourceName, s.sourceID, scientificName
HAVING homonyms>0
;

-- Flag homonym-bearing names in table name
-- Note how only names with authors are flagged
ALTER TABLE temp_homonym_names
ADD INDEX(sourceName),
ADD INDEX(sourceID),
ADD INDEX(scientificName)
;
UPDATE name n JOIN name_source ns
ON n.nameID=ns.nameID
JOIN temp_homonym_names t
ON n.scientificName=t.scientificName
AND ns.sourceID=t.sourceID
SET has_homonyms=1
WHERE n.scientificNameAuthorship IS NOT NULL
;

-- Flag non-homonym names
UPDATE name 
SET has_homonyms=0
WHERE has_homonyms IS NULL
AND scientificNameAuthorship IS NOT NULL
;

-- Check counts of homonyms names
SELECT has_homonyms, COUNT(*) AS names
FROM name
WHERE scientificNameAuthorship IS NOT NULL
GROUP BY has_homonyms
;

-- Join by name only, updating just non-homonym names
UPDATE higherClassification h JOIN name n
ON n.nameID=h.nameID
JOIN tnrs_staging.tropicos_raw t
ON n.scientificName=t.scientificName
SET h.family=t.family
WHERE h.classificationSourceID=@familysourceid
AND h.family IS NULL
AND t.family IS NOT NULL
AND n.nameRank NOT IN (
'class',
'division',
'ecad',
'family',
'order',
'subclass',
'subdivision',
'subkingdom',
'suborder',
'superdivision',
'superfamily',
'superorder'
)
AND n.has_homonyms=0
;
 
--
-- Update remainder, joining by name only,
-- but for accepted names only
--

-- strict version
UPDATE higherClassification h JOIN name n
ON n.nameID=h.nameID
JOIN tnrs_staging.tropicos_raw t
ON n.scientificName=t.scientificName
JOIN name_source ns
ON n.nameID=ns.nameID
JOIN synonym s
ON n.nameID=s.nameID AND ns.sourceID=s.sourceID
SET h.family=t.family
WHERE h.classificationSourceID=@familysourceid
AND h.family IS NULL
AND t.family IS NOT NULL
AND n.nameRank NOT IN (
'class',
'division',
'ecad',
'family',
'order',
'subclass',
'subdivision',
'subkingdom',
'suborder',
'superdivision',
'superfamily',
'superorder'
)
AND s.acceptance='Accepted'
AND t.acceptance='Accepted'
;

-- Less strict
UPDATE higherClassification h JOIN name n
ON n.nameID=h.nameID
JOIN tnrs_staging.tropicos_raw t
ON n.scientificName=t.scientificName
JOIN synonym s
ON n.nameID=s.nameID
SET h.family=t.family
WHERE h.classificationSourceID=@familysourceid
AND h.family IS NULL
AND t.family IS NOT NULL
AND n.nameRank NOT IN (
'class',
'division',
'ecad',
'family',
'order',
'subclass',
'subdivision',
'subkingdom',
'suborder',
'superdivision',
'superfamily',
'superorder'
)
AND s.acceptance='Accepted'
AND t.acceptance='Accepted'
;

-- Less strict still
UPDATE higherClassification h JOIN name n
ON n.nameID=h.nameID
JOIN tnrs_staging.tropicos_raw t
ON n.scientificName=t.scientificName
SET h.family=t.family
WHERE h.classificationSourceID=@familysourceid
AND h.family IS NULL
AND t.family IS NOT NULL
AND n.nameRank NOT IN (
'class',
'division',
'ecad',
'family',
'order',
'subclass',
'subdivision',
'subkingdom',
'suborder',
'superdivision',
'superfamily',
'superorder'
)
AND t.acceptance='Accepted'
;

-- Totally non-strict still
UPDATE higherClassification h JOIN name n
ON n.nameID=h.nameID
JOIN tnrs_staging.tropicos_raw t
ON n.scientificName=t.scientificName
SET h.family=t.family
WHERE h.classificationSourceID=@familysourceid
AND h.family IS NULL
AND t.family IS NOT NULL
AND n.nameRank NOT IN (
'class',
'division',
'ecad',
'family',
'order',
'subclass',
'subdivision',
'subkingdom',
'suborder',
'superdivision',
'superfamily',
'superorder'
)
;

--
-- Direct update for names linked directly to tropicos.
-- Run this first when incorporate into pipeline!
--

UPDATE higherClassification h 
JOIN name_source ns
ON h.nameID=ns.nameID
JOIN tnrs_staging.tropicos_raw t
ON ns.nameSourceUrl=t.nameUri
SET h.family=t.family
WHERE h.classificationSourceID=@familysourceid
AND h.family IS NULL
AND t.family IS NOT NULL
;
 
-- Clean up
DROP TABLE IF EXISTS higherClassification_bak;
DROP TABLE IF EXISTS temp_homonym_names;
SET @familysourceid:=NULL;


