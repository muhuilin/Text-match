/*************************************************************************
	> File Name: jiegoudingyi.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年03月10日 星期六 11时09分12秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode {
    unsigned char val;
    int flag;
    int id; //预留变量
    int fail;//新加的
    int father; ///预留变量还没有写初始化 以后不用的话直接删除
    int childsum; ///孩子的个数
    int nextnode, child;
}TreeNode;

typedef struct MEMPOOL {
    int curindex;
    int size;
    TreeNode *data;
}MEMPOOL;

typedef struct DATrie {
    int *base;
    int *check;
    int *fail;
    int size;
}DATrie;
