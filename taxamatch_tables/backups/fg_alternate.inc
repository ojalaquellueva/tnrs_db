<?php
// Prepares temporary table of alternative genus-family classifications
// using gf_lookup table, and appends to genlist_famlist_combined
// Table `gf_lookup` must be present!

// create temporary table 
echo "Importing alternate genus-family classification...";

$msg_error="Failed to drop previous temporary table `temp_gf`!\r\n";
$sql = "DROP TABLE IF EXISTS `temp_gf`;";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));


$msg_error="Failed to create temporary table `temp_gf`!\r\n";
$sql = "
	CREATE TABLE `temp_gf` (
  	`family` varchar(100) NOT NULL,
	`genus` varchar(100) NOT NULL,
	key `temp_gf_family`(`family`),
	key `temp_gf_genus`(`genus`)
	) ENGINE=MyISAM DEFAULT CHARSET=utf8;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));

// Import results text file to table
$msg_error = "Failed to insert genera & families into table `temp_gf`!\r\n";
$sql = "
	INSERT INTO temp_gf (
	genus,
	family	
	)
	SELECT DISTINCT
	genus,
	family
	FROM gf_lookup;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Add alternate records to combined table
// this load all possible NEW family-genus combos
echo "Adding alternate genus-family classification...";
$msg_error = "failed!\r\n";
$sql = "
	INSERT INTO `genlist_famlist_combined` (
		genus_id,
		genus,
		family_id,
		family,
		family_genus
	)
	SELECT DISTINCT
		GENUS_ID,
		genus,
		FAMILY_ID,
		family,
		famgen
	FROM
	(
		SELECT DISTINCT
		g.GENUS_ID, gf.genus, gf.family, f.FAMILY_ID, CONCAT_WS(' ', gf.family,gf.genus) as famgen
		FROM genlist g INNER JOIN temp_gf gf INNER JOIN famlist f
		ON g.GENUS=gf.genus AND gf.family=f.FAMILY
	) as gf 
	LEFT JOIN (
		SELECT DISTINCT CONCAT_WS(' ', family,genus) as famgen2 
		FROM genlist_famlist_combined
	) AS gf2
	ON gf.famgen=gf2.famgen2
	WHERE gf2.famgen2 IS NULL
	;
	";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,"",$msg_error));

$msg_error="Failed to drop temporary table `temp_gf`!\r\n";
$sql = "DROP TABLE IF EXISTS `temp_gf`;";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

?>
