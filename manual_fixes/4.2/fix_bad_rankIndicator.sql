UPDATE name
SET scientificName=REPLACE(scientificName,'monstr','monstr.'),
scientificNameWithAuthor=REPLACE(scientificNameWithAuthor,'monstr','monstr.'),
nameRank='monstruosus',
rankIndicator='monstr.'
WHERE scientificName LIKE '% monstr %'
AND nameRank LIKE 'monstr%'
;

UPDATE name
SET 
nameRank='monstruosus',
rankIndicator='monstr.'
WHERE nameRank LIKE 'monstr%'
;

UPDATE name
SET rankIndicator=REPLACE(rankIndicator,'..','.')
WHERE rankIndicator LIKE '%..%'
;

UPDATE name
SET
scientificNameAuthorship=REPLACE(scientificName,'subsp.ecioid','subspecioid'),
scientificNameWithAuthor=REPLACE(scientificNameWithAuthor,'subsp.ecioid','subspecioid'),
rankIndicator='subspecioid'
WHERE scientificName LIKE '% subsp.ecioid %'
;

UPDATE name
SET specificEpithet=NULL,
rankIndicator=NULL,
infraspecificEpithet=NULL
WHERE specificEpithet='[unranked]'
;

UPDATE name 
SET 
nameRank='Incertae sedis',
specificEpithet=NULL,
rankIndicator=NULL,
otherEpithet=NULL
WHERE scientificName='Aster group Incertae sedis'
;

UPDATE name 
SET 
specificEpithet=NULL,
rankIndicator=NULL,
infraspecificEpithet=NULL,
otherEpithet=NULL
WHERE scientificName='Hypnum sect. Pulchella et sylvatica'
;

UPDATE name 
SET 
nameRank='unknown',
genus=NULL,
specificEpithet=NULL,
rankIndicator=NULL,
infraspecificEpithet=NULL,
otherEpithet=NULL
WHERE scientificName='Genero a. - fl. meso.'
;

UPDATE name 
SET 
specificEpithet=NULL,
rankIndicator=NULL,
infraspecificEpithet=NULL,
otherEpithet='Lappa'
WHERE scientificName='Arctium sect. Lappa kuntze'
;