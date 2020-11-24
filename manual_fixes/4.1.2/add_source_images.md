# Add image logo files

## Warning: 
**Updated CREATE TABLE is only step in main code. Remainder not yet added to DB pipeline**

## Requirements:  
1. Logo files exist in subdirectory data/db/images
2. Base name of each logo file (minus extension) is IDENTICAL to sourceName

## Update table schema and import data (except file blob)

**MySQL command line:**

```
USE tnrs;

ALTER TABLE source
ADD COLUMN logo_path VARCHAR(500) DEFAULT NULL,
ADD COLUMN logo_filename VARCHAR(100) DEFAULT NULL,
ADD COLUMN logo  BLOB DEFAULT NULL
;

```

## Import the image files
* Source: https://stackoverflow.com/a/41018123/2757825  

**In shell:**  

```
cd /home/boyle/bien/tnrs/tnrs_db/data/db/images
for fpath in ./*; do
	fname=${fpath##*/}
	echo -n  "Loading ${fname}..."
	mysql --login-path=local  -e "update source set logo=FROM_BASE64('`base64 -i ${fname}`') where logo_filename='${fname}'" tnrs
	echo "done"
done
```
