-- ---------------------------------------------------------------------
-- Update metadata tables
-- Needs to be fixed in pipeline!
-- ---------------------------------------------------------------------

-- 
-- source
--

ALTER TABLE `source` 
CHANGE logoUrl logo_path varchar(500) default null
;
ALTER TABLE `source` 
DROP COLUMN logo_url
;

UPDATE `source`
SET logo_path='https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2021/07/wfo_logo.jpeg'
WHERE sourceName='wfo'
;
UPDATE `source`
SET logo_path='https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2021/07/kew_logo.png'
WHERE sourceName='wcvp'
;

ALTER TABLE `source` 
ADD COLUMN citation VARCHAR(500) DEFAULT NULL
;

UPDATE `source`
SET citation='@misc{wfo, author = {{WFO}}, title = {World Flora Online}, howpublished  = {v.2023.02}, url = {http://www.worldfloraonline.org/}, note = {Accessed 3 May 2023} }'
WHERE sourceName='wfo'
;
UPDATE `source`
SET citation='@misc{wcvp, author = {{Govaerts R (ed.)}}, publisher = {Royal Botanic Gardens, Kew}, title = {WCVP: World Checklist of Vascular Plants, version 11}, year = {2023}, url = {http://sftp.kew.org/pub/data-repositories/WCVP/}, note = {Accessed 3 May 2023} }'
WHERE sourceName='wcvp'
;


--
-- collaborator
--

ALTER TABLE `collaborator` 
CHANGE logo_url logo_path varchar(500) default null
;


