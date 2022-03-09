-- ---------------------------------------------------------------
-- Check rank names all lower case
-- ---------------------------------------------------------------

SELECT NOT EXISTS (
SELECT nameRank 
FROM name
WHERE NOT nameRank=BINARY nameRank
LIMIT 1
 ) AS a;
