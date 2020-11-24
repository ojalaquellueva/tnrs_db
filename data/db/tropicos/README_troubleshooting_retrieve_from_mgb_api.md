# Configuring and running retrieve_from_mbg_api.pl

### Trial #1: 

```
perl retrieve_from_mbg_api.pl 
Can't locate Readonly.pm in @INC (you may need to install the Readonly module) (@INC contains: /etc/perl /usr/local/lib/x86_64-linux-gnu/perl/5.22.1 /usr/local/share/perl/5.22.1 /usr/lib/x86_64-linux-gnu/perl5/5.22 /usr/share/perl5 /usr/lib/x86_64-linux-gnu/perl/5.22 /usr/share/perl/5.22 /usr/local/lib/site_perl /usr/lib/x86_64-linux-gnu/perl-base .) at retrieve_from_mbg_api.pl line 11.
BEGIN failed--compilation aborted at retrieve_from_mbg_api.pl line 11.
```

### Install Readonly module

```
# Check available packages
apt search --names-only Readonly
Sorting... Done
Full Text Search... Done
libreadonly-perl/xenial,xenial 2.000-2 all
  facility for creating read-only scalars, arrays and hashes

libreadonly-xs-perl/xenial 1.05-1build2 amd64
  faster Readonly implementation

# Install (older, slower) Readyonly, because it's what's loaded in sript
sudo apt install libreadonly-perl
```

Success.

### Trait #2:

```
perl retrieve_from_mbg_api.pl 
Can't locate POE.pm in @INC (you may need to install the POE module) (@INC contains: /etc/perl /usr/local/lib/x86_64-linux-gnu/perl/5.22.1 /usr/local/share/perl/5.22.1 /usr/lib/x86_64-linux-gnu/perl5/5.22 /usr/share/perl5 /usr/lib/x86_64-linux-gnu/perl/5.22 /usr/share/perl/5.22 /usr/local/lib/site_perl /usr/lib/x86_64-linux-gnu/perl-base .) at retrieve_from_mbg_api.pl line 12.
BEGIN failed--compilation aborted at retrieve_from_mbg_api.pl line 12.```
```

### Install POE module
* Problem: a bazillion poe-packages available (e.g., try: `apt search --names-only POE`)
* Try installing most commonly mentioned: libmoosex-poe-perl   

```
sudo apt install libmoosex-poe-perl   
```

Success. Installed a bunch of dependencies. Let's try again.

### Trial #3:

```
perl retrieve_from_mbg_api.pl 
Can't locate JSON/XS.pm in @INC (you may need to install the JSON::XS module) (@INC contains: /etc/perl /usr/local/lib/x86_64-linux-gnu/perl/5.22.1 /usr/local/share/perl/5.22.1 /usr/lib/x86_64-linux-gnu/perl5/5.22 /usr/share/perl5 /usr/lib/x86_64-linux-gnu/perl/5.22 /usr/share/perl/5.22 /usr/local/lib/site_perl /usr/lib/x86_64-linux-gnu/perl-base .) at retrieve_from_mbg_api.pl line 17.
BEGIN failed--compilation aborted at retrieve_from_mbg_api.pl line 17.
```

### Install JSON/XS module

Check packages: 

```
apt search --names-only JSON/XS
Sorting... Done
Full Text Search... Done
boyle@vegbiendev:~/bien/tnrs/data/db/tropicos$ apt search --names-only json-xs
Sorting... Done
Full Text Search... Done
libcpanel-json-xs-perl/xenial 3.0210-1ubuntu1 amd64
  module for fast and correct serialising to JSON

libjson-xs-perl/xenial 3.010-2build1 amd64
  module for manipulating JSON-formatted data (C/XS-accelerated)
```

Install:

```
sudo apt install libjson-xs-perl
```
Success.

### Trial #4:

```
perl retrieve_from_mbg_api.pl 
Can't locate Text/CSV_XS.pm in @INC (you may need to install the Text::CSV_XS module) (@INC contains: /etc/perl /usr/local/lib/x86_64-linux-gnu/perl/5.22.1 /usr/local/share/perl/5.22.1 /usr/lib/x86_64-linux-gnu/perl5/5.22 /usr/share/perl5 /usr/lib/x86_64-linux-gnu/perl/5.22 /usr/share/perl/5.22 /usr/local/lib/site_perl /usr/lib/x86_64-linux-gnu/perl-base .) at retrieve_from_mbg_api.pl line 19.
BEGIN failed--compilation aborted at retrieve_from_mbg_api.pl line 19.
```

### Install libtext-csv-xs-perl

```
sudo apt install libtext-csv-xs-perl
```

Success

### Trial #5

```
perl retrieve_from_mbg_api.pl 
```
* No errors
* Appears to be running silently
* Stopped, then started again in screen, @ 2:38 pm, Sat May 30, 2020
* Script appears to write to STOUT only, so redirecting to file

```
screen
perl retrieve_from_mbg_api.pl > tropicos_names_20200530.txt
```


