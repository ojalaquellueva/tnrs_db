-- -------------------------------------------------------------------
-- Original bibtex for source cact had issues. This should fix them.
-- Original bibtext in data directory updated, this code loades the
-- updated bibtex to the database.
-- -------------------------------------------------------------------

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
