Imports raw dump of names and synonyms and adds to staging table. 

These scripts & parameters are specific to a particular data source. This version imports an extract of names and synonymy from the USDA Plants website (using advanced search page, http://plants.usda.gov/adv_search.html). See file usdaExample.csv for an example of the extract schema. These scripts will import any file conforming to this schema (assuming no anomalies in the nameID-parentNameID links. 

Once import has been completed and the staging table populated, subsequent steps (indexing
of staging table, error-checking and normalization to core db tables) 
are universal and do not require any source-specific customizations.

Files to be imported MUST be in this directory.

Specific steps:

(1) Creates raw data table(s) for importing
(2) Creates main staging table
(3) Imports raw text files of names and synonyms into MySQL (raw data tables)
(4) Adds these names and synonyms from raw data table to main staging table

Master scripts: import.php. Calls all others.
Parameters: in params.inc; also see global_params.inc

See readme in data directory for details on how to obtain data for this source.


