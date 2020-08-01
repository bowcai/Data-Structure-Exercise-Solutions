## Exercise 08.10 - Binary Tree Depth

Compute the depth of a binary tree.  
Definition of the depth of a binary tree:
A path is the nodes from the root to one of the leaves
(including the root and the leaf).
The number of nodes in the longest path is the depth of the tree.

Input format:  
The first line is an integer *n*, representing the number of nodes in the tree.
The ID of nodes count from 1 to *n*. The root is 1 and n <= 10.  
The following *n* lines correspond to *n* nodes.  
Each line consists of two integers, representing the ID of left child and right child. If the node does not have the child, the integer will be -1.

Input sample:  
3  
2 3  
-1 -1  
-1 -1  

Output sample:  
2

给定一棵二叉树，求该二叉树的深度。  
二叉树深度定义：从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，
最长路径的节点个数为树的深度。

输入格式:  
第一行是一个整数n，表示二叉树的结点个数。二叉树结点编号从1到n，根结点为1，n <= 10  
接下来有n行，依次对应二叉树的n个节点。  
每行有两个整数，分别表示该节点的左儿子和右儿子的节点编号。
如果第一个（第二个）数为-1则表示没有左（右）儿子。

输入样例：  
3  
2 3  
-1 -1  
-1 -1  

输出样例：  
2
