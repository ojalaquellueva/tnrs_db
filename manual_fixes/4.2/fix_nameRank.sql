-- Standardize cultivar
UPDATE name
SET nameRank='cultivar'
WHERE nameRank='cultivated'
;

-- Un-abbreviate family and genus
UPDATE name
SET nameRank='family'
WHERE nameRank='fam.'
;

UPDATE name
SET nameRank='genus'
WHERE nameRank='gen.'
;


-- Remove rankIndicators where not used in scientific name
UPDATE name
SET rankIndicator=NULL
WHERE nameRank IN (
'family',
'genus',
'class',
'division'
)
;

-- Change "other infraspecific' to actual rank
-- Unabbreviated first
UPDATE name
SET nameRank=rankIndicator
WHERE nameRank='other infraspecific'
AND rankIndicator NOT LIKE '%.%'
AND infraspecificRank2 IS NULL
;
-- Abbreviated
UPDATE name
SET nameRank='convariety'
WHERE rankIndicator='convar.'
AND infraspecificRank2 IS NULL
;
UPDATE name
SET nameRank='monstruosus'
WHERE rankIndicator='monstr.'
AND infraspecificRank2 IS NULL
;
UPDATE name
SET nameRank='nm'
WHERE rankIndicator='nm.'
AND infraspecificRank2 IS NULL
;
UPDATE name
SET nameRank='nothoforma'
WHERE rankIndicator='nothofo.'
AND infraspecificRank2 IS NULL
;
UPDATE name
SET nameRank='nothosubspecies'
WHERE rankIndicator='nothosubsp.'
AND infraspecificRank2 IS NULL
;
UPDATE name
SET nameRank='nothovariety'
WHERE rankIndicator='nothovar.'
AND infraspecificRank2 IS NULL
;


UPDATE name
SET nameRank='microgen',
rankIndicator='microgen'
WHERE rankIndicator LIKE '%microgen%'
;
