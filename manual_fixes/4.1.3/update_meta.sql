-- Note removal of hard-coded access data from citation
-- In future, try coverting this to current date 
-- on the fly in API response

USE tnrs;

UPDATE meta SET db_version='4.2.3'
UPDATE meta SET citation=REPLACE(citation, 'Version 4.1.}', 'Version 5.0.1}');
UPDATE meta SET citation=REPLACE(citation, 'Accessed 15 July 2020', 'Accessed <date_of_access>');
