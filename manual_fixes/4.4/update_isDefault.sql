-- -------------------------------------------------------------------
-- Re-purposeing "isDefault" for use by the web app to determine
-- which source(s) should be on by default
-- Still needs to be updated in pipeline code
-- -------------------------------------------------------------------

-- Reset all to zero
UPDATE source
SET isDefault=0
;

-- Make WFO the default
UPDATE source
SET isDefault=1
WHERE sourceName='wfo'
;
