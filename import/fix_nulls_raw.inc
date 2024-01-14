<?php

/////////////////////////////////////////////////////
// Substitutes \N for NULL in raw data file
/////////////////////////////////////////////////////

echo "Standardizing NULLs in raw data file:\r\n";

echo "  File '$namesfile'...";
$namesfileandpath = $filepath.$namesfile;
$namesfileandpath_temp = $namesfileandpath.".temp";
$cmd = "sed -e 's/NULL/\\\N/g' $namesfileandpath > $namesfileandpath_temp";
system($cmd);
$cmd = "mv $namesfileandpath_temp $namesfileandpath";
system($cmd);
echo $done;

?>