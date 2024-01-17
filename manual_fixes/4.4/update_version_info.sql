-- -------------------------------------------------------------------
-- Fixing version info I forgot to update in parameters
-- -------------------------------------------------------------------


ALTER TABLE meta
ADD COLUMN db_code_version VARCHAR(50) DEFAULT NULL AFTER `build_date`
;

UPDATE meta
SET 
app_version='5.2',
db_code_version='4.4',
code_version='5.1',
api_version='5.1'
;