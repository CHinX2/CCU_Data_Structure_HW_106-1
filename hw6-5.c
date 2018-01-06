//==============================
// Homework 6 - 5
//==============================
// to calculate and output the e(i) and l(i)
// for all activities i in an AOE network
//==============================
// belongs to CHinX2@20180105
//==============================
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

int adj[MAX][MAX];  // adjacency matrix
int nCnt=0;         // number of nodes

int main()
{
    int i,j,a;

    /* initialize matrix */
    memset(adj,1e9,sizeof(adj));

    /* read in the adjacency cost matrix */
    printf("Please enter the number of nodes ( < 999 ) : ");
    scanf("%d",&nCnt); //get the num of node
    printf("Please enter the adjacency matrix of graph :\n");
    for(i=0;i<nCnt;i++)
    {
        for(j=0;j<nCnt;j++)
        {
            scanf("%d",&adj[i][j]);
            if(a!=0)
            {
                adj[i][j]=a;
            }
        }
    }

    return 0;
}
