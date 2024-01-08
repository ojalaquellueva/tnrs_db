<?php

///////////////////////////////////////////////////////////////////////
// Create mysql tables identical in structure to raw data files
///////////////////////////////////////////////////////////////////////

// Create the empty tables
echo "Creating table `$tbl_names_acc_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_names_acc_raw`;
CREATE TABLE `$tbl_names_acc_raw` (
`type` VARCHAR(250) DEFAULT NULL,
`uuid` VARCHAR(250) DEFAULT NULL,
`fullName` VARCHAR(250) DEFAULT NULL,
`pureName` VARCHAR(250) DEFAULT NULL,
`author` VARCHAR(250) DEFAULT NULL,
`fullTitleCache` VARCHAR(250) DEFAULT NULL,
`RANK` VARCHAR(50) DEFAULT NULL,
`taxon` VARCHAR(250) DEFAULT NULL,
`treeIndex` VARCHAR(250) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Creating table `$tbl_names_syn_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_names_syn_raw`;
CREATE TABLE `$tbl_names_syn_raw` (
`type` VARCHAR(250) DEFAULT NULL,
`synonym` VARCHAR(250) DEFAULT NULL,
`uuid` VARCHAR(250) DEFAULT NULL,
`fullName` VARCHAR(250) DEFAULT NULL,
`pureName` VARCHAR(250) DEFAULT NULL,
`author` VARCHAR(250) DEFAULT NULL,
`fullTitleCache` VARCHAR(250) DEFAULT NULL,
`rank` VARCHAR(50) DEFAULT NULL,
`accepted_ID` VARCHAR(250) DEFAULT NULL,
`acc_fullName` VARCHAR(250) DEFAULT NULL,
`treeIndex` VARCHAR(250) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Creating table `$tbl_names_raw`...";
$sql="
DROP TABLE IF EXISTS `$tbl_names_raw`;
CREATE TABLE `$tbl_names_raw` (
`nameID` VARCHAR(250) DEFAULT NULL,
`accNameID` VARCHAR(250) DEFAULT NULL,
`name` VARCHAR(250) DEFAULT NULL,
`author` VARCHAR(250) DEFAULT NULL,
`rank` VARCHAR(50) DEFAULT NULL,
`nameType` VARCHAR(250) DEFAULT NULL,
`taxonomicStatus` VARCHAR(50) DEFAULT NULL,
`concept` VARCHAR(250) DEFAULT NULL,
`fullName` VARCHAR(250) DEFAULT NULL,
`fullTitleCache` VARCHAR(250) DEFAULT NULL,
`acc_fullName` VARCHAR(250) DEFAULT NULL,
`treeIndex` VARCHAR(250) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;


?>