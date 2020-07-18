-- Fixes to table gf_lookup
-- DB version 4.1

-- ------------------------------------------------------------
-- Remove duplicate records
-- ------------------------------------------------------------

SELECT COUNT(*) FROM gf_lookup;
ALTER TABLE gf_lookup RENAME TO gf_lookup_old;
CREATE TABLE gf_lookup SELECT DISTINCT * FROM gf_lookup_old;
select * from gf_lookup order by genus, family limit 100;DROP TABLE gf_lookup_old;

-- ------------------------------------------------------------
-- Flag "safe" genera with only one family 
-- ------------------------------------------------------------
ALTER TABLE gf_lookup
ADD COLUMN unambiguous INTEGER DEFAULT 0
;

UPDATE gf_lookup g JOIN (
	SELECT genus, COUNT(*) AS fams
	FROM gf_lookup
	GROUP BY genus
	HAVING fams=1
) AS g_safe
ON g.genus=g_safe.genus
SET unambiguous=1
;

ALTER TABLE gf_lookup
ADD INDEX(unambiguous)
;

-- Add a few more indexes while we're at it
ALTER TABLE gf_lookup
ADD INDEX(genus),
ADD INDEX(family),
ADD INDEX(isPrimary)
;


