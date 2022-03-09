UPDATE name
SET scientificName=REPLACE(scientificName,'cv','cv.'),
scientificNameWithAuthor=REPLACE(scientificNameWithAuthor,'cv','cv.'),
nameRank='cultivar',
rankIndicator='cv.'
WHERE scientificName LIKE '% cv %'
AND nameRank LIKE 'cv%'
AND infraspecificRank2 IS NULL
;

UPDATE name
SET 
nameRank='cultivar',
rankIndicator='cv.'
WHERE nameRank='cv'
AND infraspecificRank2 IS NULL
;