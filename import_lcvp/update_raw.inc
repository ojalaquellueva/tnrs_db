<?php

/////////////////////////////////////////////////////////////////
// Purpose: Add integer PK to raw data
/////////////////////////////////////////////////////////////////

echo "Updating `$tbl_names_raw`\n";

echo "  Populating species_binomial...";
$sql="
	UPDATE `$tbl_names_raw` 
	SET inputSpecies=CONCAT_WS(' ', strSplit(inputTaxon,' ', 1),  strSplit(inputTaxon,' ', 2) )
	;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));


echo "  Counting rows per species_binomial...";
$sql="
	UPDATE `$tbl_names_raw` a JOIN (
	SELECT inputSpecies, COUNT(*) AS rows
	FROM `$tbl_names_raw`
	GROUP BY inputSpecies
	) b
	ON a.inputSpecies=b.inputSpecies
	SET a.inputSpeciesRows=b.rows
	;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

echo "  Populating accepted nameIDs:\n";

echo "    Joining by full taxon name...";
$sql="
	UPDATE `$tbl_names_raw` syn JOIN `$tbl_names_raw` acc
	ON syn.outputTaxon=acc.inputTaxon
	SET syn.accNameID=acc.nameID,
	syn.updateMethod='syn.outputTaxon=acc.inputTaxon'
	WHERE syn.status='synonym'
	;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

echo "    Joining by species...";
$sql="
	UPDATE `$tbl_names_raw` syn JOIN `$tbl_names_raw` acc
	ON syn.outputTaxon=acc.inputSpecies
	SET syn.accNameID=acc.nameID,
	syn.updateMethod='syn.outputTaxon=acc.inputSpecies'
	WHERE syn.accNameID IS NULL
	AND syn.status='synonym'
	AND acc.inputSpeciesRows=1
	;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_fail));

?>
