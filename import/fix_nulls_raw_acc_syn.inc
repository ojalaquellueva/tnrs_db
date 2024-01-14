<?php

/////////////////////////////////////////////////////
// Substitutes \N for NULL in raw data file
// This version for separate accepted and synonym names files
/////////////////////////////////////////////////////

echo "Standardizing NULLs in raw data files:\r\n";

$namesfile=$namesfile_acc;
echo "  File '$namesfile'...";
$namesfileandpath = $filepath.$namesfile;
$namesfileandpath_temp = $namesfileandpath.".temp";
$cmd = "sed -e 's/NULL/\\\N/g' $namesfileandpath > $namesfileandpath_temp";
system($cmd);
$cmd = "mv $namesfileandpath_temp $namesfileandpath";
system($cmd);
echo $done;

$namesfile=$namesfile_syn;
echo "  File '$namesfile'...";
$namesfileandpath = $filepath.$namesfile;
$namesfileandpath_temp = $namesfileandpath.".temp";
$cmd = "sed -e 's/NULL/\\\N/g' $namesfileandpath > $namesfileandpath_temp";
system($cmd);
$cmd = "mv $namesfileandpath_temp $namesfileandpath";
system($cmd);
echo $done;


?>