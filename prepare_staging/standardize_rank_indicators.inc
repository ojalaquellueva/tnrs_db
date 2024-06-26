<?php
// Standardizes rank indicators for infraspecific taxa
// Infraspecific taxa should have been parsed and rank
// indicator field populated prior to this step

echo "  Standardizing trinomial rank indicators:";
$sql="
	SELECT DISTINCT `$rank_ind_fld` as `rank`
	FROM `$tbl_staging`
	WHERE `$rank_ind_fld` IS NOT NULL;
";
$rows = mysqli_query($dbh, $sql);
$num_rows = mysqli_num_rows($rows);
$n=1;

if ($num_rows>0) {
	while ($row=mysqli_fetch_array($rows, MYSQLI_ASSOC)) {
		$rank=$row['rank'];
		$rankStd=stdRankIndicator($rank);
		echo "  \r                                                                 ";
		echo "  \r  Standardizing trinomial rank indicators...$n of $num_rows";

		// Update rank
		$sql_update_rank="
			UPDATE `$tbl_staging` 
			SET 
			`$rank_ind_fld`=\"$rankStd\",
			`$name_fld`=REPLACE($name_fld,\"$rank\",\"$rankStd\")
			WHERE `$rank_ind_fld`=\"$rank\";
		";
		$msg_error="\r\nFailed to update $rank_ind_fld for rank='$rank'!\r\n";
		if (sql_execute($dbh, $sql_update_rank,FALSE,$echo_on,'',$msg_error));
		$n++;

	}
}
echo "  \r                                                                 ";
echo "  \r  Standardizing trinomial rank indicators...done\r\n";

echo "  Standardizing quadrinomial rank indicators:";
$sql="
	SELECT DISTINCT `$rank_ind_fld2` as `rank`
	FROM `$tbl_staging`
	WHERE `$rank_ind_fld2` IS NOT NULL;
";
$rows = mysqli_query($dbh, $sql);
$num_rows = mysqli_num_rows($rows);
$n=1;

if ($num_rows>0) {
	while ($row=mysqli_fetch_array($rows, MYSQLI_ASSOC)) {
		$rank=$row['rank'];
		$rankStd=stdRankIndicator($rank);
		echo "  \r                                                                 ";
		echo "  \r  Standardizing quadrinomial rank indicators...$n of $num_rows";

		// Update rank
		$sql_update_rank="
			UPDATE `$tbl_staging` 
			SET 
			`$rank_ind_fld2`=\"$rankStd\",
			`$name_fld`=REPLACE($name_fld,\"$rank\",\"$rankStd\")
			WHERE `$rank_ind_fld2`=\"$rank\";
		";
		$msg_error="\r\nFailed to update $rank_ind_fld for rank='$rank'!\r\n";
		if (sql_execute($dbh, $sql_update_rank,FALSE,$echo_on,'',$msg_error));
		$n++;

	}
}
echo "  \r                                                                 ";
echo "  \r  Standardizing quadrinomial rank indicators...done\r\n";

echo "  Correcting erroneous rank indicators...";
// Mainly needed for ncbi names, where names of all rank are tagged with
// rank of accepted name
// Doesn't catch all instances, but should help with names species and below

// fix taxa erroneously labeled as family
$sql="
	UPDATE $tbl_staging 
	SET $rank_fld='unknown'
	WHERE $rank_fld='family' AND $name_fld NOT LIKE '%aceae' 
	AND $name_fld NOT IN ('Cruciferae','Guttiferae','Umbelliferae','Compositae','Leguminosae','Palmae','Labiatae','Gramineae');
";
$msg_error="Failed to correct mislabeled families!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));

// Add missing "subsp." rank indicator
$sql="
	UPDATE $tbl_staging 
	SET $rank_ind_fld='subsp.'
	WHERE $rank_fld='subspecies' 
	AND $infraepithet_fld IS NOT NULL 
	AND $rank_ind_fld IS NULL;
";
$msg_error="Failed to correct subspecies!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));

// Convert ssp. to subsp. in full name
// For some reason is slipping through above standardizations
$sql="
	UPDATE $tbl_staging 
	SET $name_fld=REPLACE($name_fld,' ssp. ',' subsp. ')
	WHERE $name_fld LIKE '% ssp. %'
	;
";
$msg_error="Failed to correct 'ssp.'!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));

// fix forma abbreviation in full name
$sql="
	UPDATE $tbl_staging 
	SET $name_fld=REPLACE($name_fld,' f. ',' fo. ')
	WHERE $rank_fld='forma';
";
$msg_error="Failed to correct formas!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));

// standardize variety rank
$sql="
	UPDATE $tbl_staging 
	SET $rank_fld='variety'
	WHERE $rank_fld='varietas';
";
$msg_error="Failed to standardize varieties!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

// Replace 'cv..' with 'cv.'
// Another weird one slipping throughm, no idea...
$sql="
	UPDATE $tbl_staging 
	SET $name_fld=REPLACE($name_fld,' cv.. ',' cv. ')
	WHERE $name_fld LIKE '% cv.. %'
	;
";
$msg_error="Failed to correct 'cv..' in name!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));
$sql="
	UPDATE $tbl_staging 
	SET $rank_ind_fld='cv.'
	WHERE $rank_fld='cv..'
	;
";
$msg_error="Failed to correct 'cv..' in rankIndicator!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,'',$msg_error));

echo "  Hard-wired fixes for erroneous rankIndicator2 values...";
$sql="
UPDATE $tbl_staging 
SET rankIndicator2=NULL,
infraspecificEpithet2=NULL,
otherEpithet=NULL
WHERE rankIndicator2 IN ('alfred','de','Dulce','jamasakura','Loriceum','magis','manitra','nucipersica','obtuse')
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

/*
// Not sure why this is here; it only makes sense in the loop above
// keep for now.
// Standardize cases where nameRank is used as rank indicator
$sql="
	UPDATE $tbl_staging 
	SET $name_fld=REPLACE($name_fld,\"$rank\",\"$rankStd\")
	WHERE `$rank_ind_fld` IS NOT NULL;
";
$msg_error="Failed to correct nameRank used as rank indicator!\r\n";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));
*/
?>
