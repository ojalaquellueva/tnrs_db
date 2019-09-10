<?php
//////////////////////////////////////////////////////////
// Purpose:
// Set names of default famiy columns
//////////////////////////////////////////////////////////

echo "Determining default family field: ";
$sql="
	SELECT sourceName
	FROM source
	WHERE isDefault=1;
";
$defaultSource=sql_get_first_result($dbh, $sql,'sourceName');
$default_family_fld="family_".$defaultSource;
$fld_default_family=$default_family_fld;

echo "$default_family_fld\r\n";	

?>
