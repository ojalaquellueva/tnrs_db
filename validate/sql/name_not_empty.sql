-- -------------------------------------------------------------
-- check table name not empty
-- -------------------------------------------------------------

SELECT EXISTS (
SELECT nameID 
FROM name 
LIMIT 1
) AS not_empty
; 

