<?php

//////////////////////////////////////////////////////////
// Removes unneeded or temporary tables after database
// rebuild is complete. Raw data tables and staging
// tables are moved to backup db, the remainder
// are dropped altogether
//////////////////////////////////////////////////////////

echo "Cleaning up...";

// Drop raw ncbi tables
// Hard-wired because I'm lazy
// Delete if not applicable
$sql="
	DROP TABLE IF EXISTS names_parsed;
	DROP TABLE IF EXISTS ncbi_citations;
	DROP TABLE IF EXISTS ncbi_delnodes;
	DROP TABLE IF EXISTS ncbi_division;
	DROP TABLE IF EXISTS ncbi_gencode;
	DROP TABLE IF EXISTS ncbi_merged;
	DROP TABLE IF EXISTS ncbi_names;
	DROP TABLE IF EXISTS ncbi_nodes;
";
sql_execute_multiple($dbh, $sql);

// Backup or drop remaining raw data tables
if ($use_db_backup && isset($DB_BACKUP)) {
	// move raw data tables (except for ncbi) to backup db
	
	foreach ($src_array as $src) {
		
		if ($src<>'ncbi') {
			$tbl_raw = $src."_raw";
			if (exists_table($dbh, $tbl_raw)) {
				$sql="
					DROP TABLE IF EXISTS ".$DB_BACKUP.".".$tbl_raw.";
					CREATE TABLE ".$DB_BACKUP.".".$tbl_raw." LIKE ".$tbl_raw.";
					INSERT INTO ".$DB_BACKUP.".".$tbl_raw." SELECT * FROM ".$tbl_raw.";
					DROP TABLE ".$tbl_raw.";
				";
				sql_execute_multiple($dbh, $sql);		
			}	
			// Backup "verbatim_raw" table
			// This is used if (verbatim) raw data table is first loaded
			// to sDwC table, prior to loading to staging table
			
			$tbl_raw_verbatim = $src."_raw_verbatim";
			if (exists_table($dbh, $tbl_raw_verbatim)) {
				$sql="
					DROP TABLE IF EXISTS ".$DB_BACKUP.".".$tbl_raw_verbatim.";
					CREATE TABLE ".$DB_BACKUP.".".$tbl_raw_verbatim." LIKE ".$tbl_raw_verbatim.";
					INSERT INTO ".$DB_BACKUP.".".$tbl_raw_verbatim." SELECT * FROM ".$tbl_raw_verbatim.";
					DROP TABLE ".$tbl_raw_verbatim.";
				";
				sql_execute_multiple($dbh, $sql);					
			}

		}
		
	}
	
} else {
	// Just drop them
	
	foreach ($src_array as $src) {
		$sql="
			DROP TABLE IF EXISTS ".$src."_raw;
			DROP TABLE IF EXISTS ".$src."_raw_verbatim;
		";
		sql_execute_multiple($dbh, $sql);
	}
	
}

// drop last version of staging table
$sql="
	DROP TABLE IF EXISTS nameStaging;
";
sql_execute_multiple($dbh, $sql);

// Get rid of extra taxamatch tables if you didnt delete them earlier
$sql="
	DROP TABLE IF EXISTS `infra1list`;
	DROP TABLE IF EXISTS `infra2list`;
	DROP TABLE IF EXISTS `splist`;
";
sql_execute_multiple($dbh, $sql);

// DROP "forward-compatible" tables currently not used
$sql="
	DROP TABLE IF EXISTS fuzzyMatch;
	DROP TABLE IF EXISTS name_lexicalGroup;
	DROP TABLE IF EXISTS lexicalGroup;
";
sql_execute_multiple($dbh, $sql);

// Drop error report tables
// Currently this is source-specific, and pertains to the 
// last source loaded. Consider saving a separate version
// for each source in backup db. Some day...
$sql="
	DROP TABLE IF EXISTS error_table;
	DROP TABLE IF EXISTS duplicateNames;
	DROP TABLE IF EXISTS orphanSpecies;
";
sql_execute_multiple($dbh, $sql);

echo "done\r\n\r\n";

?>
