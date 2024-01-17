-- ------------------------------------------------------------
-- Check for non-plant scrubbed families
-- ------------------------------------------------------------

SELECT NOT EXISTS (
SELECT family 
FROM higherClassification 
WHERE NOT family LIKE '%aceae%' 
AND family IS NOT NULL 
AND LOWER(family)<>'incertae sedis'
) AS no_bad_families
;
