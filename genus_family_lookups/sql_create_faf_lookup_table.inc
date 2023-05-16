<?php

$sql_create_faf_lookup_table="
DROP TABLE IF EXISTS `$faf`;
CREATE TABLE `$faf` (
	family VARCHAR(255) NOT NULL,
	acceptedFamily VARCHAR(255) NOT NULL,
	INDEX(family),
	INDEX(acceptedFamily)
) ENGINE=INNODB DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci;
";

?>