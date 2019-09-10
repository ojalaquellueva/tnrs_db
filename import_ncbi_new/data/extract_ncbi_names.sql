-- Use these scripts to import file names.dmp to MySQL and
-- export just the names column as file "ncbi_names.txt"
-- These files are then uploaded manually to TNRS for parsing
-- You MUST enter valid values for 'databasename' and 'path_from_root/'
-- before running these commands

USE databasename;

DROP TABLE IF EXISTS ncbi_names;
CREATE TABLE ncbi_names (
tax_id INT(11) UNSIGNED NOT NULL,
name_txt VARCHAR(250) NOT NULL,
unique_name VARCHAR(250) DEFAULT NULL,
name_class VARCHAR(250) DEFAULT NULL
) ENGINE=MYISAM DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;

LOAD DATA LOCAL INFILE 'path_from_root/names.dmp'
INTO TABLE ncbi_names
FIELDS TERMINATED BY '\t|\t'
LINES TERMINATED BY '\t|\n'
IGNORE 1 LINES;

-- Be sure to check that record count from table = line count from file - 1

-- Delete quoted names
-- They serve no purpose taxonomically and screw up database loading
-- by creating duplicate entries (due to removal of quotes during parsing)
DELETE FROM ncbi_names
WHERE name_txt LIKE "'%" OR name_txt LIKE "\"%";
