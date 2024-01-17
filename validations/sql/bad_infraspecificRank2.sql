-- ------------------------------------------------------------
-- Known bad rank quadrinomial rank indicators
-- This method uses whitelist of allowable indicators
-- ------------------------------------------------------------

SELECT NOT EXISTS (
SELECT infraspecificRank2 
FROM name
WHERE infraspecificRank2 NOT IN ('fo.','lusus','prol.','subvar.','subfo.','cv.','subsp.')
LIMIT 1
 ) AS a;
