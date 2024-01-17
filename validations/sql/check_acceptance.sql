-- ------------------------------------------------------------
-- Check standard TNRS acceptance codes only
-- ------------------------------------------------------------

SELECT NOT EXISTS (
SELECT acceptance 
FROM synonym
WHERE acceptance NOT IN (
'Accepted',
'Illegitimate',
'Invalid',
'No opinion',
'Orth. var.',
'Rejected name',
'Synonym'
)
LIMIT 1
 ) AS a;
