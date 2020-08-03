## Exercise 10.10 - Shortest Road

After the 2008 earthquake, a county wants to build a one-way
telecom line from the headquarters to all villages.
However, the one-way telecom line can only be built
between given two villages.  
Try to find the shortest path to connect the headquarters
to all the villages.

Input format:  
The input includes several test sets.  
For each set:  
1. The first line includes two integers N(1<=N<=100), M(M<=10000),
N stands for the number of villages, 
and M stands for the number of path between villages.
2. The following N lines are two integers xi, yi, 
stands for the coordinates of villages (xi, yi).
3. The next following M lines stands are two integers 
c1(1<=c1<=N), c2(1<=c2<=N),
means that a one-way telecom line can be built 
from village c1 to village c2.   

Note that:  
The length of telecom line between villages is 
their Euclid distance.  
The headquarters are placed in the village No.1.  
The input ends with EOF.

Output format:  
For each test set, print a whole line for the length
of the shortest path.
The result is accurate to two decimal places.  
If it is impossible to build a one-way telecom line, 
print "NO".

Input sample:  
4 6  
3 6  
4 6  
3 4  
7 20  
1 2  
1 3  
2 3  
3 4  
3 1  
3 2  
4 3  
0 0  
1 0  
1 1  
1 2  
1 3  
4 1  
2 3  

Output sample：  
19.49  
NO


2008年地震之后，坚强县受灾严重，该县通信线路也收到了致命的打击，
县总部为了能够及时的向各村的发送消息，命令小强去解决一下这个问题。  
小强经过调查发现，为了能够快速的实现通信，
当务之急是能够建立起一条从总部可以向各个村单向发送信息的通信系统。
由于灾后情况紧急，不是每一个村之间都能够快速的建立起通信线路，
只有有限的村比如村A和村B间可以建立单向的从A向B发送信息的通信线路，
小强现在的问题就是要找出一个合适的方案，使从总部发送出的信息能够通到各村，
而用的总的通信线路是最短的（毕竟情况危急，物质短缺）。

输入格式:  
输入包括多组的测试数据。  
对于每一组测试数据:  
1、第一行包括两个整数N(1<=N<=100), M(M<=10000), N表示通信网络中村子的数量，
M表示在这些村子中，可以有M条通信线路建起来。  
2、接下来N行，每行两个整数xi, yi，代表着这个村子的X轴，Y轴的坐标(xi,yi)  
3、接下来M行，每行两个整数c1(1<=c1<=N), c2(1<=c2<=N)，
代表着从村c1到村c2可以建一个单向线路。  
注：两村之间的直线段距离（通信线路长度），即为两点间的欧式距离。  
县总部所在的村假设都在编号为1的村。  
输入以文件终止为结束。  

输出格式：  
对于每一组的测试数据，输出完全的一行，值为最短的总长度，结果保留两位小数。  
如果不能建立一个单向的临时网络，输出"NO"。

输入样例：  
4 6  
3 6  
4 6  
3 4  
7 20  
1 2  
1 3  
2 3  
3 4  
3 1  
3 2  
4 3  
0 0  
1 0  
1 1  
1 2  
1 3  
4 1  
2 3  

输出样例：  
19.49  
NO
