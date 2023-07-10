-- -----------------------------------------------------------------
-- Create data dictionary of TNRS output -----------------------------------------------------------------

DROP TABLE IF EXISTS dd_output;
CREATE TABLE dd_output (
col_name varchar(100),
ordinal_position integer NOT NULL,
data_type varchar(25) NOT NULL,
description text  NOT NULL,
PRIMARY KEY (`col_name`)
);

INSERT INTO dd_output (col_name, ordinal_position, data_type, description)
VALUES 
('ID', 1, 'Integer', 'Unique integer identifier assigned by TNRS'),
('Name_submitted', 2, 'Text', 'Verbatim name submitted by user'),
('Overall_score', 3, 'Float', 'Overall match score'),
('Name_matched_id', 4, 'Integer', 'Identifier of matched name in source database'),
('Name_matched', 5, 'Text', 'Matched name (no author)'),
('Name_score', 6, 'Float', 'Match score of name, not including author'),
('Name_matched_rank', 7, 'Text', 'Taxonomic rank of matched name'),
('Author_submitted', 8, 'Text', 'Author submitted by user'),
('Author_matched', 9, 'Text', 'Author matched'),
('Author_score', 10, 'Float', 'Match score of author'),
('Canonical_author', 11, 'Text', 'Canonical (official) author of matched name in source database'),
('Name_matched_accepted_family', 12, 'Text', 'Accepted family of matched name'),
('Genus_submitted', 13, 'Text', 'Genus submitted by user'),
('Genus_matched', 14, 'Text', 'Genus matched'),
('Genus_score', 15, 'Float', 'Match score of genus'),
('Specific_epithet_submitted', 16, 'Text', 'Specific epithet submitted by user'),
('Specific_epithet_matched', 17, 'Text', 'Specific epithet matched'),
('Specific_epithet_score', 18, 'Float', 'Match score of species (genus + specific epithet)'),
('Family_submitted', 19, 'Text', 'Family submitted by user'),
('Family_matched', 20, 'Text', 'Family matched'),
('Family_score', 21, 'Float', 'Match score of family'),
('Infraspecific_rank', 22, 'Text', 'Infraspecific rank, if applicable'),
('Infraspecific_epithet_matched', 23, 'Text', 'Infraspecific epithet matched'),
('Infraspecific_epithet_score', 24, 'Float', 'Match score of infraspecfic taxon'),
('Infraspecific_rank_2', 25, 'Text', 'Second-level infraspecific rank, if applicable'),
('Infraspecific_epithet_2_matched', 26, 'Text', 'Second-level infraspecific epithet matched'),
('Infraspecific_epithet_2_score', 27, 'Float', 'Match score of second-level infraspecfic taxon'),
('Annotations', 28, 'Text', 'Standard taxonomic annotations detected'),
('Unmatched_terms', 29, 'Text', 'Remaining unmatched terms, if any'),
('Name_matched_url', 30, 'Text', 'URL of name matched in source database'),
('Name_matched_lsid', 31, 'Text', 'LSID of name matched in source database'),
('Phonetic', 32, 'Text', 'Is matched name phonetically identical to submitted name?'),
('Taxonomic_status', 33, 'Text', 'Taxonomic status of matched name'),
('Accepted_name', 34, 'Text', 'Accepted name of matched name'),
('Accepted_species', 35, 'Text', 'Accepted species of matched name'),
('Accepted_name_author', 36, 'Text', 'Author of accepted name'),
('Accepted_name_id', 37, 'Text', 'Identifier of accepted name in source database'),
('Accepted_name_rank', 38, 'Text', 'Taxonomic rank of accepted name'),
('Accepted_name_url', 39, 'Text', 'URL of accepted name in source database'),
('Accepted_name_lsid', 40, 'Text', 'LSID of accepted name in source database'),
('Accepted_family', 41, 'Text', 'Accepted family of accepted name'),
('Overall_score_order', 42, 'Integer', 'Match result ranked by Overall_score (1=best)'),
('Highertaxa_score_order', 43, 'Integer', 'Match result ranked by best scoring higher taxon (1=best)'),
('Source', 44, 'Text', 'Taxonomic source(s) returning this match'),
('Warnings', 45, 'Text', 'Warnings (inspect carefully, if any)'),
('selected', 46, 'TRUE/FALSE', 'Match is best match (according to TNRS algorithm)'),
('unique_id', 47, 'Text', 'Optional user-supplied identifier')
;

ALTER TABLE dd_output ADD INDEX (col_name);
ALTER TABLE dd_output ADD INDEX (ordinal_position);




