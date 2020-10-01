-- ---------------------------------------------------------------
-- Add column `api_version` to table `meta` and update the 
-- relevant columns
-- Updating core code to 5.0 to distinguish break from original
-- TNRS, which was at 4.1 at final release.
-- ---------------------------------------------------------------

ALTER TABLE meta
ADD COLUMN api_version VARCHAR(50) DEFAULT NULL
;

UPDATE meta 
SET
db_version='4.1.1',
code_version='5.0',
api_version='1.0',
build_date=CURRENT_DATE()
;
