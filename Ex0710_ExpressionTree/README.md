## Exercise 07.10 - Expression Tree

Any expression can be converted into an expression tree.
For example, expression "a+b*c" can be converted into 
the following expression tree:  
&nbsp;&nbsp;\+  
&nbsp;/&nbsp;\\  
a&nbsp;&nbsp;&nbsp;\*  
&nbsp;&nbsp;&nbsp;/&nbsp;\\  
&nbsp;&nbsp;&nbsp;b c  
Now, given a infix expression, with only variable names
(do not contain numbers).
Convert the expression into an expression tree.

Input format:  
The input includes three parts.  
The first part consists of one line. It is a infix expression, which is shorter than 50 characters.
The expression contains lower characters (a-z) as variables, and operators (+, -, *, /, brackets).
It do not contains numbers and blank spaces.  
The second part consists of one integer *n* (n<10).
It stands for the number of variables in the infix expression.  
The third part consists of *n* lines. The format of each line is *C x*. 
*C* represents the name of variable, and *x* represents the value.

Input Sample:  
a\+b\*c  
3  
a 2  
b 7  
c 5  

Output Sample:  
abc\*\+  
&nbsp;&nbsp;&nbsp;\+  
&nbsp;&nbsp;/&nbsp;\\  
&nbsp;a&nbsp;&nbsp;&nbsp;\*  
&nbsp;&nbsp;&nbsp;&nbsp;/&nbsp;\\  
&nbsp;&nbsp;&nbsp;&nbsp;b&nbsp;c  
37  

众所周知，任何一个表达式，都可以用一棵表达式树来表示。例如，表达式a\+b\*c，可以表示为如下的
表达式树：  
&nbsp;&nbsp;\+  
&nbsp;/ \\  
a&nbsp;&nbsp;&nbsp;\*  
&nbsp;&nbsp;&nbsp;/ \\  
&nbsp;&nbsp;&nbsp;b c  
现在，给你一个中缀表达式，这个中缀表达式用变量来表示（不含数字），请你将这个中缀表达式用表达
式二叉树的形式输出出来。

输入格式：  
输入分为三个部分。  
第一部分为一行，即中缀表达式（长度不大于50）。中缀表达式可能含有小写字母代表变量（a-z），也可
能含有运算符（\+、\-、\*、/、小括号），不含有数字，也不含有空格。  
第二部分为一个整数n(n < 10)，表示中缀表达式的变量数。  
第三部分有n行，每行格式为C x，C为变量的字符，x为该变量的值。

输入示例：  
a\+b\*c  
3  
a 2  
b 7  
c 5  

输出示例：  
abc\*\+  
&nbsp;&nbsp;&nbsp;\+  
&nbsp;&nbsp;/&nbsp;\\  
&nbsp;a&nbsp;&nbsp;&nbsp;\*  
&nbsp;&nbsp;&nbsp;&nbsp;/&nbsp;\\  
&nbsp;&nbsp;&nbsp;&nbsp;b&nbsp;c  
37  
