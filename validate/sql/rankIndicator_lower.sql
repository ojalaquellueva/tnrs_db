-- ---------------------------------------------------------------
-- Check rank indicators all lower case
-- ---------------------------------------------------------------

SELECT NOT EXISTS (
SELECT rankIndicator 
FROM name
WHERE NOT rankIndicator=BINARY rankIndicator
LIMIT 1
 ) AS a;
