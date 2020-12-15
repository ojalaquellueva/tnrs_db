# Correct erroneous source image path

## Warning: 
**Not yet added to DB pipeline**

## Requirements:  
1. Logo files exist in subdirectory data/db/images
2. Base name of each logo file (minus extension) is IDENTICAL to sourceName

## Correct image file path

**In shell:**  

```
cd /home/boyle/bien/tnrs/api/images

for fpath in ./*; do
	fname=${fpath##*/}
	fname_base=${fname%".png"}
	echo -n  "Loading ${fname}..."
	mysql --login-path=local  -e "update source set logo_path=concat('images/', '${fname}') where sourceName='${fname_base}'" tnrs
	echo "done"
done
```
