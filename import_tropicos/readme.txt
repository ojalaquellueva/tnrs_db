Imports raw dump of names and synonyms and adds to staging table. 

These scripts & parameters are specific to a particular data source. This version imports an extract of names and synonymy, accessed using the Tropicos API. See file tropicos_api_extract_example.csv for an example of the extract schema. These scripts will import any file conforming to this schema (assuming no anomalies in the nameID-parentNameID links. 

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

Last changed: 29 March 2013
Changes this version: Changed Tropicos import routine to include three additional fields: NomenclatureStatusID, NomenclatureStatusName, Symbol. These fields are returned by Tropicos API, and provide additional information regarding nomenclatural status. Values in the three fields are equivalent representations of the same value. For names where the Tropicos ComputedAcceptance algorithm does not provide a taxonomic opinion (as indicated by NULL value of `acceptance`, the value of NomenclatureStatusName is transfered to `acceptance` WHERE NomenclatureStatusName IN ('Illegitimate','Invalid'). NomenclatureStatusName='nom. rej.' is translated as "Rejected name' and transfered to `acceptance`. The goal of transferring these values is to alert the user that the name in question is problematic, even if Tropicos does not provide a link to the accepted name.   


