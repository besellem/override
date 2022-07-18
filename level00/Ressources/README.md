# level00

```sh
$> ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:abcd
Invalid Password!
```

With gdb, we can see that there's a hardcoded comparison between the password retrieved by `scanf()` and the value `0x149c` (`5276` in decimal)

```sh
$> gdb -q ./level00
(gdb) disas main
Dump of assembler code for function main:
[...]
   0x080484e7 <+83>:	cmp    $0x149c,%eax
[...]
```

We juste have to retry with this value :

```sh
./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```
