//==============================
// Homework 6 - 4
//==============================
// Find all articulation points of a graph
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
    memset(adj,0,sizeof(adj));

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
                adj[i][j]=1;
            }
        }
    }

    return 0;
}
