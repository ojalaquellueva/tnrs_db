#!/bin/bash

##############################################################
# Application parameters
# Check and change as needed
##############################################################

# Db and schema to validate
DB="tnrs_dev"

# Set process names, for notification and screen echo,
# depending on which is being run
if [ "$local_basename" == "validate_db_dev_private" ]; then
	pname_local="Validate TNRS database '"$DB"'"
else
	pname_local="$local_basename"
fi

# List of required tables
# One table name per line, no commas or quotes
required_tables="
classification
collaborator
family_acceptedFamily_lookup
famlist
genlist
genlist_famlist_combined
genlist_new_test
gf_lookup
higherClassification
infra1list_splist_combined
infra2list_infra1list_combined
meta
name
name_source
source
splist_genlist_combined
synonym
"

# Miscellaneous required columns to check
# Use to check for columns accidentally purged by CREATE TABLE AS operations
# Format: 
# TABLE_NAME,COLUMN_NAME
# One couplet per line, separated by comma, no comma at end, no quotes
# To omit this test, set to empty string ("")
required_columns=""

# Basenames of SQL files containing validation fk checks
# See inidividual files for details
taxonomic_checks="
check_fk_gnrs
check_fk_cds
check_fk_tnrs
check_fk_nsr
check_fk_cods_promimity
check_fk_cods_keyword
"

# Tables to check for present of validation fkeys
validation_fkeys_check_tables="
${vfoi}
agg_traits
"

# Valiation fkey columns to check
validation_fk_cols="
fk_tnrs_id
fk_gnrs_id
fk_cds_id
nsr_id
cods_proximity_id
cods_keyword_id
"

