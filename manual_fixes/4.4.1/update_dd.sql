-- ----------------------------------------------------------------------
-- Modify data dictionary table schema and content to include definitions 
-- of output from modes 'parse' and 'syn'
-- ----------------------------------------------------------------------

USE tnrs_4_4;

-- Add new column for mode
ALTER TABLE dd_output
ADD COLUMN `mode` VARCHAR(50) FIRST
;

-- Update mode for all existing entries
UPDATE dd_output
SET mode='resolve'
;

-- Change primary key to make col_name unique within mode
ALTER TABLE dd_output DROP PRIMARY KEY, 
ADD PRIMARY KEY(mode, col_name)
;

-- Insert new definitions for mode='parse'
INSERT INTO dd_output 
(mode, col_name, ordinal_position, data_type, description)
VALUES 
('parse', 'ID', 1, 'integer', 'Integer identifier (added by TNRS)'),
('parse', 'Name_submitted', 2, 'text', 'Name submitted'),
('parse', 'Family', 3, 'text', 'Family name'),
('parse', 'Genus', 4, 'text', 'Genus name'),
('parse', 'Specific_epithet', 5, 'text', 'Specific epithet'),
('parse', 'Infraspecific_rank', 6, 'text', 'Rank abbreviation of infraspecific taxon'),
('parse', 'Infraspecific_epithet', 7, 'text', 'Epithet of intraspecific taxon'),
('parse', 'Infraspecific_rank_2', 8, 'text', 'Rank abbreviation of lower infraspecific taxon'),
('parse', 'Infraspecific_epithet_2', 9, 'text', 'Epithet of lower intraspecific taxon'),
('parse', 'Author', 10, 'text', 'Author of the name'),
('parse', 'Annotations', 11, 'text', 'Standard btanical annotations (not part of name)'),
('parse', 'Unmatched_terms', 12, 'text', 'Trailing unmatched text'),
('parse', 'WarningsEng', 13, 'text', 'Warnings')
;

-- Insert new definitions for mode='syn'
INSERT INTO dd_output 
(mode, col_name, ordinal_position, data_type, description)
VALUES 
('syn', 'submitted_name', 1, 'text', 'Name submitted'),
('syn', 'matched_nameWithAuthor', 2, 'text', 'Name matched, with author'),
('syn', 'matched_taxonomicStatus', 3, 'text', 'Name matched taxonomic status'),
('syn', 'accepted_nameWithAuthor', 4, 'text', 'Accepted name, with author'),
('syn', 'accepted_source', 5, 'text', 'Taxonomic source of accepted name'),
('syn', 'accepted_nameUrl', 6, 'text', 'Hyperlink to accepted name in taxonomic source'),
('syn', 'syn_nameWithAuthor', 7, 'text', 'Synonym with author'),
('syn', 'syn_taxonomicStatus', 8, 'text', 'Synonym taxonomic status'),
('syn', 'syn_source', 9, 'text', 'Taxonomic source of synonym'),
('syn', 'syn_nameUrl', 10, 'text', 'Hyperlink to synonym in taxonomic source'),
('syn', 'accepted_nameWithAuthor_strict', 11, 'text', 'Exact accepted name (may be child of accepted name)')
;
