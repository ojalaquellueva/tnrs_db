<?php

$sql_create_gf_lookup_table="
DROP TABLE IF EXISTS `$fg`;
CREATE TABLE `$fg` (
	genus VARCHAR(255) NOT NULL,
	family VARCHAR(255) NOT NULL,
	altFamily VARCHAR(255) NOT NULL,
	isPrimary INTEGER(1) UNSIGNED DEFAULT NULL,
	INDEX(genus),
	INDEX(family),
	INDEX(altFamily),
	INDEX(isPrimary)
) ENGINE=INNODB DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci;
";

?>