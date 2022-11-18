-- --------------------------------------------------------------
-- Add TNRS read-only user to the newly-created database
-- --------------------------------------------------------------

GRANT SELECT ON tnrs_dev.* TO 'tnrs'@'localhost' IDENTIFIED BY 'tnrs_read';