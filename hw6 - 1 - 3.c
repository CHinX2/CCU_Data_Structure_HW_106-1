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
typedef struct e
{
    int a;          // node a
    int b;          // node b
    int v;          // value
}el;

el edge[1000];      // edge list
int nMax = 100;     // max num of node
int eMax = 1000;    // max num of edge
int dis[100];       // distance of edge
int eIndex[100];    // min outer edge's index
int ans[100][100];  // answer adjensity matrix
int eCnt=0;         // count of edges
int nCnt=0;         // count of nodes
int vis[100];       // Disjoint-sets Forest

/* initial vis[] */
int initVis()
{
    int i;
    for (i=0; i<nMax; ++i)
        vis[i] = i;
}
/* find the new last visited index in the subtree*/
int find(int x)
{
    return x == vis[x] ? x : (vis[x] = find(vis[x]));
}
/* union two node */
void uni(int x, int y) {
    int k=find(x);
    int f=find(y);
    vis[k] = f;
}
/* compare edge's value */
int cmp(const void *a,const void *b)
{
    return (*(el*)a).v-(*(el*)b).v;
}
/* Sollin's algorithm */
void sollin()
{
    initVis(); // initial vis[]

    while (1)
    {
        int efind = 0; //fining edge
        for (int i=0; i<nMax; ++i) dis[i] = 1e9; //initial dis[]

        for (int i=0; i<eMax; ++i)
        {
            int a = find(edge[i].a);
            int b = find(edge[i].b);
            int c = edge[i].v;
            if (a == b) continue; // circle
            efind++;
            /* store the selected distance */
            if (c < dis[a] || c == dis[a] && i < eIndex[a]) //check if it is smallest
                dis[a] = c, eIndex[a] = i;
            if (c < dis[b] || c == dis[b] && i < eIndex[b]) //check if it is smallest
                dis[b] = c, eIndex[b] = i;
        }

        if (efind == 0) break; //edge not found

        /* store in answer and union 2 nodes */
        for (int i=0; i<nMax; ++i)
            if (dis[i] != 1e9)
            {
                /* store the distance value in answer */
                ans[edge[eIndex[i]].a][edge[eIndex[i]].b]=edge[eIndex[i]].v;
                ans[edge[eIndex[i]].b][edge[eIndex[i]].a]=edge[eIndex[i]].v;

                uni(edge[eIndex[i]].a, edge[eIndex[i]].b); // union
            }
    }
}

int main()
{
	int a, b, value;
    memset(ans,0,sizeof(ans)); //initialize ans[]

    /* data input and store in struct edge[]*/
	printf("Please enter the number of nodes (limit : 99) : \n");
	scanf("%d", &nCnt); //max num of nodes
	while (1)
	{
		printf("Please enter 2 connected nodes' index(0 ~ %d) and the distance\n",nCnt-1);
		printf("Sample format : a b distance");
		printf("if you want to stop, please enter : 0 0 0\n");
		scanf("%d%d%d", &a, &b, &value);
		if (value == 0&&a==0&&b==0)
			break;
        edge[eCnt].a=a;
        edge[eCnt].b=b;
        edge[eCnt].v=value;
        eCnt++;
	}
	qsort(edge,eCnt,sizeof(edge[0]),cmp); //sort the edge by it value(small->big)

	sollin(); //Sollin's algorithm

	/* print the answer matrix */
	int i, j;
	for (i = 0; i < nCnt; i++)
	{
		for (j = 0; j < nCnt; j++)
		{
			printf("%4d ", ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
