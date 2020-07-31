## Exercise 04.07 - String Cyclic Shift

Design an linear algorithm to determine whether string *T* is the cyclic shift 
of another string *T'*. 
For example, "arc" and "car" are cyclic shift strings of each other.

设计一个线性算法来判断串*T*是否是另一个串*T'*的循环反转，例如arc和car便互为循环反转。

### Solution

Concatenate string *T* to its own tail.
Check if *T'* is the substring of the new string with KMP algorithm.
If the answer is yes, then the two strings are cyclic shift strings.

将字符串T接在自己后面延长一倍，利用KMP算法判断T'是否为新字符串的子串。
若是子串，则说明两者互为循环移位。
