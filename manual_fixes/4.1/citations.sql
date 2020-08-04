-- ------------------------------------------------------------------------
-- Manual updates to support bibtex citations for TNRS (in meta table) and 
-- sources (in source table)
-- Changes not yet incorporated into pipeline, add to pipeline next version
-- DB version 4.1
-- ------------------------------------------------------------------------

USE tnrs;

ALTER TABLE meta
ADD COLUMN citation TEXT DEFAULT NULL
;

ALTER TABLE source
ADD COLUMN citation TEXT DEFAULT NULL
;

--
-- Load tnrs citation
--
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/tnrs/TNRS_website.bib' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
-- Fix weird characters in front of @
UPDATE citation_raw
SET citation = TRIM(REPLACE(citation, 'ï»¿@', '@'))
;
UPDATE meta m, citation_raw c
SET m.citation=c.citation
;

--
-- Load tropicos citation
--
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/tropicos/Tropicos.bib' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
-- Fix weird characters in front of @
UPDATE citation_raw
SET citation = TRIM(REPLACE(citation, 'ï»¿@', '@'))
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.sourceName='tropicos'
;

--
-- Load tpl citation
--
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/tpl/ThePlantList.bib' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
-- Fix weird characters in front of @
UPDATE citation_raw
SET citation = TRIM(REPLACE(citation, 'ï»¿@', '@'))
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.sourceName='tpl'
;

--
-- Load usda plants citation
--
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/usda/USDA_Plants.bib' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
-- Fix weird characters in front of @
UPDATE citation_raw
SET citation = TRIM(REPLACE(citation, 'ï»¿@', '@'))
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.sourceName='usda'
;

DROP TABLE IF EXISTS citation_raw;

