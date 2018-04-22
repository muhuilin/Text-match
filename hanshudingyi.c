/*************************************************************************
	> File Name: hanshudingyi.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年03月10日 星期六 11时22分24秒
 ************************************************************************/

#include "jiegoudingyi.h"
#include "hanshu.h"
#define MEMBLOCK (1024 * 1024 * 100)
void initTreeNode(TreeNode *tree, unsigned char val) { //初始化一个节点
    tree->val = val;
    tree->flag = 0;
    tree->id = 0;
    tree->fail = 0;
    tree->nextnode = tree->child = 0;
    return ;
}

MEMPOOL* initMEMPOOL(int num) { // 初始化内存池
    MEMPOOL* memery = (MEMPOOL *)malloc(sizeof(MEMPOOL) * 1);
    memery->curindex = 0;
    memery->size = MEMBLOCK * num;
    memery->data = (TreeNode *)malloc(memery->size);
    memery->data[0].val = -1;
    return memery;
}

void clearMEMPOOL(MEMPOOL *mem) {
    free(mem->data);
    free(mem);
}

int externmem(MEMPOOL *mem) {
    TreeNode *temp_data = (TreeNode *)realloc(mem->data, mem->size + MEMBLOCK);
    if(temp_data == NULL) {
        printf("内存申请失败\n");
        return 0;
    }
    mem->data = temp_data;
    mem->size += MEMBLOCK;
    return 1;
}

int getTreeNodefromMEM(MEMPOOL *mem, unsigned char val){ //返回的已经是下标了
    mem->curindex += 1;
    if(mem->curindex >= mem->size) {
        externmem(mem);
    }
    initTreeNode(mem->data + mem->curindex, val);
    return mem->curindex;
}
/*
DATrie *initDATrie(int num) {// 初始化一棵双数组字典树，单位是 M
    DATrie *tree = (DATrie *)malloc(sizeof(DATrie) * 1);
    tree->base = (int *)malloc(MEMBLOCK * num);
    tree->check = (int *)malloc(MEMBLOCK * num);
    tree->fail = (int *)malloc(MEMBLOCK * num);
    tree->size = num * MEMBLOCK;
    return tree;
}
*/
/*
TreeNode *NodeisLink(TreeNode *tree, unsigned char val) {//查找子节点中是否有目标节点 有返回指针没有返回空
    TreeNode *p = tree;
    while(p) {
        if(p->val == val) return p;
        p = p->nextnode;
    }
    return NULL;
}
*/
void inserttoTrie(int tree, MEMPOOL *mem, const unsigned char *str) {
    int tmp = tree;
    int newnode, p;
    while(*str) {
       // printf("%c %p 程序正常运行\n", *str, p);
       // fflush(stdout);
        p = mem->data[tmp].child;
        //插入的节点影响了上一层  /// 插入的节点影响本层
        if(p == 0 || *str < mem->data[p].val) { 
            newnode = getTreeNodefromMEM(mem, *str);
            mem->data[newnode].nextnode = p;
            mem->data[tmp].child = newnode;
            p = newnode;
        } 
        else if(*str == mem->data[p].val) {
            p = p;   ///已经找到了 不做处理
        }
        else {
        //最后在处理 p 11 48 最新
            while(mem->data[p].nextnode && *str > mem->data[mem->data[p].nextnode].val) {
                p = mem->data[p].nextnode;
            }
            if(mem->data[mem->data[p].nextnode].val == *str) {
                p = mem->data[p].nextnode;
            }
            else {
                newnode = getTreeNodefromMEM(mem, *str);
                mem->data[newnode].nextnode = mem->data[p].nextnode;
                mem->data[p].nextnode = newnode;
                p = newnode;
            }
        }
        tmp = p;
        str++;
    }
    mem->data[p].flag = 1;
    return ;
}

