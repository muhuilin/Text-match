/*************************************************************************
	> File Name: main.c
	> Author:  muhuilin 
	> Mail: 
	> Created Time: 2018年03月10日 星期六 18时28分54秒
 ************************************************************************/

#include "hanshudingyi.c"
#include <stdlib.h>
#include <time.h>
//#define DEBUG
void print(MEMPOOL *mem) {
    for(int i = 1; i <= mem->curindex; i++) {
        printf("%d: %d %d %d %d %d %d %d\n"
              ,i
              ,mem->data[i].val
              ,mem->data[i].flag
              ,mem->data[i].id
              ,mem->data[i].fail
              ,mem->data[i].nextnode
              ,mem->data[i].child
              ,mem->data[i].childsum
            );
    }
}
int main() {
    clock_t start, finish;
    start = clock();
    MEMPOOL *mem = initMEMPOOL(8);
    printf("MEMINIT OK\n");
    int linktree = getTreeNodefromMEM(mem, 0);
    unsigned char *str = (unsigned char *)malloc(sizeof(unsigned char) * 1024 * 1024 * 4);
    //FILE *fin = fopen("/home/muhuilin/PROJECT/3信息检索/data/company.txt","r");
    //FILE *fin_match = fopen("/home/muhuilin/PROJECT/3信息检索/data/corpus1.txt","r");
    FILE *fin = fopen("./data/company.txt","r");
    FILE *fin_match = fopen("./data/corpus1.txt","r");
    char *temp = (char *)malloc(sizeof(char ) * 1024 * 1024);
    //printf("STR OK\n");
    int node = 0;
    #ifdef DEBUG
    FILE *test1 = fopen("./testdata/1", "r");
    while(fscanf(test1, "%s", str) != EOF) {
        inserttoTrie(linktree, mem, str);
        printf("%s\n", str);
    }
    print(mem);
    //printf("****************\n");
    MEMPOOL *mem2 = initMEMPOOL(8);
    changeintocon(linktree, mem, mem2);
    //print(mem2);
    printf("转换完成\n");
    clearMEMPOOL(mem);
    build_actree_inMEMPOOL(mem2, linktree);
    print(mem2);
    printf("AC自动机建立完成\n");
    int sum = 0;
    fclose(test1);
    while(scanf("%s", str) != EOF) {
        sum = seach_inMEMPOOL(mem2, linktree, str);
        printf("sum = %d\n", sum);
    }
    
    
    
    
    #else
    while(fscanf(fin, "%[^\t\n]\t", str) != EOF) {
        if(str[0] >= '0' && str[0] <= '9') continue;
        node ++;
        //printf("%s\n", str);
        inserttoTrie(linktree, mem, str);
    }
    printf("插入成功\n");
    //print(mem);
    printf("******************************\n");
    MEMPOOL *mem2 = initMEMPOOL(8);
    changeintocon(linktree, mem, mem2);
    //print(mem2);
    printf("转换完成\n");
    clearMEMPOOL(mem); /// 删除mem1的空间改进方向是原地交换 暂时还不想写QAQ
    /// 改进 可以在边 调整顺序边 建AC自动机吗
    //证明 ？？？ 脑抽了
    build_actree_inMEMPOOL(mem2, linktree);
    printf("AC自动机建立完成\n");
    int sum = 0;
    fclose(fin);
    while(fscanf(fin_match, "%s" ,str) != EOF) {
        sum += seach_inMEMPOOL(mem2, linktree, str);
    }
    printf("memcurindex = %d MEMPOOL = %d use = %dM\n", mem2->curindex, mem2->size / 1024 /1024, (int)sizeof(TreeNode) * mem2->curindex / 1024 / 1024);
    printf("sum == %d node = %d\n", sum, node);
    fclose(fin_match);
    /*MEMPOOL *mem2 = initMEMPOOL(mem->size / MEMBLOCK);
    int actree = getTreeNodefromMEM(mem2, 0);
    DATrie *dattree = initDATrie(300);
    printf("双数组字典树空间申请完成\n");
    //changeintodat(linktree, dattree);
    printf("双数组构建完成\n");*/
    #endif
    finish = clock();
    printf("耗时：%lf\n", (double)(finish - start) / CLOCKS_PER_SEC);
}
