# Create & populate new table collaborator, including logo files

## Warning: 
**CREATE TABLE is only step in main code. Remainder not yet added to DB pipeline**

## Requirements:  
1. File collaborators.csv exists in data directory  
2. Logo files in subdirectory data/db/images
3. Name of files in images directory match file names in collaborators.csv

## Create table and import data (except file blob)

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
  logo_filename VARCHAR(100) DEFAULT NULL,
  logo BLOB DEFAULT NULL,    
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
logo_path,
logo_filename
)
SELECT
collaboratorName,
collaboratorNameFull,
collaboratorUrl,
description,
logo_path,
logo_filename
FROM collaborator_raw
;

DROP TABLE collaborator_raw;

```

## Import the image files
* Source: https://stackoverflow.com/a/41018123/2757825  

**In shell:**  

```
cd /home/boyle/bien/tnrs/tnrs_db/data/db/images
for fpath in ./*; do
	fname=${fpath##*/}
	echo -n  "Loading ${fname}..."
	mysql --login-path=local  -e "update collaborator set logo=FROM_BASE64('`base64 -i ${fname}`') where logo_filename='${fname}'" tnrs
	echo "done"
done
```
