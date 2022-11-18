-- -------------------------------------------------------------------
-- Update base urls for USDA Plants
-- Changes have been added to pipeline in import_usda/params.inc
-- -------------------------------------------------------------------

-- base url for name with code
UPDATE name_source
SET nameSourceUrl=REPLACE(nameSourceUrl,
'http://plants.usda.gov/java/profile?symbol=',
'https://plants.sc.egov.usda.gov/home/plantProfile?symbol='
)
WHERE sourceID=4
AND nameSourceUrl LIKE 'http://plants.usda.gov/java/profile?symbol=%'
;

-- Generic url if no name code
UPDATE name_source
SET nameSourceUrl=REPLACE(nameSourceUrl,
'http://plants.usda.gov/java/nameSearch',
'https://plants.sc.egov.usda.gov/home'
)
WHERE sourceID=4
AND nameSourceUrl LIKE 'http://plants.usda.gov/java/nameSearch%'
;