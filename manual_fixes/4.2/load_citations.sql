-- ------------------------------------------------------------------------
-- Manual updates to support bibtex citations for TNRS (in meta table) and 
-- sources (in source table)
-- Changes not yet incorporated into pipeline
-- ------------------------------------------------------------------------

/* In shell:
# Remove BOM and line endings from all bibtex files
# and copy to new file
cd ~/bien/tnrs/data
cd tnrs
dos2unix TNRS_publication.bib
tr '\n\ ' ' TNRS_publication.bib TNRS_publication.bib.no-line-endings
dos2unix TNRS_website.bib
tr '\n\ ' ' TNRS_website.bib TNRS_website.bib.no-line-endings

cd ..
cd tropicos
dos2unix Tropicos.bib
tr '\n\ ' ' Tropicos.bib Tropicos.bib.no-line-endings

cd ..
cd wfo
dos2unix wfo.bib
tr '\n\ ' ' wfo.bib wfo.bib.no-line-endings

cd ..
cd wcvp
dos2unix wcvp.bib
tr '\n\ ' ' wcvp.bib wcvp.bib.no-line-endings

cd ..
cd usda
dos2unix USDA_Plants.bib
tr '\n\ ' ' USDA_Plants.bib.USDA_Plants.bib usda.bib.no-line-endings

*/

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
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/tnrs/TNRS_website.bib.no-line-endings' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
-- Fix BOM
UPDATE citation_raw
SET citation = TRIM(REPLACE(citation, 'ï»¿@', '@'))
;
UPDATE meta m, citation_raw c
SET m.citation=c.citation
;

--
-- Load tnrs publication citation
--
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/tnrs/TNRS_publication.bib.no-line-endings' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
-- Fix BOM
UPDATE citation_raw
SET citation = TRIM(REPLACE(citation, 'ï»¿@', '@'))
;
UPDATE meta m, citation_raw c
SET m.publication=c.citation
;

--
-- Load tropicos citation
--
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/tropicos/Tropicos.bib.no-line-endings' 
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
-- Load usda plants citation
--
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/usda/USDA_Plants.bib.no-line-endings' 
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