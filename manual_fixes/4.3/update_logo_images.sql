-- UNDER CONSTRUCTION!!! Missing some image files

-- 
-- Update logo_paths for collaborators to use BIEN website media store
--

-- BIEN
UPDATE collaborator
SET logo_path='https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2016/09/bien_logo_notext-1.png'
WHERE collaboratorName='BIEN'
;

-- MBG
UPDATE collaborator
SET logo_path='https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2023/06/MBG_notext.png'
WHERE collaboratorName='MBG'
;

-- NCEAS
UPDATE collaborator
SET logo_path='https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2023/06/nceas.png'
WHERE collaboratorName='NCEAS'
;

--  NSF
UPDATE collaborator
SET logo_path='https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2018/05/nsf.png'
WHERE collaboratorName='NSF'
;

-- University of Arizona
UPDATE collaborator
SET logo_path='https://bien.nceas.ucsb.edu/bien/wp-content/uploads/2023/06/UA_notext.png'
WHERE collaboratorName='University of Arizona'
;