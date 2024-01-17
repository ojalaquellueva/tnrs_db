-- ------------------------------------------------------------
-- Check for unknown families
-- Returns FAIL is family="Unknown" exists
-- Not necessarily bad but good to know
-- ------------------------------------------------------------

SELECT NOT EXISTS (
SELECT family 
FROM higherClassification
 WHERE LOWER(family)='unknown'
 LIMIT 1
 ) AS a;
