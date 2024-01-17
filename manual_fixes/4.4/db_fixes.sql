-- -----------------------------------------------------------------
-- Manual fixes for a couple of glitches in TNRS DB v4.4
-- All fixes implemented in main DB pipeline
-- DO NOT REPEAT for next version
-- -----------------------------------------------------------------

USE tnrs_dev;

-- The fields fixed inb DB pipeline, no need to add manually in future.
ALTER TABLE source RENAME COLUMN logoUrl TO logo_path
;
ALTER TABLE source DROP COLUMN logo_url
;
ALTER TABLE source ADD COLUMN citation TEXT DEFAULT NULL
;
ALTER TABLE collaborator RENAME COLUMN logo_url TO logo_path
;

--
-- Load wfo citation
--
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/wfo/wfo.bib.no-line-endings' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.sourceName='wfo'
;

--
-- Load wcvp citation
--
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/wcvp/wcvp.bib.no-line-endings' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.sourceName='wcvp'
;

--
-- Load cact citation
--
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/cact/cact.bib.no-line-endings' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.sourceName='cact'
;

DROP TABLE IF EXISTS citation_raw;

-- Fix descriptions
-- One-time fix due to incorrect values of parameter "description"
-- Now updated in DB pipeline
UPDATE `source`
SET description='Cactaceae at Caryophyllales.org – a dynamic online species-level taxonomic backbone for the family.'
WHERE sourceName='cact'
;
UPDATE `source`
SET description=' The World Checklist of Vascular Plants is based on Kew names and taxonomic backbone which has been created by reconciling the names from the International Plant Names Index (IPNI) with the taxonomy from the World Checklist of Selected Plant Families (WCSP). This Beta version therefore only displays names that are in both IPNI and WCVP. It contains both families that have been completed and peer reviewed by both external and internal experts on the relevant families as well as families that are in the process of being edited and reviewed. Some of the original data which WCSP built upon came from our generous collaborators listed in the acknowledgements. WCVP aims to represent a global consensus view of current plant taxonomy by reflecting the latest published taxonomies while incorporating the opinions of taxonomists based around the world.'
WHERE sourceName='wcvp'
;

--
-- Add missing final curly braces to TNRS publication citation bibtex
-- One-time fix, have updated original bibtex file
UPDATE meta
SET publication=CONCAT(publication, " }")
;

