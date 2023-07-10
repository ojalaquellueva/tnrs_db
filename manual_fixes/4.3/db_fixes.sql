-- -----------------------------------------------------------------
-- Manual fixes for a couple of glitches in TNRS DB v4.3
-- -----------------------------------------------------------------

USE tnrs_4_3;

ALTER TABLE source RENAME COLUMN logoUrl TO logo_path
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
-- Fix weird characters in front of @
UPDATE citation_raw
SET citation = TRIM(REPLACE(citation, 'ï»¿@', '@'))
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
-- Fix weird characters in front of @
UPDATE citation_raw
SET citation = TRIM(REPLACE(citation, 'ï»¿@', '@'))
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.sourceName='wcvp'
;

DROP TABLE IF EXISTS citation_raw;

-- Note escape in "world\'s"
UPDATE source
SET description="The WFO is an open-access, Web-based compendium of the world\'s plant species. It is a collaborative, international project, building upon existing knowledge and published Floras, checklists and revisions"
WHERE sourceID=1
;
-- Shorten WFO description while we're at it
UPDATE source
SET description="The World Checklist of Vascular Plants (WCVP) is a global consensus view of all known vascular plant species (flowering plants, conifers, ferns, clubmosses and firmosses)"
WHERE sourceID=2
;

--
-- Add missing final curly braces to TNRS publication citation bibtex
-- Also: update original bibtex file
--

UPDATE meta
SET publication="@article{tnrspub, author = {Boyle, B. and Hopkins, N. and Lu, Z. and Garay, J. A. R. and Mozzherin, D. and Rees, T. and Matasci, N. and Narro, M. L. and Piel, W. H. and McKay, S. J. and Lowry, S. and Freeland, C. and Peet, R. K. and Enquist, B. J.}, journal = {BMC Bioinformatics}, number = {1}, pages = {16}, title = {The taxonomic name resolution service: an online tool for automated standardization of plant names}, volume = {14}, year = {2013}, doi = {10.1186/1471-2105-14-16}}"
;

-- Fix some citations
UPDATE `source`
SET citation="@misc{wfo, author = {{WFO}}, title = {World Flora Online}, howpublished  = {v.2023.02}, year = {2023}, url = {http://www.worldfloraonline.org/}, note = {Accessed 3 May 2023} }"
WHERE sourceName='wfo'
;
