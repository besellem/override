# level03

### First solution

As we can see, there's a `switch` in the code with 2 possible cases :
- it's one of those numbers (`1, 2, 3, 4, 5, 6, 7, 8, 9, 16, 17, 18, 19, 20 or 21`).
In that case, it uses the difference between `0x1337d00d` (`322424845` in decimal) and the number from the user.
- It uses `rand()` to generate a random number.

So, we have to obviously use one `322424845 - x`, `x` being one of the numbers from the list above.  

By testing, we can see that `x` is `18`. So the password is `322424827`

### Second solution

A second solution is to use [this website](https://www.dcode.fr/chiffre-xor) with the `buffer`.  
The output will be :

```
(hexadecimal number, clear text)
0x10	Amlepcvwncvkmlq#
0x11	@lmdqbwvobwjlmp"
0x12	Congratulations!
[...]
```
*`0x12` is `18` in decimal*


**Either way, the solution is the same, we find that the password is `322424845 - 18 = 322424827`**

```sh
$> ./level03
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
