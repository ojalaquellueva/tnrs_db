<?php
// Insert names from raw import table into staging table

echo "Merging separate raw data tables into `$tbl_names_raw`:\r\n";

echo "  `$tbl_names_acc_raw`...";
$msg_error = "Failed!";
$sql="
INSERT INTO `$tbl_names_raw` (
`nameID`,
`accNameID`,
`taxonomicStatus`,
`name`,
`author`,
`rank`,
`nameType`,
`concept`,
`fullName`,
`fullTitleCache`,
`acc_fullName`,
`treeIndex`
)
SELECT
`uuid`,
NULL,
'Accepted',
`pureName`,
`author`,
`RANK`,
`type`,
`taxon`,
`fullName`,
`fullTitleCache`,
NULL,
`treeIndex`
FROM `$tbl_names_acc_raw`;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));

echo "  `$tbl_names_syn_raw`...";
$msg_error = "Failed!";
$sql="
INSERT INTO `$tbl_names_raw` (
`nameID`,
`accNameID`,
`taxonomicStatus`,
`name`,
`author`,
`rank`,
`nameType`,
`concept`,
`fullName`,
`fullTitleCache`,
`acc_fullName`,
`treeIndex`
)
SELECT
`uuid`,
`accepted_ID`,
'Synonym',
`pureName`,
`author`,
`rank`,
`type`,
`synonym`,
`fullName`,
`fullTitleCache`,
`acc_fullName`,
`treeIndex`
FROM `$tbl_names_syn_raw`;
";
if (sql_execute($dbh, $sql,$die_on_fail,$echo_on,$msg_success,$msg_error));



?>
