//==============================
// Homework 6 - 4
//==============================
// Find all articulation points of a graph
//==============================
// belongs to CHinX2@20180105
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

int adj[MAX][MAX];  // adjacency matrix
int vis[MAX];       // visited node
int low[MAX];       // the highest ancestor that the node can visit with lower traversal time
int nCnt=0;         // number of nodes
int time=1;         // traversal time

/* find the small one */
int imin(int a,int b)
{
    return (a < b) ? a : b;
}

/* find articulation points by dfs */
void dfs_ap(int v,int p) //v is the point we need to check
{
    vis[v]=time;
    low[v]=time;
    time++;
    int i,child,ap; // child : num of child of this node
                    // ap : flag of articulation point
    child=ap=0;

    for(i=0;i<nCnt;i++)
    {
        if(adj[v][i]!=0&&i!=p)
        {
            if(vis[i]!=0)  // it is back edge
                low[v]=imin(low[v],vis[i]); // ancestor is the one who has lower time
            else    // it is tree edge
            {
                child++;
                dfs_ap(i,v); //search next node

                low[v]=imin(low[v],low[i]);
                if(low[i]>=vis[v])ap++; // it is articulation point
            }
        }
    }
    if((v==p&&child>1)||(v!=p&&ap>0))
        printf("node %d\n",v);
}

int main()
{
    int i,j,a;

    /* initialize matrix */
    memset(adj,0,sizeof(adj));
    memset(low,0,sizeof(low));
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

    printf("\nArticulation points :\n");
    dfs_ap(0,0); // set root = 0,check 0

    return 0;
}
