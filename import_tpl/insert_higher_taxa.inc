<?php

/////////////////////////////////////////////////////////////////
// Purpose:
// Adds missing species, genera and families
/////////////////////////////////////////////////////////////////

// Extract genera from column `genus` and add them to as separate 
// taxa. For homonym genera in different families, this version 
// will insert duplicate genera in different families. This is 
// preferable to placing illegitimate names in the wrong family.
// As a solution, try infering acceptance in separate step
// based on status of child taxa of the genus
if (!isset($extract_species)) $extract_species=false;
if ($extract_species) {
	echo "Extracting missing species...";
	// Don't flag taxonomicStatus for now, 
	// do it in separate step, below. Value 
	// 'PENDING' is a placeholder. Uses 
	// infraspecificEpithet2 as temporary 
	// flag to avoid time-consuming left join. 
	// Can do this because infraspecificEpithet2 
	// not used for this source 
	$tbl_names_raw_temp = $tbl_names_raw . "_temp";
	$sql="
		-- Initial index on all infraspecific taxa
		UPDATE $tbl_names_raw
		SET infraspecificEpithet2='orphan_infra'
		WHERE rank IN ('forma','subspecies','variety')
		;
		
		-- Remove index for any with parent species
		-- already present
		UPDATE $tbl_names_raw AS infra 
		JOIN $tbl_names_raw  AS sp
		ON infra.genus=sp.genus AND infra.specificEpithet=sp.specificEpithet
		SET infra.infraspecificEpithet2=NULL
		WHERE sp.rank='species'
		AND infra.rank IN ('forma','subspecies','variety')
		;
		
		-- Insert species of orphan infraspecific taxa 
		INSERT INTO `$tbl_names_raw` (
		family,
		scientificName,
		genus,
		specificEpithet,
		rank,
		taxonomicStatus
		)
		SELECT DISTINCT
		family,
		CONCAT(genus,' ',specificEpithet),
		genus,
		specificEpithet,
		'species',
		'PENDING'
		FROM `$tbl_names_raw` 
		WHERE infraspecificEpithet2='orphan_infra'
		;
		
		-- Reset infraspecificEpithet2
		UPDATE $tbl_names_raw
		SET infraspecificEpithet2=NULL
		WHERE infraspecificEpithet2 IS NOT NULL
		;
	";
	sql_execute_multiple($dbh, $sql);
	echo $done;	
	
	echo "Linking orphan subspecies to species...";
	$sql="
		-- species with genus and family
		UPDATE `$tbl_names_raw` s JOIN `$tbl_names_raw` g
		ON s.genus=g.scientificName AND s.family=g.family
		SET s.parentNameID=g.nameID
		WHERE s.parentNameID IS NULL
		AND s.rank='species' AND g.rank='genus' 
		;
		-- species without family
		UPDATE `$tbl_names_raw` s JOIN `$tbl_names_raw` g
		ON s.genus=g.scientificName
		SET s.parentNameID=g.nameID
		WHERE s.rank='species' AND g.rank='genus' 
		AND s.parentNameID IS NULL
		AND s.family IS NULL AND g.family IS NULL
		;
	";
	sql_execute_multiple($dbh, $sql);
	echo $done;	
	
	echo "Inferring species taxonomic status...";
	// The reasoning here is that one or more child species
	// belonging to the same family+genus are explicity flagged
	// as "Accepted", the the genus must be accepted as well
	$sql="
		-- infraspecific taxa with families
		UPDATE `$tbl_names_raw` sp JOIN `$tbl_names_raw` infra
		ON sp.genus=infra.genus AND sp.specificEpithet=infra.specificEpithet
		AND sp.family=infra.family
		SET sp.taxonomicStatus='Accepted'
		WHERE sp.rank='species' AND infra.rank IN ('forma','subspecies','variety')   
		AND infra.taxonomicStatus='Accepted'
		AND sp.taxonomicStatus='PENDING'
		;
		-- infraspecific taxa without families
		UPDATE `$tbl_names_raw` sp JOIN `$tbl_names_raw` infra
		ON sp.genus=infra.genus AND sp.specificEpithet=infra.specificEpithet
		SET sp.taxonomicStatus='Accepted'
		WHERE sp.rank='species' AND infra.rank IN ('forma','subspecies','variety')   
		AND infra.taxonomicStatus='Accepted'
		AND sp.taxonomicStatus='PENDING'
		;
		-- set the remainder to unassessed
		UPDATE `$tbl_names_raw`
		SET taxonomicStatus='Unassessed'
		WHERE taxonomicStatus='PENDING'
		;
	";
	sql_execute_multiple($dbh, $sql);
	echo $done;	
}


