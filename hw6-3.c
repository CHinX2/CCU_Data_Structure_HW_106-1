//==============================
// Homework 6 - 3
//==============================
// Depth first search
//==============================
// belongs to CHinX2@20180105
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

int adj[MAX][MAX];  // adjacency matrix
int ans[MAX][MAX];  // dfs spanning tree as adjacency matrix
int vis[MAX];       // visited node
int nCnt=0;         // number of nodes

void dfs(int v)
{
    vis[v]=1;
    int i;
    for(i=0;i<nCnt;i++)
    {
        if(vis[i]==1)continue; // the node has visited, check next node
        if(adj[v][i]!=0)
        {
            // union two node ( non-directed )
            ans[v][i]=1;
            ans[i][v]=1;
            dfs(i); //search next node
        }
    }
}

int main()
{
    int i,j,a;

    /* initialize matrix */
    memset(adj,0,sizeof(adj));
    memset(ans,0,sizeof(ans));
    memset(vis,0,sizeof(vis));

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

    dfs(0); // root = 0

    /* print the dfs spanning tree as adjacency matrix */
    printf("\n=== DFS spanning tree ( non-directed ) ===\n\n");
    for(i=0;i<nCnt;i++)
    {
        for(j=0;j<nCnt;j++)
        {
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}

