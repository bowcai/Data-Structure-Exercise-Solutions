## Exercise 06.07 - Magic Square

Magic Square is a *m*\**m* matrix filled with integers from 1 to *m*\**m*.
The sum of integers in each row, column and diagonal is equal.
Print a magic square with given *m*, for example *m*=15.

魔方阵是一个古老的智力问题，它要求在一个*m*\**m*的矩阵中填入1-*m*\**m*的数字(*m*为奇数)，
使得每一行，每一列，每一条对角线的累加和都相等。请写程序实现魔方阵并输出。例如*m*=15。

### Solution

According to [Wikipedia](https://en.wikipedia.org/wiki/Magic_square), 
there is a method to construct a magic square of odd order 
called [Siamese Method](https://en.wikipedia.org/wiki/Siamese_method).
The program is an implementation of this method.

根据[维基百科](https://zh.wikipedia.org/wiki/%E5%B9%BB%E6%96%B9)，有一种奇数阶幻方的构造方法，
称为[Siamese方法](https://en.wikipedia.org/wiki/Siamese_method)。本程序依据此方法编写。