void changeintocon(int tree, MEMPOOL *mem1, MEMPOOL *mem2) {
    int tree1 = tree, tree2 = tree;
    int head = tree1, tail = tree1 + 1; // head指向 mem2 和 mem1 的头节点 
                            // 注 head 同时指向mem1 和 mem2 是错的 原因是 mem1走的顺序是不对的 ***
    //改  为mem1设置自己的头节点 first
    
    // 可改项 -》 mem2 的child nextnode 已经没有意义了 可以用来记录节点个数
    int first = head;
                                    // tail指向 mem2 的尾节点
                                    //通过last 对mem1进行遍历
    int last = tree1; // 当前节点指针
    int sum = 0;
    int temp;
    //last = mem1->data[tail].child;
    mem2->data[head] = mem1->data[head];
    //printf("head = %d %d\n", head, mem2->data[head].val);
    while(head < tail) {
        mem2->data[head].child = tail;
        mem1->data[last].nextnode = mem1->data[first].child;
        sum = 0; // 记录孩子个数
        while(mem1->data[last].nextnode) {
            sum++;
            mem2->data[tail++] = mem1->data[mem1->data[last].nextnode]; ///空间进行
            // mem1->data[last].nextnode = last;
            last = mem1->data[last].nextnode;
        }
        mem2->data[head].childsum = sum;
        head++;
        first = mem1->data[first].nextnode;
        /*last = mem1->data[head].child;
        mem2->data[head].child = tail;
        mem2->data[tail].nextnode = last;
        sum = 0;
        while(mem2->data[tail].nextnode) { // 孩子节点没有找完
            sum++;
            mem2->data[tail++].nextnode =  
        }*/
    }
    mem2->curindex = mem1->curindex;
}

int find(MEMPOOL *mem, int p, int x) {
    //判断 p 的孩子节点里面是否有 x

    int l = mem->data[p].child, 
    r = mem->data[p].child + mem->data[p].childsum - 1;
    while(l <= r) {
        int mid = (l + r) / 2;
        if(mem->data[mid].val == x) {
            return mid;
        }
        if(mem->data[mid].val < x) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return 0;
}

int build_actree_inMEMPOOL(MEMPOOL *mem, int tree) {
    /// 已经在一个 顺序访问就是 bfs的顺序了
    //QAQ 
    #define NIL 0
    for(int i = 1; i < mem->curindex; i++) {
        for(int j = 0; j < mem->data[i].childsum; j++) {
            int childind = mem->data[i].child + j;
            int p = mem->data[i].fail;
            int x;
            while(p != NIL && (x = find(mem, p, mem->data[childind].val)) == NIL) {
                p = mem->data[p].fail;
            }
            if(p == NIL) p = tree;
            else p = x;
            mem->data[childind].fail = p;
        }
    }
    return 1;

    #undef NIL
}

int seach_inMEMPOOL(MEMPOOL *mem, int tree, const  unsigned char *str) {

    #define NIL 0
    int ret = 0;
    int p = tree, q;
    int x;
    while(str[0]) {
        while(p != NIL && (x = find(mem, p, str[0])) == NIL ) {
            p = mem->data[p].fail;
        }
        if(p) p = x;
        else p = tree;
        q = p;
        while(q) {
            //printf("%d %d\n", mem->data[q].flag, 
            //mem->data[q].val);
            ret += mem->data[q].flag;
            //if(mem->data[q].flag == 1) 
               // mem->data[q].flag = 0;
            q = mem->data[q].fail;
        }

        str++;
    }
    return ret;

    #undef NIL
}


/*
void changeintodat(TreeNode *linktree, DATrie *dattree) { //将字典树转化成双数组字典树
    TreeNode *head = linktree, *tail = linktree;
    TreeNode *p;
    head->id = 1;
    while(head) {
        p = head->child;
        int i;
        for(i = 2; ; i++) {
            //printf("%d 程序正常运行\n", i);
            int flag = 0;
            while(p) {
                if(dattree->check[i + p->val] != 0) {
                    flag = 1; 
                    break;
                }
                p = p->nextnode;
            }
            if(flag == 0) break;
        } 
        //printf("line in 88程序正常运行\n");
        dattree->base[head->id] = i;
        p = head->child;
        while(p) {
            tail->nextnode = p;
            tail = p;
           // printf("地址为%p 内容是%c id = %d\n", p, p->val, i + p->val);
            p->id = i + p->val;
            dattree->check[p->id] = head->id;
            if(p->flag == 1) dattree->check[p->id] *= -1;
            p = p->nextnode;
        }
        //printf("line in 98 程序正常运行\n");
        head = head->nextnode;
    }
}

void output(TreeNode *tree) {
    TreeNode *p = tree->child;
    while(p) {
       // printf("%c\n", p->val);
        p = p->nextnode;
    }
    return ;
}
void output1(TreeNode *tree, int c) {
    TreeNode *p = tree;
    while(p) {
        printf("%d = %c\n",c, p->val);
        output1(p->child, c + 1);
        p = p->nextnode;
    }
    return ;
}

*/
