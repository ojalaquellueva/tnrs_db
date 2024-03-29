<?php

////////////////////////////////////////////////////////////////////////////////
// Purpose:
// Loops through GRIN genus table, extracting genus, accepted family, and
// parsing out all previous family classifications for that genus from 
// column `othfamily`. For each family found in othfamily, inserts a record 
// into table `genus_family_lookup` containing the genus, family (accepted 
// family), and altfamily (alternate family classification). Also inserts
// one record for the accepted family itself; that is, with accepted 
// family also listed as both family and altfamily.
////////////////////////////////////////////////////////////////////////////////

echo "Inserting genus records...";
$msg_error="Failed!\r\n";

// Get all genus records from source table
$query="
	SELECT genus, family, othfamily
	FROM genus;
";
$result=mysqli_query($dbh, $query);
$num_rows=mysqli_num_rows($result);
$curr_row=0;

// Loop through records, adding one at at time to destination table
if ($num_rows>0) {
	while ($row=mysqli_fetch_array($result, MYSQLI_ASSOC)) {
		$genus=$row['genus'];
		$prim_family=$row['family'];
		$arr_fams=array($prim_family);
		$othfamily=$row['othfamily'];
		$arr_othfamilies=explode(";",$othfamily);	// tokenize this field
		
		if(trim($arr_othfamilies[0]<>'')) {
			 // merge all associated families into one array		
			$arr_fams=array_merge((array)$arr_fams,(array)$arr_othfamilies);		
		}

		foreach($arr_fams as $fam1) {
			foreach($arr_fams as $fam2) {

			$curr_row++;
			$fam1==$prim_family?$isPrimary=1:$isPrimary=0;
			// insert genus+family combination
			echo "\rInserting genus records...$curr_row";
			$sql="
				INSERT INTO `$fg` 
				(
				genus,
				family,
				altFamily,
				isPrimary
				)
				VALUES 
				(
				trim('$genus'),
				trim('$fam1'),
				trim('$fam2'),
				$isPrimary
				);
			";
			$msg_error="Failed to insert genus+family combination (genus='$genus', family1=$fam1, family2=$fam2)\r\n";
			if (sql_execute($dbh, $sql,TRUE,$echo_on,'',$msg_error));
			}
		}
	}
}
echo "\rInserting genus records...$curr_row\r\n";

?>
