/*************************************************************************
	> File Name: hanshu.h
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年03月10日 星期六 11时20分26秒
 ************************************************************************/

#ifndef _HANSHU_H
#define _HANSHU_H

void initTreeNode(TreeNode *, unsigned char);
// 节点的初始化 
MEMPOOL* initMEMPOOL(int);
// 内存池的初始化
int getTreeNodefromMEM(MEMPOOL *,unsigned char);
// 从内存池中分配节点
int externmem(MEMPOOL *);
// 内存池不够了 每次扩容100 M
void inserttoTrie(int , MEMPOOL *, const unsigned char *);
// 每次插入一个字串串 unsigned char 的
void changeintocon(int , MEMPOOL *, MEMPOOL *);
// 使用开辟新空间的形式转换 -
int find(MEMPOOL *, int , int );
// 二分判断孩子节点
int build_actree_inMEMPOOL(MEMPOOL *, int );
// 建立ac自动机
int seach_inMEMPOOL(MEMPOOL *, int , const unsigned char *);
// 在ac自动机中查找 返回个数 一个公司名出现多次算多次
void clearMEMPOOL(MEMPOOL *);
// 空间回收


/*
 * 老版本的函数
DATrie *initDATrie(int);
// 初始化双数组字典树

TreeNode *NodeisLink(TreeNode*, unsigned char);
void inserttoTrie(TreeNode *,MEMPOOL *);
void changeintodat(TreeNode *, DATrie *);
void output(TreeNode *);
*/

#endif
