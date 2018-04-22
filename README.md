###大规模文本匹配
####项目介绍：
Linux下基于C开发的项目，目的是在corpus1.txt（49,159,731 字节）文件中匹配有多少company.txt（121,262,428 字节 共999998个公司名）文件中的公司名
####项目基本结构：

内存分配 : 在自己申请的内存中为节点分配空间
data文件夹下存储 corpus1.txt 和 company.txt 
testdata文件下存储 DEBUG下的测试数据
jiegoudingyi.h 为内存池和内存池节点的定义文件
hanshu.h 为函数的声明文件
hanshudingyi.c 为函数的定义文件
main.c 为主函数的包含文件 也是要编译的文件

内存池1：原始读入内存池，公司名按照读入顺序即数组中的存入下标 内部链表指针是按照有序存储的
内存池2：由内存池1转换而来，bfs顺序内存池，公司名下标对应字典树的bfs遍历顺序

内存池结构
当前分配到的节点个数 curindex
开辟空间的节点总数 size
数据节点数组 data

内存池中 节点结构 （必要节点）
储存节点值 val
是否是串的最后节点 flag
ac自动机的fail指针 faill
节点的孩子个数 childsum
节点的孩子节点的第一个节点 child

插入节点会插到本层的节点中最后一个小于次节点值的节点后面 保证链表的每层都是有序的

虚拟队列转换成bfs序结构
head 内存池2中当前要计算孩子节点个数的节点 
tail 内存池2中用于表示已经存储到内存池2中的最后一个节点

first head在内存池1中的头节点
last tail在内存池1中的头节点 还要额外进行nextnode的链接

1234
1245
2345
2346
3456
				&nbsp&nbsp&nbsp&nbsp	  root
	&nbsp&nbsp&nbsp&nbsp		  /       
	&nbsp&nbsp&nbsp&nbsp		1    -   2   -   3
	&nbsp&nbsp&nbsp&nbsp		|  &nbsp&nbsp&nbsp&nbsp| &nbsp&nbsp&nbsp&nbsp|
	&nbsp&nbsp&nbsp&nbsp		2 &nbsp&nbsp3&nbsp&nbsp &nbsp4
	 &nbsp&nbsp&nbsp&nbsp	/    &nbsp&nbsp&nbsp&nbsp| &nbsp&nbsp &nbsp|
	&nbsp&nbsp 3   -  4 4&nbsp&nbsp &nbsp5
	&nbsp&nbsp |   &nbsp&nbsp&nbsp |&nbsp&nbsp | &nbsp&nbsp &nbsp\
	&nbsp&nbsp4  &nbsp&nbsp   5&nbsp&nbsp 5 - 6&nbsp6
	
在内存池2中的顺序为
123234344545566

####使用方法：
文件从data文件夹下面的corpus1.txt 和 company.txt 读入
编译运行main.c 输出
sum为匹配到的公司名个数;
node为公司名字个数;
 memcurindex为节点个数;
  MEMPOOL 为内存池的大小;
   use是实际使用空间大小.

如果定义DEBUG则文件从testdata下面的文件1读入
需要自己输入串进行匹配
输出信息包括mem1 和 mem2 的节点信息 
依次是 下标 对应的权值 flag id（预留位置无意义）fail指针 nextnode（mem2中的无意义） 孩子节点的下标 孩子节点的个数（mem1中的无意义）
