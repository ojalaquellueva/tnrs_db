<?php

///////////////////////////////////////////////////////////
// Renames error tables, appending source-specific suffix
///////////////////////////////////////////////////////////

echo "Renaming error tables...";

$err_tbls=array(
	"error_table",
	"duplicateNames",
	"orphanSpecies"
);

foreach ($err_tbls as $err_tbl) {
	if ( exists_table($dbh, $err_tbl) ) {
		$err_tbl_src = $err_tbl . "_" . $src;
		$sql="ALTER TABLE $err_tbl RENAME TO $err_tbl_src";
		sql_execute_multiple($dbh, $sql);
	}
}

echo "done\n";

?>