-- ---------------------------------------------------------------
-- Check rank indicators all lower case
-- ---------------------------------------------------------------

SELECT NOT EXISTS (
SELECT infraspecificRank2 
FROM name
WHERE NOT infraspecificRank2=BINARY infraspecificRank2
LIMIT 1
 ) AS a;