// Extract genera from column `genus` and add them to as separate 
// taxa. For homonym genera in different families, this version 
// will insert duplicate genera in different families. This is 
// preferable to placing illegitimate names in the wrong family.
// As a solution, try infering acceptance in separate step
// based on status of child taxa of the genus
if ($extract_genera) {
	echo "Extracting genera...";
	// Don't flag taxonomicStatus for now, 
	// do it in separate step, below
	$sql="
		INSERT INTO `$tbl_names_raw` (
		family,
		scientificName,
		genus,
		rank,
		taxonomicStatus
		)
		SELECT DISTINCT
		family,
		genus,
		genus,
		'genus',
		NULL
		FROM `$tbl_names_raw`
		WHERE genus IS NOT NULL;
	";
	sql_execute_multiple($dbh, $sql);
	echo $done;	
	
	echo "Linking species to genera...";
	$sql="
		-- species with genus and family
		UPDATE `$tbl_names_raw` s JOIN `$tbl_names_raw` g
		ON s.genus=g.scientificName AND s.family=g.family
		SET s.parentNameID=g.nameID
		WHERE s.rank='species' AND g.rank='genus' 
		;
		-- species without family
		UPDATE `$tbl_names_raw` s JOIN `$tbl_names_raw` g
		ON s.genus=g.scientificName
		SET s.parentNameID=g.nameID
		WHERE s.rank='species' AND g.rank='genus' 
		AND s.parentNameID IS NULL
		AND s.family IS NULL AND g.family IS NULL
		;
	";
	sql_execute_multiple($dbh, $sql);
	echo $done;	
	
	echo "Inferring genus taxonomic status...";
	// The reasoning here is that one or more child species
	// belonging to the same family+genus are explicity flagged
	// as "Accepted", the the genus must be accepted as well
	$sql="
		UPDATE `$tbl_names_raw` g JOIN `$tbl_names_raw` s
		ON g.scientificName=s.genus AND g.family=s.family
		SET g.taxonomicStatus='Accepted'
		WHERE g.rank='genus' AND s.rank='species'   
		AND s.taxonomicStatus='Accepted'
		;
	";
	sql_execute_multiple($dbh, $sql);
	echo $done;	
}

// Extract family from the column "family" and add them to as 
// separate taxa
// Only do this if you are sure families are not already
// in the classification. May get weird results if taxa between
// the ranks of genus and family area included. This is also a 
// bad idea if the source database contains homonym families (unlikely)
if ($extract_families) {
	echo "Extracting families...";
	$sql="
		-- OK to flag all families as accepted for this source
		INSERT INTO `$tbl_names_raw` (
		family,
		scientificName,
		rank,
		taxonomicStatus
		)
		SELECT DISTINCT
		family,
		family,
		'family',
		'Accepted'
		FROM `$tbl_names_raw`
		WHERE family IS NOT NULL;
	";
	sql_execute_multiple($dbh, $sql);
	echo $done;	
	
	echo "Linking genera to families...";
	$sql="
		UPDATE `$tbl_names_raw` g JOIN `$tbl_names_raw` f
		ON g.family=f.scientificName
		SET g.parentNameID=f.nameID
		WHERE g.rank='genus' AND f.rank='family' 
	";
	sql_execute_multiple($dbh, $sql);
	echo $done;	
}

?>
