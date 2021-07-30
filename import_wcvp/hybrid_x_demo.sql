DROP TABLE IF EXISTS hybridx;
CREATE TABLE hybridx AS 
SELECT nameID, scientificName
FROM wcvp_raw
WHERE ASCII(strSplit(scientificName,' ',2))=195
LIMIT 6
;

ALTER TABLE hybridx
CHARACTER SET utf8,
COLLATE utf8_general_ci;

SELECT * FROM hybridx;

UPDATE hybridx
SET scientificName=REPLACE(scientificName,'×','x ')
;
UPDATE hybridx
SET scientificName=REPLACE(scientificName,'  ',' ')
;

SELECT * FROM hybridx;

DROP TABLE hybridx;
