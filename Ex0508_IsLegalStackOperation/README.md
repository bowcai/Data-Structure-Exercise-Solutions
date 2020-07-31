## Exercise 05.08 - Is Legal Stack Operation

"S" represents for push of stack and "X" represents for pop.
A sequence of "S" and "X" operates with an empty stack.
If all the operations are executable and the final status of the stack
is empty, then the sequence of operations is legal.  
Write a program to check if one sequence of "S" and "X" is legal.

Format of input:  
Given two integers *N* and *M* in the first line. 
*N* is the number of sequences to be checked, 
*M* (≤50) is the capacity of stack.
The followed *N* lines are the sequences with "S" and "X",
which are not empty and shorter than 100 characters.  
Format of output:  
For each sequence, output "YES" for legal operation and 
output "NO" for illegal operation.

Input sample:  
4 10  
SSSXXSXXSX  
SSSXXSXXS  
SSSSSSSSSSXSSXXXXXXXXXXX  
SSSXXSXXX  
Output sample：  
YES  
NO  
NO  
NO  

假设以S和X分别表示入栈和出栈操作。如果根据一个仅由S和X构成的序列，
对一个空堆栈进行操作，相应操作均可行（如没有出现删除时栈空）且最后状态也是栈空，
则称该序列是合法的堆栈操作序列。请编写程序，输入S和X序列，判断该序列是否合法。

输入格式:  
输入第一行给出两个正整数N 和M，其中N 是待测序列的个数，M（≤50）是堆栈的最大
容量。随后N 行，每行中给出一个仅由S 和X 构成的序列。序列保证不为空，且长度不超
过100。  
输出格式:  
对每个序列，在一行中输出YES 如果该序列是合法的堆栈操作序列，或NO 如果不是。

输入样例：  
4 10  
SSSXXSXXSX  
SSSXXSXXS  
SSSSSSSSSSXSSXXXXXXXXXXX  
SSSXXSXXX  
输出样例：  
YES  
NO  
NO  
NO  
