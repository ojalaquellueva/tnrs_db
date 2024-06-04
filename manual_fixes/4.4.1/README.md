# BIEN DB 4.4.1 updates

## Overview

Minor update to support data dictionary content for multiple modes. Date: 4 June 2024.

## Changes
* Modify data dictionary table schema and content to include definitions of output from modes 'parse' and 'syn'
  * Add column `mode` to table `dd_output`
  * Set `mode`='resolve' for existing rows
  * Add column definitions for `mode`='parse'
  * Add column definitions for `mode`='syn'
* Modify schema, table `meta`
  * Add columns `db_update_date` & `version_comments`
* Add new version record

## Notes
* ***Schema changes NOT yet added to pipeline!!!***
