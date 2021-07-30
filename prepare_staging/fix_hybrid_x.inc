<?php
// converts extended ascii hybrid "×" characters to plain ascii "x"

$encoded_x="×";
$plain_x="x";

echo "  Standarizing hybrid 'x'...";
$sql="
UPDATE `$tbl_staging` 
SET `$name_fld`=REPLACE(`$name_fld`,'$encoded_x','$plain_x ')
;
UPDATE `$tbl_staging` 
SET `$name_fld`=REPLACE(`$name_fld`,'  ',' ')
;
UPDATE `$tbl_staging` 
SET `$name_fld`=REPLACE(`$name_fld`,CHAR(195),'$plain_x ')
;
UPDATE `$tbl_staging` 
SET `$name_fld`=REPLACE(`$name_fld`,'  ',' ')
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


?>
