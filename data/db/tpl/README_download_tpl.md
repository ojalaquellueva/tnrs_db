# TPL download from MBG

## FTP info
* FTP site: `ftp.cissus.org`
* Port: 21
* User name: garfile
* Password: garden2003
* File: `tpl.zip`
* In folder: psmock
* **Didn't work!**

## wget + dropbox

* Download date: 2020-06-25

### Get dropbox link

1. Go to Dropbox --> Dropbox Transfer files
2. Beside file, click Share
3. In Share popup, click "Copy link"
4. Paste link into text editor, change dl=0 to dl=1

### In terminal

1. Navigate to download folder
2. wget command:

**Syntax:**

```
wget <modified_dropbox_link>
```

**Actual command:**

```
wget https://www.dropbox.com/s/1mowiwfddk5pofm/tpl.zip?dl=1
```