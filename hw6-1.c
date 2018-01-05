//==============================
// Homework 6 - 1
//==============================
// minimum cost spanning tree
// using Sollin's algorithm
//==============================
// belongs to CHinX2@20180105
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int dis[MAX];		// save distance
int index[MAX];		// save index
int vis[MAX];
int eCnt = 0;		// edge count
int nCnt = 0;       // node count
int adj[MAX][MAX];
int ans[MAX][MAX];

void addvis(int a,int b)
{
    int i;
    if(vis[a]!=0)
    {
        if(vis[b]==0)
        {
            vis[a]++;
            vis[b]=vis[a];

            for(i=0;i<nCnt;i++)
                if(ans[a][i]!=0&&i!=b)vis[i]++;
        }
        else{
            vis[a]+=vis[b];
            vis[a]++;
            vis[b]=vis[a];

            for(i=0;i<nCnt;i++)
                if(ans[a][i]!=0&&i!=b)vis[i]=vis[a];
            for(i=0;i<nCnt;i++)
                if(ans[b][i]!=0&&i!=a)vis[i]=vis[b];
        }
    }
    else if(vis[b]!=0)
    {
        vis[b]++;
        vis[a]=vis[b];

        for(i=0;i<nCnt;i++)
            if(ans[b][i]!=0&&i!=a)vis[i]++;
    }
    else{
        vis[a]++;
        vis[b]++;
    }
    return;
}

void sollin()
{
    int a,b;
    int min = 1e9;
    int i,j;

    for(i=0;i<nCnt;i++)
    {
        min = 1e9;
        for(j=i;j<nCnt;j++)
        {
            if(adj[i][j]!=0&&adj[i][j]<min&&ans[i][j]==0)
            {
                min=adj[i][j];
                a=i;
                b=j;
            }
        }
        ans[a][b]=ans[b][a]=min;
        addvis(a,b);
    }
    for(i=0;i<nCnt;i++)
    {
        min = 1e9;
        for(j=i;j<nCnt;j++)
        {
            if(adj[i][j]!=0&&adj[i][j]<min&&ans[i][j]==0)
            {
                min=adj[i][j];
                a=i;
                b=j;
            }
            else if(ans[i][j]!=0)
            {

            }
        }
        ans[a][b]=ans[b][a]=min;
        addvis(a,b);
    }
}

int main()
{
	int a, b, value;
    memset(adj,0,sizeof(adj));
    memset(ans,0,sizeof(ans));
    memset(vis,0,sizeof(vis));

	printf("Please enter the number of nodes (limit : 99) : \n", nCnt - 1);
	scanf("%d", &nCnt);
	while (1)
	{
		printf("Please enter 2 connected nodes' index(0 ~ %d) and the distance\n",nCnt-1);
		printf("Sample format : a b distance");
		printf("if you want to stop, please enter -1 -1 -1\n");
		scanf("%d%d%d", &a, &b, &value);
		if (a == -1)
			break;
        adj[a][b]=value;
        eCnt++;
	}
	sollin();

	int i, j;
	for (i = 0; i < nCnt; i++)
	{
		for (j = 0; j < nCnt; j++)
		{
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
