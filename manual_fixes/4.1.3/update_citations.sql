-- --------------------------------------------------------------------
-- Repeat for any active instance DB
-- Version below is for DB tnrs on vegbiendev
-- NOTE 1: Schema changes for table meta added to main db pipeline
-- NOTE 2: Insert of citation/publication content NOT yet added
--   to main DB pipeline
-- --------------------------------------------------------------------

USE tnrs;

UPDATE source
SET citation='@misc{tropicos,
address = {St. Louis, USA},
author = {{Missouri Botanical Garden}},
publisher = {Missouri Botanical Garden},
title = {Tropicos},
url = {http://www.tropicos.org},
note = {Accessed 30 May 2020}
}'
WHERE sourceName='tropicos'
;

UPDATE source
SET citation='@misc{tpl,
title = {The Plant List, version 1.1},
year = {2013},
url = {http://www.theplantlist.org},
note = {Accessed 26 June 2020}
}'
WHERE sourceName='tpl'
;

UPDATE source
SET citation='@misc{usda,
address = {Greensboro, NC, USA},
author = {{USDA, NRCS}},
publisher = {National Plant Data Team},
title = {The PLANTS Database},
url = {http://plants.usda.gov},
note = {Accessed 3 July 2020}
}'
WHERE sourceName='usda'
;

ALTER TABLE meta
ADD COLUMN publication text
;

UPDATE meta
SET publication='@article{tnrspub,
author = {Boyle, B. and Hopkins, N. and Lu, Z. and Garay, J. A. R. and Mozzherin, D. and Rees, T. and Matasci, N. and Narro, M. L. and Piel, W. H. and McKay, S. J. and Lowry, S. and Freeland, C. and Peet, R. K. and Enquist, B. J.},
journal = {BMC Bioinformatics},
number = {1},
pages = {16},
title = {The taxonomic name resolution service: an online tool for automated standardization of plant names},
volume = {14},
year = {2013},
doi = {10.1186/1471-2105-14-16}
}'
;

UPDATE meta
SET citation='@misc{tnrs,
author = {Boyle, B. L. and Matasci, N. and Mozzherin, D. and Rees, T. and Barbosa, G. C. and Kumar Sajja, R. and Enquist, B. J.},
journal = {Botanical Information and Ecology Network},
title = {Taxonomic Name Resolution Service, version 5.0},
year = {2021},
url = {https://tnrs.biendata.org/},
note = {Accessed <date_of_access>}
}'
;

