# Add image logo files

## Warning: 
**Updated CREATE TABLE is only step in main code. Remainder not yet added to DB pipeline**

## Requirements:  
1. Logo files exist in subdirectory data/db/images
2. Base name of each logo file (minus extension) is IDENTICAL to sourceName

## Update table schema 
**MySQL command line:**

```
USE tnrs;

ALTER TABLE source
ADD COLUMN logo_path VARCHAR(500) DEFAULT NULL
;

```

## Populate image file path

**In shell:**  

```
cd /home/boyle/bien/tnrs/api/images

for fpath in ./*; do
	fname=${fpath##*/}
	fname_base=${fname%".png"}
	echo -n  "fname: ${fname}, "
	echo "fname_base: ${fname_base}"
done

for fpath in ./*; do
	fname=${fpath##*/}
	fname_base=${fname%".png"}
	echo -n  "Loading ${fname}..."
	mysql --login-path=local  -e "update source set logo_path=concat('images/', '${fname}') where sourceName='${fname_base}'" tnrs
	echo "done"
done
```
