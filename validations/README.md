# Performs automated validations & integrity checks on completed TNRS database

Author: Brad Boyle (bboyle@email.arizona.edu)  

### I. Preparation

Review all parameters in params.sh and adjust as needed.

### II. Usage

Validate completed development private database

```
./validate.sh [-<option1> -<option2> ...]
```


* Options:
| Option | Purpose |
| ------ | ------- |
| s      | Silent mode |
| m      | Send start/stop/error ermails |
| a      | Append to existing logfile [replaces file if omitted (default) |
