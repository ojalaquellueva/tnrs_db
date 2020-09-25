-- ---------------------------------------------------------------
-- Update metadata table after execution all manual validations
-- Run this step last
-- ---------------------------------------------------------------

-- Update code_version with latest git tag for TNRS DB code.
-- Be sure to update repo and tag with new version number
-- after building Db and executing all scripts in this directory. 
-- Leave DB version as is
UPDATE meta 
SET
code_version='4.1',
build_date=CURRENT_DATE()
;
