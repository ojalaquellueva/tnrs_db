-- -----------------------------------------------------------------
-- Manual fixes for a couple of glitches in TNRS DB v4.3
-- -----------------------------------------------------------------

--
-- 1. Embedded single quote in column source.description
-- Causes "sources" metadata query to fail
--

USE tnrs_4_3;

-- Note escape in "world\'s"
UPDATE source
SET description="The WFO is an open-access, Web-based compendium of the world\'s plant species. It is a collaborative, international project, building upon existing knowledge and published Floras, checklists and revisions"
WHERE sourceID=1
;
-- Shorten WFO description while we're at it
UPDATE source
SET description="The World Checklist of Vascular Plants (WCVP) is a global consensus view of all known vascular plant species (flowering plants, conifers, ferns, clubmosses and firmosses)"
WHERE sourceID=2
;

--
-- Add missing final curly braces to TNRS publication citation bibtex
-- Also: update original bibtex file
--

UPDATE meta
SET publication="@article{tnrspub, author = {Boyle, B. and Hopkins, N. and Lu, Z. and Garay, J. A. R. and Mozzherin, D. and Rees, T. and Matasci, N. and Narro, M. L. and Piel, W. H. and McKay, S. J. and Lowry, S. and Freeland, C. and Peet, R. K. and Enquist, B. J.}, journal = {BMC Bioinformatics}, number = {1}, pages = {16}, title = {The taxonomic name resolution service: an online tool for automated standardization of plant names}, volume = {14}, year = {2013}, doi = {10.1186/1471-2105-14-16}}"
;
