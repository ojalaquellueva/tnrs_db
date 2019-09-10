<?php
////////////////////////////////////////////////////////////////
// Purpose:
// Backs up completed staging table. This prevents loss of 
// staging table for current source when new source is loaded
// Backup database and backup staging table name are set in 
// global_params.inc
////////////////////////////////////////////////////////////////

echo "  Backing up staging table to `$DB_BACKUP`.`$tbl_staging_bak`...";
$do_backup=true;

if (exists_table_in_db($dbh, $tbl_staging_bak,$DB_BACKUP)){
	$msg="\r\n  Delete existing table `$tbl_staging_bak` in database `$DB_BACKUP`? (yes/no): ";
	if (responseYesNoDie($msg)===false) {
		$msg="\r\n  Continue without backing up? (yes/no): ";
		if (responseYesNoDie($warningMsg)===false) {
			die("\r\nOperation cancelled\r\n";
		}else{
			$do_backup=false;
		}
	}else{
		echo "    Proceeding with backup...";
	}
}

if ($do_backup===true) {
	$sql="
	DROP TABLE IF EXISTS `$DB_BACKUP`.`$tbl_staging_bak`;
	";
	$msg_error="failed to delete previous table `$DB_BACKUP`.`$tbl_staging_bak`!\r\n";
	if (sql_execute($dbh, $sql,TRUE,$echo_on,"",$msg_error));

	$sql="
	CREATE TABLE `$DB_BACKUP`.`$tbl_staging_bak` LIKE `$DB`.`$tbl_staging`;
	";
	$msg_error="failed to create table `$DB_BACKUP`.`$tbl_staging_bak`!\r\n";
	if (sql_execute($dbh, $sql,TRUE,$echo_on,"",$msg_error));

	$sql="
	INSERT INTO `$DB_BACKUP`.`$tbl_staging_bak` SELECT * FROM `$DB`.`$tbl_staging`
	";
	$msg_error="failed to insert into table `$DB_BACKUP`.`$tbl_staging_bak`!\r\n";
	if (sql_execute($dbh, $sql,TRUE,$echo_on,$msg_success,$msg_error));
}
?>
