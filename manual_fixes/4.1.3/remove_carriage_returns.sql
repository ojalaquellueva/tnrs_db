-- ---------------------------------------------------------------
-- Fixes very specific issue of carriage return (/r) embedded in name
-- in database, spotted by Xiao and reported as Issue #2 for
-- TNRS API, for submitted (invalid) name "Monniera monniera"
-- 
-- Date: 6 april 2021
-- ---------------------------------------------------------------

-- Mysql on vegbiendev: use tnrs;

-- MySQL on paramo: use tnrs_4_1_2;

--
-- name
-- 

-- Count all names with carriage return:
select count(*) from name where scientificName REGEXP "\r";

-- If not too many, display names vertically
select * from name where scientificName REGEXP "\r"\G

-- Backup, just in case
create table name_bak like name;
insert into name_bak select * from name;

-- Update name components
UPDATE name
SET scientificName=REPLACE(scientificName,CHAR(13),'')
WHERE scientificName REGEXP "\r"
;
UPDATE name
SET specificEpithet=REPLACE(specificEpithet,CHAR(13),'')
WHERE specificEpithet REGEXP "\r"
;
UPDATE name
SET scientificNameWithAuthor=REPLACE(scientificNameWithAuthor,CHAR(13),'')
WHERE scientificNameWithAuthor REGEXP "\r"
;

--
-- splist_genlist_combined
-- 

-- Count all names with carriage return:
select count(*) from splist_genlist_combined where species REGEXP "\r";

-- Backup, just in case
create table splist_genlist_combined_bak like splist_genlist_combined;
insert into splist_genlist_combined_bak select * from splist_genlist_combined;

-- Update name components
UPDATE splist_genlist_combined
SET species=REPLACE(species,CHAR(13),'')
WHERE species REGEXP "\r"
;
UPDATE splist_genlist_combined
SET genus_species=REPLACE(genus_species,CHAR(13),'')
WHERE genus_species REGEXP "\r"
;

--
-- infra1list_splist_combined
-- 

-- Count all names with carriage return:
select count(*) from infra1list_splist_combined where species_infra1 REGEXP "\r";
-- Aren't any

--
-- drop backup tables if satisfied
-- 
