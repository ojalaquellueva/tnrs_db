# Create & populate new table collaborator, including logo urls

## Warning: 
**CREATE TABLE is only step in main code. Remainder not yet added to DB pipeline**

## Requirements:  
1. File collaborators.csv exists in data directory  
2. Url portion of url_logo in collaborators.csv must point to api/images
3. File name portion of url_logo in collaborators.csv must match names of files in api/images

## Create table and import data 

**MySQL command line:**

```
USE tnrs;

--
-- Create table
-- 

DROP TABLE IF EXISTS collaborator;
CREATE TABLE collaborator (
  collaboratorID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  collaboratorName VARCHAR(50) NOT NULL UNIQUE,
  collaboratorNameFull VARCHAR(250) DEFAULT NULL,
  collaboratorUrl VARCHAR(500) DEFAULT NULL,
  description text,
  logo_path VARCHAR(500) DEFAULT NULL,
  PRIMARY KEY(collaboratorID),
  INDEX collaborator_collaboratorName(collaboratorName)
)
ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

--
-- Create raw data table
-- 

DROP TABLE IF EXISTS collaborator_raw;
CREATE TABLE collaborator_raw LIKE collaborator;
ALTER TABLE collaborator_raw DROP COLUMN collaboratorID;

--
-- Insert the raw text from file
-- 

LOAD DATA LOCAL INFILE '/home/boyle/bien/tnrs/tnrs_db/data/db/collaborators.csv' 
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
```