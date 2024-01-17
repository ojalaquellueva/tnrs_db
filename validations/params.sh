#!/bin/bash

##############################################################
# Application parameters
# Check and change as needed
##############################################################

# DB to validate & connection parameters
DB="tnrs_dev"
HOST="localhost";	
USER="tnrs"
DBMS="MySQL"; # For display only

# Path to config directory for confidential connection parameters
# Set working directory $DIR in main script
# Include config directory name & omit trailing slash
CONFIG_PATH="$DIR/../../config"

# Set process names, for notification and screen echo,
# depending on which is being run
if [ "$local_basename" == "validate_db_dev_private" ]; then
	pname_local="Validate TNRS database '"$DB"'"
else
	pname_local="$local_basename"
fi

# logfile options
mkdir -p log	
glogfile="log/logfile_${local_basename}.log"
appendlog="false"


# List of required tables
# One table name per line, no commas or quotes
REQUIRED_TABLES="
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
REQUIRED_COLUMNS="
name,nameID
name_source,sourceID
"
REQUIRED_COLUMNS=""

# Basenames of SQL files containing validation fk checks
# See inidividual files for details
CHECKS="
name_not_empty
bad_families
unknown_family
bad_rankIndicator
bad_infraspecificRank2
check_acceptance
nameRank_lower
rankIndicator_lower
infraspecificRank2_lower
"

####################################
# Notification options
####################################

# Custom process name for echo and emails
# Optional. Comment out or set to "" to use main file basename
pname="Validate TNRS"

# Supply email here if using -m option
email="bboyle@arizona.edu"
