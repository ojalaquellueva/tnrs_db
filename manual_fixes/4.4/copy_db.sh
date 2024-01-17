# Shell commands for copying database from dev to production

cd ~/bien/tnrs/backups
mysqldump -u boyle -p tnrs_dev > tnrs_db_v4_4_20240117.sql
mysqladmin -u boyle -p create tnrs_4_4
mysql --compress -u root --password="$(cat /home/boyle/bien/config/mysql_root)" tnrs_4_4 < tnrs_db_v4_4_20240117.sql
rm tnrs_db_v4_4_20240117.sql
