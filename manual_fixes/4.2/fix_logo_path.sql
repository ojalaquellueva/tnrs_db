-- This needs to be fixed in pipeline!

ALTER TABLE `source` 
CHANGE logoUrl logo_path varchar(500) default null
;

ALTER TABLE `collaborator` 
CHANGE logo_url logo_path varchar(500) default null
;