-- ------------------------------------------------------------------
-- Grant access to user 'tnrs' on database 'tnrs_4_4'
-- ------------------------------------------------------------------

-- Check if user has access to database:

SELECT * FROM mysql.db WHERE Db = 'tnrs_4_4' and User='tnrs';

-- Grant access to the new database

GRANT SELECT ON tnrs_4_4.* TO 'tnrs'@'localhost';
FLUSH PRIVILEGES;
