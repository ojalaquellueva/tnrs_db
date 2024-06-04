-- -------------------------------------------------------------------
-- Add version comments column and insert new version
-- Schema changes NOT yet added to pipeline!!!
-- -------------------------------------------------------------------

-- Rename ID column same as other API meta tables
ALTER TABLE meta
RENAME COLUMN meta_id TO id
;

-- Add version comments column
ALTER TABLE meta
ADD COLUMN version_comments text DEFAULT NULL
;

-- Add minor DB update data column
ALTER TABLE meta
ADD COLUMN db_update_date DATE DEFAULT NULL AFTER build_date
;


INSERT INTO meta (
app_version,
db_version,
build_date,
db_update_date,
db_code_version,
code_version,
api_version,
citation,
publication,
logo_path,
version_comments
)
VALUES ( 
'5.3.1',
'4.4.1',
'2024-01-17',
'2024-06-04',
'4.4.1',
'5.1',
'5.3.2',
'@misc{tnrs, author = {Boyle, B. L. and Matasci, N. and Mozzherin, D. and Rees, T. and Barbosa, G. C. and Kumar Sajja, R. and Enquist, B. J.}, journal = {Botanical Information and Ecology Network}, title = {Taxonomic Name Resolution Service, version 5.1}, year = {2021}, url = {https://tnrs.biendata.org/}, note = {Accessed <date_of_access>} }',
'@article{tnrspub, author = {Boyle, B. and Hopkins, N. and Lu, Z. and Garay, J. A. R. and Mozzherin, D. and Rees, T. and Matasci, N. and Narro, M. L. and Piel, W. H. and McKay, S. J. and Lowry, S. and Freeland, C. and Peet, R. K. and Enquist, B. J.}, journal = {BMC Bioinformatics}, number = {1}, pages = {16}, title = {The taxonomic name resolution service: an online tool for automated standardization of plant names}, volume = {14}, year = {2013}, doi = {10.1186/1471-2105-14-16} }',
'',
'Modify data dictionary table (dd_output) schema and content to include definitions of output from modes \'parse\' and \'syn\''
)
;
