# TNRS DATABASE LOADING SCRIPTS

Purpose: Creates, populates and indexes the TNRS database
See: http://tnrs.iplantcollaborative.org/
Author: Brad Boyle (ojalaquellueva@gmail.com)
Latest update: 27 March 2019
Version: 4.1
Compatible with new TNRSbatch application and TNRSapi

NOTE: This README not yet fully coverted the Git Markdown, some formatting may still be wonky

## CONTENTS
INTRODUCTION  
VERSION  
REQUIREMENTS  
  SOFTWARE  
  COMPATIBILITY  
  SOURCE DATA   
INSTRUCTIONS  
  TEST BUILD  
  BUILD OF CURRENT TNRS PRODUCTION DATABASE  
  BUILD OF TNRS DATABASE USING REFRESHED DATA FOR EXISTING SOURCES  
  ADDING NEW SOURCES - SIMPLIFIED DARWIN CORE  
  ADDING NEW SOURCES - NOT SIMPLIFIED DARWIN CORE    
CHANGE LOG  
AUTHOR & CONTACT INFORMATION  

## INTRODUCTION

Files in this directory and subdirectories contains all scripts and data needed to build the current (as of 13 Jan. 2016) reference database for the iPlant 
Taxonomic Name Resolution Service or TNRS (http://tnrs.iplantcollaborative.org). You should also use these scripts to update existing data sources or add new  data sources. 


## VERSION

Code version (this application): 4.1  
Code version note: Based on v4.0, but PHP code updated to compatibility with PHP 7.2  
Version date: 27 March 2019  
Most recent database version: 4.0  
Most recent database release date: 28 August 2015  
TNRS application compatibility: Compatible with TNRS v.4.0  

## REQUIREMENTS

### SOFTWARE
* Unix-like operating system (OS X, Ubuntu, Debian, etc).
* PHP 5.5.30 (cli) or newer. Probably will not work on versions >=7.0 due to 	
  deprecation of legacy mysql extension (not tested).
* MySQL 5.5.13 or newer.
* Perl 5.22.1 (for dbfdump and Tropicos api download)
* Perl utility DBD-XBase-1.05 (for command dbfdump)

### COMPATIBILITY
* Compatible with TNRS version 4.0

### SOURCE DATA 

Extracts from the following data sources must be present in the data 
directories within their respective import directores (e.g., 
import\_tropicos/data/). These data sources are not imported automatically; they 
must be obtained separately in advance of running this application. For details 
on requesting, extracting and preparing source data, see the individual readme
in the respective import directories.

* GCC (http://dixon.iplantcollaborative.org/CompositaeWeb/default.aspx). Global
  Compositae Checklist.
* ILDIS (http://www.ildis.org). International Legume Database & Information
  Service.
* TROPICOS (www.tropicos.org).
* TPL (http://www.theplantlist.org). The Plant List.
* USDA (http://plants.usda.gov/java/). USDA Plants.
* NCBI (http://www.ncbi.nlm.nih.gov/guide/taxonomy/). NCBI Taxonomy. NOTE:   
  Do NOT refresh data for NCBI. Changes in data structure for the NCBI
  taxonomy download will cause the current to fail. NCBI cannot be updated
  until (if and when) the NCBI-specific import scripts have been updated to
  handle these changes.


## INSTRUCTIONS

The file "load\_tnrs.php" runs a complete build of the TNRS database. This 
script calls all others. Prior to running this script:

1. Check that all key parameters are correctly set in global\_params.inc (in 
   application root directory). 
2. Obtain data file(s) for each source and copy to the data folder within that
   source's import directory (e.g., import\_tropicos/data/).
3. Set source-specific parameters in the params.inc file for that source (also 
   in import directory).

### TEST BUILD

For a preliminary test build (recommended) of the TNRS database using small 
extracts of a subset of data sources, do the following.

1. Edit global parameters (file "global\_params.inc")
* Set $src\_array as to use example data source, as follows (just uncomment if
  already present):
  
$src\_array=array(
	"dwcExample",
	"gccExample",
	"usdaExample"
);

* Ensure that paths to directories "functions/" and "global\_utilities/" are 
  correct (parameters $local\_utilities\_path and $global\_utilities\_path in 
  section "Include paths and filenames").
* Set server and MySQL connection parameters in section "Db connection info"

2. Run the master script:

$ php load\_tnrs.php

Example database build should complete in under a minute.

### BUILD OF CURRENT TNRS PRODUCTION DATABASE

For a complete build of the current TNRS database (ver. 4.0) using all 
existing data sources, do the following.

1. Edit global parameters (file "global\_params.inc")
* Set $src\_array as follows:
  
$src\_array=array(
	"tpl",
	"gcc",
	"ildis",
	"tropicos",
	"usda",
	"ncbi"
);

* Ensure that paths to directories "functions/" and "global\_utilities/" are 
  correct (parameters $local\_utilities\_path and $global\_utilities\_path in 
  section "Include paths and filenames").
* Set server and MySQL connection parameters in section "Db connection info"

2. Run the master script:

$ php load\_tnrs.php

Database build should take several hours to a full day, depending
on system resources. Each step, including any errors detected, will echo to the
terminal screen. To avoid tying up a terminal or accidentally aborting due to a
lost connection, I recommend running the process remotely using the unix 
"screen" utility.

### BUILD OF TNRS DATABASE USING REFRESHED DATA FOR EXISTING SOURCES

The procedure to refresh one or more data sources, keeping all remaining data 
sources unchanged, is identical to the procedure above. The only difference is
that you must first replace the old raw data file for the source to be refreshed
with the new (refreshed) data file, and update any source-specific parameters
as needed.

For example, if you are refreshing ONLY the data for Tropicos, do the following:

1. Copy the new tropicos data file to the tropicos data directory: 
   "import\_tropicos/data/". You can name the file whatever you want, but I 
   recommend that the file name include the date of download.
2. Edit the source parameters file ("params.inc") in the source directory (in this
   example, "import\_tropicos/".
   * Change $dateAccessed to the download date of the data file
   * Change $namesfile to the name of the data file. This is critical.
   
Repeat for any other refreshed data source, then run the remaining steps from
the preceding section (BUILD OF CURRENT TNRS PRODUCTION DATABASE).

The above procedure will work if and only if the schema of the refreshed data
source is the same as the current version. If the schema has changed, the import
for that source will almost certain fail. Because a complete build can take 
many hours, I recommend running a trial build using only the single source to 
be refreshed. If that source loads successfully, then the complete
build should also run successfully. If the import fails, you will need to 
diagnose how the new data dump differs from the previous source, and either (a)
obtain a new dump conforming to the old schema, or (b) modify the import scripts
for that source.

Note that refreshing one or more sources requires rebuilding the entire 
database. Although the global parameters file (global\_params.inc) contains a 
parameter that in theory allows you to refresh only an individual source within
an existing database (this is done by setting "$replace\_db = false;"), I do NOT
recommend you use this option. This option has not been tested since several
major changes were made to the database scripts, and may introduce anomalies if
used.

### ADDING NEW SOURCES - TNRS SIMPLE DARWIN CORE

This simplest way to build a custom TNRS database which includes one or more 
new data sources this is to ensure that the data extract for each source 
conforms to the TNRS Simple Darwin Core schema. This schema is described
in the readme found within the TNRS Simple Darwin Core (DWC) example import 
directory  ("import\_dwcExample/"). Please refer to this readme for detailed 
specifications of this schema. 

Every source MUST have a unique short, alphanumeric code ([sourceName], above), 
without spaces or punctuation (e.g., "tropicos", "tpl", "gcc", etc.). I 
recommend using only lowercase alphabetic characters. This short name will be
displayed in the TNRS application as the code for the source, so choose 
carefully. 

Once you have restructured you new data extract to match the TNRS Simplified 
Darwin Core schema, do the following:

1. Make a new copy of the entire DWC example directory
2. Rename the the new directory, changing the suffix "dwcExample" to the code 
   of the new source (e.g., "import\_mynewsource").
3. Place the data extract within the data subdirectory of the import directory.
4. Edit the source parameters file ("params.inc") in the source import 
   directory:
   * Set $sourceName to the code for this source. [critical]
   * Set $sourceNameFull to a longer, human-readable name of this source
   * Set $sourceUrl to the url where data was obtained [optional]
   * Set $dateAccessed to the download date of the data file
   * Set $namesfile to the name of the data file. [critical]
5. Modify the parameter $src\_array in the global parameters file 
   ("global\_params.inc") to include the code for the new source.

At this stage, I recommend running a trial build using only the new source, to 
confirm that it loads successfully on its own (to do so, set $src\_array equal 
only to the code for the new source). If the source file fails to 
import correctly or does not import at all, try adjusting the MySQL import
parameters at the end of the source parameters file. Most commonly you will 
need to adjust "$lines\_terminated\_by" (either "\n", "\r" or "\r\n") and 
"$fields\_terminated\_by" (typically "," or "\t"). Also check that accented 
characters are loaded properly. If this is not the case, try setting 
"$fix\_chars=true" in the source parameter file. 

Once each new source has been test-loaded separately, you may then perform a 
complete build by modifying $src\_array to include the codes for all data 
sources.

### ADDING NEW SOURCES - NOT SIMPLIFIED DARWIN CORE

If for some reason you cannot restructure the new data to conform to the
TNRS Simplified Darwin Core Schema, you will need to write a new set
of custom import scripts. Describing how to so do in detail is beyond the scope 
of this document. 

As a general approach to learning how to write a custom import script, I 
recommend the following:

1. Examine in detail the Simplified DWC import scripts (in "import\_dwcExample"). 
   These are the simplest. 
2. Examine more complex custom import scripts, in particular for Tropicos. 
3. Learn the structure of the staging table ("nameStaging"). Your goal is to 
   restructure the new data into this table, performing all necessary 
   validations. To produce an example of this table, run a partial import of a 
   single existing source which you know loads successfully, for example 
   Tropicos. Before doing so, set a breakpoint to stop the operation immediately
   after import. This is done by inserting an abort command ("die();") after 
   the line in "load\_tnrs.php" that runs the import for an single source 
   ("include\_once $src\_dir."import.php";", currently line 151). Now, get into 
   the new database and example the contents of the staging table. If you can
   import your data into this table and ensure that it satisfied all key 
   valdations, then it will import successfully to the final database.


## OVERVIEW OF THE STEPS IN BUILDING THE TNRS DATABASE

This section provides an over of the major steps performed by the TNRS DB 
loading files. Files performing a set of related operations are group into a 
single directory, where they are called by a single master scripts bearing the
same base name as the containing directory. The master script (extension .php) 
calls all others (extensions .inc). The main steps are as follows:

1. create\_tnrs\_core.php (in create\_tnrs\_core/)
   * Creates empty tnrs database
2. import.php (in import\_[sourceName]/) 
   * Imports raw data for an individual taxonomic source into MySQL and 
   performs initial loading to the staging table (nameStaging)
   * Steps specific to an individual source are in this directory
3. prepare\_staging.php (in prepare\_staging/)
   * Finishes structuring and populating staging table (nameStaging)
   * These operations are universal, not source-specific
4. load\_core\_db.php (in load\_core\_db/)
   * Normalizes the contents of the staging table to the core database
5. make\_genus\_family\_lookups (in genus\_family\_lookups/)
   * Builds lookup tables of current and historic genus-in-family 
   classifications, based on GRIN taxonomy website
6. taxamatch\_tables.php (in taxamatch\_tables/)
   * Denormalizes names in core database into lookup tables used by TaxaMatch 
   fuzzy matching application
7. build\_classifications.php (in build\_classifications/)
   * Builds table 'higherClassification', which classifies all names from all 
     sources according to any source for which isHigherClassification=1 (set in 
     params.inc for that source)

For a build from multiple sources, step 1 is run ONCE. Steps 2-4 are run for EACH 
source. Finally, steps 5-6 are run ONCE.

The entire process is sequenced by the master script load\_tnrs.php, which calls
all the others. Before running this script, you MUST set critical parameters in 
global\_params.inc. Also, set source-specific parameters in params.inc in the 
import directory for each source. See instructions in load\_tnrs.php, 
global\_params.inc. For details on setting source-specific parameters, see the 
readme file in import\_dwcExample/.

An individual source can be refreshed without rebuilding the entire database by
loading source only and setting $replace\_db=false (in global\_params.inc). This 
will run steps 2-7 above, replacing only names linked uniquely to the source in 
question. For a faster replace, set $replace=false in params.inc for the source
being refreshed. Only entirely new names from that source will be added. 
Existing names (and metadata such as source urls and date of access) will not be
changed. WARNING: Reloading of individual sources not recommended until this 
option has been updated.

## CHANGE LOG

Version 3.6.3.

1. Added scripts in directory tropicos\_fixes/. These are fixes specific to 
   tropicos. Are not part of the pipeline, but should be run separately after 
   completing build of the database. See readme in tropicos\_fixes.

Version 3.6: 

1. Changed Tropicos import routine to include three additional fields: 
   NomenclatureStatusID, NomenclatureStatusName, Symbol. These fields are 
   returned by Tropicos API, and provide additional information regarding 
   nomenclatural status. Values in the three fields are equivalent 
   representations of the same value. For names where the Tropicos 
   ComputedAcceptance algorithm does not provide a taxonomic opinion (as 
   indicated by NULL value of `acceptance`, the value of NomenclatureStatusName
   is transfered to `acceptance` WHERE NomenclatureStatusName IN 
   ('Illegitimate','Invalid'). NomenclatureStatusName='nom. rej.' is translated 
   as "Rejected name' and transfered to `acceptance`. The goal of transferring 
   these values is to alert the user that the name in question is problematic, 
   even if Tropicos does not provide a link to the accepted name.   
   
Version 4.0:

1. Changes to support the import of new data sources TPL (The Plant List) and 
   ILDIS (International Legume Database & Information Service). 
2. Automated tropicos\_fixes/ (added to main TNRS pipeline)
3. Standardized rank names to non-abbreviated form 
   * Previous db had mix of abbreviated and full
     rank names
   * Standard botanical rank indicator abbreviations  
     still used to form infraspecific taxon names

Version 4.1 (27 March 2019)

1. Updated PHP code  to php7.2
2. Updated main README and README for dwcExample

## AUTHOR & CONTACT INFORMATION
Brad Boyle
bboyle@email.arizona.edu
