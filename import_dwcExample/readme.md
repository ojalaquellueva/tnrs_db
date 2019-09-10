# Import template and sample data in  TNRS Simple Darwin Core format

## Overview

Use this template to import taxonomic reference data in TNRS Simple Darwin Core (DwC) format. TNRS Simple DwC is a TNRS-specific format for taxonomic data, with all information stored in single plain text file. Most columns and their names are identical to DwC Taxon terms, as listed at http://rs.tdwg.org/dwc/terms/index.htm. Columns not represented in the current version of DwC  are indicated by an asterisk (*) after the column name. 

## File format

To use this import template, you taxonomic source data must match the format of the example file "dwcExample.csv" in the directory data/. In particular, it must have the following columns in the order shown:

| Column name | Meaning 
| ----------- | -------
| taxonID		| Required. Unique identifier for each taxon (name). Can be character 	or numeric. MUST be unique for each record. 
| parentNameUsageID	| Link to identifier (taxonID) of most proximate parent taxon. Required 	for any taxon that has a parent. Taxa without a parent will be linked to the root. Orphan parentNameUsageIDs (linking to nonexistent taxonIDs) will be linked to the root. WARNING: circular parentNameUsageID-taxonID links will cause database loading to fail.
| taxonRank	| Required. Differs slight from DwC specification in that this is the fully spelled (not abbreviated) English name of the rank of the taxon. You MUST use the following controlled vocabulary (similar to http://code.google.com/p/darwincore/wiki/Taxon#taxonRank, under column "English", except "forma" instead of "form", more extensive vocabulary): kingdom, subkingdom, superdivision, division, subdivision, superclass, class, subclass, order, suborder, family, subfamily, tribe, subtribe, section, subsection, series, subseries, genus, subgenus, species, subspecies, variety, subvariety, forma, subforma, cultivar, unranked 
| family	| Optional but recommended. 
| scientificName| Required. The fully formed scientific name, without the authority.
| scientificNameAuthorship | Optional but recommended. This is the terminal authority of the taxon. Please do not include any internal authorities (for example, if the name is a subspecies, this should be the authority for the subspecies, not the species. Required if your list contains homonyms (duplicate names  disambiguated only by authority).
| genusHybridMarker*	| Optional but recommended. Leave blank if not a hybrid name. The TNRS loading scripts will detect most hybrids.
| genus | Required if taxon at rank of genus or lower.
| speciesHybridMarker* | Optional but recommended. Leave blank if not a hybrid name. The TNRS loading scripts will detect most hybrids.
| specificEpithet | Required if taxon at rank of species or lower. Just the epithet; do not include the genus portion of a species name. Leave blank for hybrid formula names (e.g., Adiantum latifolium x petiolatum).
| infraspecificRank* | Required if name is an infraspecific trinomial (e.g., "Poa annua var. supina"). This is the abbreviated rank indicator included in names of subspecies, varieties, etc. Not directly equivalent to any Darwin Core term. Controlled vocabulary as per abbreviations as used in the ICBN Vienna code (http://ibot.sav.sk/icbn/main.htm; see esp. Section 5): "subsp.", "var.", "subvar.", "fo.", "subfo.", "cv.". The TNRS will attempt to parse this value from the scientificName if column infraspecificRank is left blank. The TNRS has an extensive library of infraspecific rank indicators and their variants and will attempt to standardize any variant abbreviations. Leave blank if taxon is at rank of species or higher. 
| infraspecificEpithet | Required if taxon is subspecies, variety, forma, etc.  Tribes and subgeneric taxa such as section and series (e.g., Psychotria sect. Notopleura) can be entered by leaving specificEpithet blank (null) and entering the rank indicator in infraspecificRank and epithet infraspecificEpithet.
| infraspecificRank2* | Required if name is an infraspecific quadrinomial (e.g., "Silene laciniata ssp. major var. angustifolia"). These will be taxa of ranks variety, forma, subforma, etc. Not directly equivalent to any DwC term. Controlled vocabulary as per abbreviations as used in the ICBN Vienna code (http://ibot.sav.sk/icbn/main.htm; see esp. Section 5): "var.", "subvar.", "fo.", "subfo.", "cv.". 
| infraspecificEpithet2* | Required if taxon is an infraspecific quadrinomial (see infraspecificRank2, above). Not directly equivalent to any Darwin Core term. If used, infraspecificRank2 as well as all higher taxonomic name component fields must be populated.
| taxonomicStatus | Short indicator of taxonomic status. If name is a synonym, more detailed reason for (nomenclaturally) invalid or illegitimate names can be used. If left blank (null), TNRS will treat name as "No opinion" (=unresolved). Current controlled vocabulary supported: "Accepted", "Synonym", "Invalid", "Illegitimate", NULL.
| acceptedNameUsageID | Optional but recommended if taxonomicStatus is "Synonym", "Invalid", or "Illegitimate". Link to taxonID of accepted name. 
| taxonUri | 	Optional but recommended. Hyperlink to name in original database.
| lsid	| Optional. LSID, if known. 

## Prepare taxonomy file for import

1. Parse names. If your taxonomic list contains only concatenated names, use the TNRS in parse-only mode to break the names into their atomic components (http://tnrs.iplantcollaborative.org/TNRSapp.html).
2. Check file format. Make sure your file contains only the columns listed above. You can also use example file dwcExample.csv (in the directory data/) as a template for prepating your data. 

## Set up import directory and prepare source-specific parameter file

1. Choose a short one-word code for this data source. For example, "mysource". Source code MUST be unique within your TNRS database.
2. Created a new, source-specific import directory, import\_\[sourcecode\] (e.g., "import\_mysource").
3. Copy this directory and its contents to the new directory.
4. Place the file in the data subdirectory inside the import directory.
5. Edit params.inc, making the following mandatory changes:  
  1. $sourceName="\[sourcecode\]"
     * Example, $sourceName="mysource"
  2. $is\_higher\_classification="false"
     * Set to true only if you want families of this taxonomic source to be used as a family classification for all other sources in the database.
  3. $filepath="import\_\[sourcecode\]/data/"
     * Example $filepath="import_dwcExample/data/"
  4. $namesfile = "[taxonomic source file name]"
     * Use the name and extension of the taxonomic data file you placed in folder data/.
  5. Set "MySQL LOAD DATA INFILE" parameters
     * Make sure these parameters are appropriate for the format of your file 
     * * For more information, see `https://dev.mysql.com/doc/refman/8.0/en/load-data.html`.
6. Edit other optional parameters in source-specific params file as desired
7. If you are importing other taxonomic sources, prepare a separate import directory for each source.	
	
## Build the database:

1. Edit global_params.inc, making the following changes:
  1. Add your source name(s) to array $src_array. For example,

		```
		$src_array=array(
			"mysource"
		);
		```
	
	  or (multiple sources):

		```
		$src_array=array(
			"mysource",
			"someothersource",
			"yetanothersource"
		);
		```
		
  2. Set any other parameters as needed, in particular $replace_db and all parameters in section "Db connection info". Note that source names in array $src_array (in global_params.inc) MUST match the values
of $sourceName in params.inc for each source AND the suffix of each import directory.
		
2. Run script "load_tnrs.php"


		


