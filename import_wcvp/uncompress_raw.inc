<?php

/////////////////////////////////////////////////////
// Uncompresses the raw data files and concatenates
// into single file
/////////////////////////////////////////////////////

echo "Uncompressing raw data files...";
$cmd="unzip -p ".$filepath."'".$namesfile1_compressed."' > ".$filepath.$namesfile1;
system($cmd);
$cmd="unzip -p ".$filepath."'".$namesfile2_compressed."' > ".$filepath.$namesfile2;
system($cmd);
echo $done;

echo "Concatenating uncompressed files...";
$cmd = "( cat ".$filepath.$namesfile1." ; tail -n +2 ".$filepath.$namesfile2." ) > ".$filepath.$namesfile;
system($cmd);
// remove the uncompressed partial files
$cmd = "rm ".$filepath.$namesfile1." ".$filepath.$namesfile2;
system($cmd);
echo $done;

?>