-- Untranslated hybrid x in tropicos name
UPDATE name
SET scientificName='Catalpa x erubescens fo. x purpurea',
scientificNameWithAuthor='Catalpa x erubescens fo. x purpurea Dode',
speciesHybridX=NULL,
specificEpithet='erubescens',
rankIndicator='fo.',
infraspecificHybridX=NULL,
infraspecificEpithet='purpurea',
infraspecificRank2=NULL,
infraspecificEpithet2=NULL,
isHybrid=1
WHERE scientificName='Catalpa Ã— erubescens fo. Ã— purpurea'
;

-- Hybrid subspecies from usda
UPDATE name
SET scientificName='Phragmites australis subsp. americanus x subsp. australis',
scientificNameWithAuthor='Phragmites australis subsp. americanus x subsp. australis [unnamed hybrid]',
speciesHybridX=NULL,
specificEpithet='australis',
rankIndicator='subsp.',
infraspecificHybridX=NULL,
infraspecificEpithet='americanus',
infraspecificRank2='subsp.',
infraspecificEpithet2='australis',
isHybrid=1
WHERE scientificName='Phragmites australis subsp. americanus âˆšÃ³ subsp. australis'
;

UPDATE name
SET scientificName='Platanthera dilatata var. leucostachys x yosemitensis',
scientificNameWithAuthor='Platanthera dilatata var. leucostachys x yosemitensis [unnamed hybrid]',
speciesHybridX=NULL,
specificEpithet='dilatata',
rankIndicator='var.',
infraspecificHybridX=NULL,
infraspecificEpithet='leucostachys',
infraspecificRank2=NULL,
infraspecificEpithet2='yosemitensis',
isHybrid=1,
isNamedHybrid=1
WHERE scientificName='Platanthera dilatata var. leucostachys âˆšÃ³ yosemitensis'
;

-- 'c.' instead of 'cv.'
UPDATE name
SET scientificName=REPLACE(scientificName,'c.','cv.'),
scientificNameWithAuthor=REPLACE(scientificNameWithAuthor,'c.','cv.'),
nameRank='cultivar',
infraspecificRank2='cv.'
WHERE scientificName LIKE '% c. %' 
AND infraspecificRank2='c.'
;


