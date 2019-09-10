Imports Global Compositae Checklist

Once import has been completed and the staging table populated, subsequent steps (indexing
of staging table, error-checking and normalization to core db tables) 
are universal and do not require any source-specific customizations.

Source-specific scripts MUST be in this directory. Place raw data file in subdirectory data/

Specific steps:

(1) Creates raw data table(s) for importing
(2) Creates main staging table (standard step for all import scripts)
(3) Imports raw text files of names and synonyms into MySQL (raw data tables)
(4) Adds these names and synonyms from raw data table to main staging table

Master scripts: import.php. Calls all others.
Parameters: in params.inc; also see global_params.inc
Raw data: in subdirectory data/

WARNING: Data file name must not contain spaces. Rename it if it does.

See readme in data/ directory for details on how to obtain data dump

