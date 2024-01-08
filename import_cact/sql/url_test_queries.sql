-- Test queries for URL structure for TNRS source "cact"

(select nameID, nameID_char, acceptedNameID_char, scientificName, scientificNameAuthorship, taxonomicStatus, taxonUri from cact_raw where `rank`='species' and taxonomicStatus='Accepted' limit 1)
UNION ALL
(select nameID, nameID_char, acceptedNameID_char, scientificName, scientificNameAuthorship, taxonomicStatus, taxonUri from cact_raw where `rank`='species' and taxonomicStatus='No opinion' limit 1)
UNION ALL
(select nameID, nameID_char, acceptedNameID_char, scientificName, scientificNameAuthorship, taxonomicStatus, taxonUri from cact_raw where `rank`='species' and taxonomicStatus='Invalid' limit 1)
;

-- synonym
select nameID, nameID_char, acceptedNameID_char, scientificName, scientificNameAuthorship, taxonomicStatus, taxonUri from cact_raw where `rank`='species' and taxonomicStatus='Synonym' limit 1\G



UPDATE `cact_raw` 
SET taxonUri=
CASE
WHEN `taxonomicStatus` IN ('Accepted','Invalid','No opinion') THEN CONCAT('https://caryophyllales.org/cdm_dataportal/taxon/', `nameID_char`)
WHEN `taxonomicStatus`='Synonym' THEN CONCAT(
	'https://caryophyllales.org/cdm_dataportal/taxon/', `acceptedNameID_char`, 
	'/synonymy?highlite=', `nameID_char`, 
	'&acceptedFor=', `nameID_char`, 
	'#', `nameID_char`
	)
ELSE NULL
END
WHERE nameID_char IS NOT NULL
;
