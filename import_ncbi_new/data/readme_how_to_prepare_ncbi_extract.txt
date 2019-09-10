-- How to prepare NCBI taxonomy extract for import to TNRS database

1. Download taxdump.tar.gz from NCBI Taxonomy ftp site (ftp://ftp.ncbi.nih.gov/pub/taxonomy/) to this directory (import_ncbi/data/)
2. Uncompressed taxdump.tar.gz (tar -xzf taxdump.tar.gz)
3. Run SQL scripts in extract_ncbi_names.sql (in this directory) to import NCBI names file (names.dmp) to MySQL. Be sure to enter valid values for 'databasename' and 'path_from_root/' before running commands
4. Run the following shell command to dump all distinct names from column name_txt to a plain text file:

mysql -u username -p -B databasename -e "select distinct name_txt from ncbi_names" > ncbi_names.txt

5. Upload 'ncbi_names.txt' to the TNRS (http://tnrs.iplantcollaborative.org/TNRSapp.html) using the "Upload and Submit List" tab. Make sure option "my file contains an identifier as first column" is unchecked
6. Under "Processing Mode Settings" select "Perform name resolution".
7. Press "Submit List"
8. When finished, download parsed results file, rename it to "ncbi_names_parsed.txt" (or whatever file name you chose for $names_parsed_file in params.inc) and place in folder data/