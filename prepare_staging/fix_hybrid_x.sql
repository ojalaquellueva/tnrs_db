-- ------------------------------------------------------------------------
-- Convert extended-ascii multiplication sign hybrid '×' to plain ascii 'x'
-- ------------------------------------------------------------------------

-- Transform hybrid × if applicable.
-- Insert space after '×' in case snugged up against epithet
-- Space required to distinguish plain ascii hybrid 'x' from name
UPDATE `nameStaging` 
SET `scientificName`=REPLACE(`scientificName`,'×','x ')
;

-- Remove superflous space if applicable
UPDATE `nameStaging` 
SET `scientificName`=REPLACE(`scientificName`,'  ',' ')
;