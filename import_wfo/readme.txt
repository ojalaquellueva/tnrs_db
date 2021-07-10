Imports data dump of The Plant List (TPL) to the TNRS database

Raw data format

Data was received as single zip file

Instructions

- Place the zipped raw data files in subdirectory data/
- Edit params.inc (this directory), updating the following as needed:
	
	$sourceUrl [only change if home page has changed since last load]
	$dateAccessed
	$namesfile1 [name of the first zipped data file]
	$namesfile2 [name of the second zipped data file]
	
- Edit 'MySQL LOAD DATA INFILE parameters' in param.inc if needed.
  I recommend doing a test load by inserting a break near the end 
  of the main file (import.php) in this directory. E.g.,
  
  die("Stopping code...");
  
  Inspect their raw data table (tpl_raw). If no records imported or 
  other issues, try changing the MySQL import parameters, especially
  $lines_terminated_by.
- The files in this directory and these instructions assume that the 
  raw data file type, compression, character encoding and schema have
  not changed. If any of these have changes, the import probably will 
  not work and the import scripts will need to be updated accordingly.
  
See readme in data directory for details on how to obtain data for this source.
	
	