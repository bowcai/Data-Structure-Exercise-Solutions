## Exercise 03.07 - Maze

Solve the maze problem for one pathway.  
Use array MAZE(1..m, 1..n) to represent the maze,
in which 1 represents passable path and 0 represents impassable path.
MAZE(1, 1) represents the entrance, and MAZE(m, n) represents exit.  
Design an algorithm to determine if the maze have a solution,
and print the pathway.

用计算机模拟“迷宫问题”，求出其中的一条通路。用数组 MAZE(1..m, 1..n) 表示迷宫，
数组元素为1意味死路，为0表示通路，MAZE(1, 1) 为迷宫入口，MAZE(m, n) 为迷宫出口，
试着设计一个算法判别迷宫问题是否有解，并打印路径。

### Solution

Use backtracking algorithm to solve the problem.
If the path reaches a dead end, then move a step behind and find another path.

使用回溯法解决迷宫问题。如果此路径已无路可走，则回退一格，寻找其他路径。
