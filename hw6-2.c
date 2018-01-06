//==============================
// Homework 6 - 2
//==============================
// Transitive closure matrix A+
// Reflexive transitive closure matrix A*
//==============================
// belongs to CHinX2@20180105
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

int tcm[MAX][MAX];  // transitive closure matrix
int nCnt=0;         // number of nodes

/* find the node's path */
void find(int a,int b)
{
    int i;
    for(i=0;i<nCnt;i++)
    {
        if(tcm[b][i]!=0)
        {
            tcm[a][i]++;
            if(tcm[a][i]==1)find(b,i); //if this node hasn't visited, check it's path
        }
    }
}

/* build the transitive closure matrix */
void transi()
{
    int i,j;
    for(i=0;i<nCnt;i++)
    {
        for(j=0;j<nCnt;j++)
        {
            if(tcm[i][j]!=0)
            {
                find(i,j); // find the node which node i can meet through node j
            }
        }
    }
}

int main()
{
    int i,j,a;
    memset(tcm,0,sizeof(tcm)); // initialize the tcm matrix

    /* read in the adjacency matrix */
    printf("Please enter the number of nodes ( < 999 ) : ");
    scanf("%d",&nCnt); //get the num of node
    printf("Please enter the adjacency matrix of graph :\n");
    for(i=0;i<nCnt;i++)
    {
        for(j=0;j<nCnt;j++)
        {
            scanf("%d",&a);
            if(a!=0)
            {
                tcm[i][j]=1;
            }
        }
    }

    transi();

    /* print the transitive closure matrix */
    /* path > 0 */
    printf("=== transitive closure matrix ===\n");
    for(i=0;i<nCnt;i++)
    {
        for(j=0;j<nCnt;j++)
        {
            if(tcm[i][j]!=0)printf("1 ");
            else printf("0 ");
        }
        printf("\n");
    }
    /* print the reflexive transitive closure matrix */
    /* path >= 0 */
    printf("=== reflexive transitive closure matrix ===\n");
    for(i=0;i<nCnt;i++)
    {
        for(j=0;j<nCnt;j++)
        {
            if(i==j)printf("1 "); // path 0
            else if(tcm[i][j]!=0)printf("1 ");
            else printf("0 ");
        }
        printf("\n");
    }
    return 0;
}
