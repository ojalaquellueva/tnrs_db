#!/bin/bash

#########################################################################
# Purpose: Validates completed database
#
# Notes:
#	1. Parameters specifying database, schema, etc. are loaded from 
#		parameter file params.sh. 
#	2. Sets of parameters relevant to a particular database should be
#		be backed up by saving a copy of the params file with an 
#		appropriate suffix (e.g., "params.sh.tnrs_dev"). Copy and 
#		replace the main params.sh file with the appropriate database-
#		specific params backup file.
#  
# Author: Brad Boyle (bboyle@email.arizona.edu)
#########################################################################

: <<'COMMENT_BLOCK_x'
COMMENT_BLOCK_x
#echoi $e; echoi $e "EXITING script `basename "$BASH_SOURCE"`"; exit 0

######################################################
# Set parameters, load functions & confirm operation
# 
# Loads local parameters only if called by master script.
# Otherwise loads all parameters, functions and options
######################################################

# Get local working directory
DIR_LOCAL="${BASH_SOURCE%/*}"
if [[ ! -d "$DIR_LOCAL" ]]; then DIR_LOCAL="$PWD"; fi

# $local = name of this file
# $local_basename = name of this file minus ='.sh' extension
# $local_basename should be same as containing directory, as  
# well as local data subdirectory within main data directory, 
# if local data directory needed
local=`basename "${BASH_SOURCE[0]}"`
local_basename="${local/.sh/}"
pname="$local_basename"

# Set working directory to current directory if running independently &
# suppress main message
if [ -z ${master+x} ]; then
	DIR=$DIR_LOCAL
	suppress_main='true'
else
	suppress_main='false'
fi

# Load paramerters, function and get command line options
source "$DIR/params.sh"
source "$CONFIG_PATH/db_config.sh"
source "$DIR/../includes/functions.sh"	
source "$DIR/../includes/get_options.sh"	

# Begin timer
start=`date +%s%N`; prev=$start		# Get start time
pid=$$								# Set process ID

# Set default pname if applicab
if [ "$pname" == "" ]; then pname="$local_basename"; fi

# Send start message if mail option set
if [[ "$m" = "true" ]]; then source "$DIR/../includes/mail_process_start.sh"; fi	

######################################################
# Custom confirmation message. 
# Will only be displayed if running as
# standalone script and -s (silent) option not used.
######################################################

if [[ "$i" = "true" && -z ${master+x} ]]; then 

	# Reset confirmation message
	msg_conf="$(cat <<-EOF

	Process '$pname' will use following parameters: 
	
	Database to validate: 	$DB
	DB type: 		$DBMS
	Host: 			$HOST
	User: 			$USER
	
EOF
	)"		
	confirm "$msg_conf"
fi

#########################################################################
# Main
#########################################################################

echoi $e ""
echoi $e "------ Executing process '$pname' ------"
echoi $e ""

######################################################
# Set error tracking parameters
######################################################

errs=0

######################################################
# Check required tables and columns
######################################################

echoi $e "Checking existence of required tables:"
for tbl in $REQUIRED_TABLES; do
	echoi $e -n "- $tbl..."
	sql_exists_table="SELECT EXISTS (SELECT TABLE_NAME FROM information_schema.tables WHERE table_schema = '${DB}' AND table_name = '${tbl}') AS exists_tbl"
	if [[ $(mysql --login-path=$LOGINPATH -sse "$sql_exists_table") == 0 ]]; then
		echoi $e "FAIL!"
		let "errs++"
	else
		echoi $e "pass"
	fi
done

echoi $e -n "Checking existence of required columns:"
if [ "$REQUIRED_COLUMNS" == "" ]; then
	echoi $e " [nothing to check]"
else
	echoi $e ""
	for tblcol in $REQUIRED_COLUMNS; do
		tblcol2=${tblcol//,/ }	# Replace all ',' with ' ', the default IFS
		tblcol_arr=($tblcol2)	# Split into array using IFS
		tbl=${tblcol_arr[0]}
		col=${tblcol_arr[1]}
		tblcol_disp=${tblcol/,/.}	# Convert to std tbl.col format

		echoi $e -n "- $tblcol_disp..."
		sql_exists_col="SELECT EXISTS (SELECT COLUMN_NAME FROM information_schema.columns WHERE table_schema = '${DB}' AND table_name = '${tbl}' AND COLUMN_NAME = '${col}') AS exists_col"
		if [[ $(mysql --login-path=$LOGINPATH -sse "$sql_exists_col") == 0 ]]; then
			echoi $e "FAIL!"
			let "errs++"
		else
			echoi $e "pass"
		fi
	done
fi

######################################################
# Run checks from sql scripts
######################################################

echoi $e "Checking validation fkeys not all null:"

for check in $CHECKS; do
	echoi $e -n "- $check..."
	test=$(mysql --login-path=$LOGINPATH --database="$DB" -sse "source sql/${check}.sql")
	
	if [[ "$test" == 0 ]]; then
		echoi $e "FAIL!"
		let "errs++"
	else
		echoi $e "pass"
	fi
done

######################################################
# Report errors
######################################################

echoi $e
if [ "$errs" -gt 0 ]; then 
	echoi $e "Total errors found: $errs"
else
	echoi $e "No errors found"
fi

######################################################
# Report total elapsed time and exit 
######################################################


#echoi $e "Process '$pname' completed in "
source "$DIR/../includes/finish.sh"