-- ---------------------------------------------------------
-- Added to pipeline, DO NOT REPEAT for next version
-- ---------------------------------------------------------

USE tnrs_dev;

--
-- Create raw data table
-- Main table already exists
-- 

DROP TABLE IF EXISTS collaborator_raw;
CREATE TABLE collaborator_raw LIKE collaborator;
ALTER TABLE collaborator_raw DROP COLUMN collaboratorID;

--
-- Insert the raw text from file
-- 

LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/data/db/collaborators/collaborators.csv' 
INTO TABLE collaborator_raw
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 LINES
;

--
-- Insert to final table & delete raw table
-- 

INSERT INTO collaborator (
collaboratorName,
collaboratorNameFull,
collaboratorUrl,
description,
logo_path
)
SELECT
collaboratorName,
collaboratorNameFull,
collaboratorUrl,
description,
logo_path
FROM collaborator_raw
;

DROP TABLE collaborator_raw;
