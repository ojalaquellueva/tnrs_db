-- Creates and populates scope columns in table source
-- Added to DB, no need to repeat

--USE tnrs_dev;
USE tnrs_4_4;

ALTER TABLE `source`
ADD COLUMN geographic_scope VARCHAR(50) DEFAULT NULL, 
ADD COLUMN taxonomic_scope VARCHAR(50) DEFAULT NULL, 
ADD COLUMN `scope` VARCHAR(50) DEFAULT NULL
;

ALTER TABLE `source` 
ADD INDEX source_geographic_scope(geographic_scope),
ADD INDEX source_taxonomic_scope(taxonomic_scope),
ADD INDEX source_scope(`scope`)
;

UPDATE source
SET
geographic_scope='global',
taxonomic_scope='Embryophyta',
`scope`='global'
WHERE `sourceName`='wfo'
;
UPDATE source
SET
geographic_scope='global',
taxonomic_scope='Tracheophyta',
`scope`='global'
WHERE `sourceName`='wcvp'
;
UPDATE source
SET
geographic_scope='global',
taxonomic_scope='Cactaceae',
`scope`='limited'
WHERE `sourceName`='cact'
;


