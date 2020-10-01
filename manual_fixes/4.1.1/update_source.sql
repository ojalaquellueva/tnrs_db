-- ------------------------------------------------------------------------
-- Manual updates to support new columns added to table sources. These 
-- Changes also added to pipeline.
-- ------------------------------------------------------------------------

USE tnrs;

--
-- Add columns
-- 

ALTER TABLE source
ADD COLUMN description TEXT AFTER sourceUrl
;
ALTER TABLE source
ADD COLUMN logoUrl VARCHAR(500) DEFAULT NULL AFTER description
;  
ALTER TABLE source
ADD COLUMN dataUrl VARCHAR(500) DEFAULT NULL AFTER logoUrl
;  

--
-- Update columns
-- 

-- Tropicos
UPDATE source
SET
sourceUrl='https://www.tropicos.org/',
logoUrl='https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2020/10/TropicosLogo.gif',
dataUrl='http://services.tropicos.org/',
description="The Missouri Botanical Garden's Tropicos database links over 1.33M scientific names with over 4.87M specimens and over 685K digital images. The data includes over 150K references from over 52.6K publications offered as a free service to the world’s scientific community."
WHERE sourceName='tropicos'
;

-- TPL
UPDATE source
SET
sourceUrl='http://www.theplantlist.org/',
logoUrl='https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2020/10/tpl_logo.png',
dataUrl='',
description="The Plant List (TPL) was a working list of all known plant species produced by the botanical community in response to Target 1 of the 2002-2010 Global Strategy for Plant Conservation (GSPC). TPL has been static since 2013, but was used as the starting point for the Taxonomic Backbone of the World Flora Online (WFO), and updated information can be found at www.worldfloraonline.org"
WHERE sourceName='tpl'
;

-- usda
UPDATE source
SET
sourceUrl='https://plants.sc.egov.usda.gov/java/',
logoUrl='https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2020/10/tpl_logo.png',
dataUrl='http://plants.usda.gov/adv_search.html',
description="The PLANTS Database provides standardized information about the vascular plants, mosses, liverworts, hornworts, and lichens of the U.S. and its territories."
WHERE sourceName='usda'
;
