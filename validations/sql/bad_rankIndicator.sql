-- ------------------------------------------------------------
-- Known bad rank indicators
-- ------------------------------------------------------------

SELECT NOT EXISTS (
SELECT rankIndicator 
FROM name
WHERE rankIndicator IN ('ssp','ssp.','sbsp','sbsp.','f','f.','cv','monstr')
OR rankIndicator LIKE '%..%'
LIMIT 1
 ) AS a;
