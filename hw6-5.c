//==============================
// Homework 6 - 5
//==============================
// to calculate and output the e(i) and l(i)
// e(i) : earliest time of v-i -> etv
// l(i) : latest time of v-i   -> ltv
// for all activities i in an AOE network
//==============================
// belongs to CHinX2@20180105
//==============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000 // MAX vertex

typedef struct n
{
    int id;   //vertex index
    int val;  //value
    struct n *next;
}node; // likend node

typedef struct h
{
    int count;
    node *link;
}hNode; // header node

hNode graph[MAX];   // save graph's path
int etv[MAX];       // earlest time
int ltv[MAX];       // latest time
int stack[MAX];     // topological sort of vertex
int sTop;           // top of stack
int nCnt=0;         // number of nodes

/* initialize graph structure */
void init()
{
    int i;
    for(i=0;i<nCnt;i++)
    {
        graph[i].count=0;
        graph[i].link=NULL;
    }
    return;
}
/* adjencecy matrix insert */
node *insert(node *a,int b,int v)
{
    if(a==NULL)
    {
        a=(node*)malloc(sizeof(node));
        a->id=b;
        a->val=v;
        a->next=NULL;
    }
    else{
        a->next=insert(a->next,b,v);
    }
    return a;
}
/* topological sort & find the etv*/
int topsort()
{
    int i,j,k,top,count;
    node *ptr;
    count=0; //count the num of vertex

    //a stack of vertices with no predecessors
    top=-1;
    for(i=0;i<nCnt;i++)
    {
        if(graph[i].count==0)
        {
            graph[i].count=top;
            top=i;
        }
    }

    for(i=0;i<nCnt;i++)
    {
        if(top==-1) //cycle
        {
            printf("\nError!! Cycle exists.\n");
            return 0;
        }
        else{
            j=top; //unstack a vertex
            top=graph[top].count;
            //if(count>0)printf("-> ");
            //printf("v%d ",j);
            count++;
            stack[++sTop]=j; //store the vertex in stack
            for(ptr=graph[j].link;ptr;ptr=ptr->next)
            {
                k=ptr->id;
                graph[k].count--;
                //add vertex k into stack
                if(graph[k].count==0)
                {
                    graph[k].count=top;
                    top=k;
                }
                //get the earlest time of vertex (in etv)
                if((etv[j]+ptr->val)>etv[k])
                {
                    etv[k]=etv[j]+ptr->val;
                }
            }
        }
    }
    printf("\n");
    if(count<nCnt)return 0; // it is not feasible
    return 1;
}
/* find th ltv and critical path */
void critipath()
{
    node* ptr;
    int i,j,k;
    int ete,lte;

    int check=topsort();
    if(check==0)
    {
        printf("this AOE network is not feasible.\n");
        return;
    }
    /* initialize ltv[] */
    for(i=0;i<nCnt;i++)
    {
        ltv[i]=etv[nCnt-1];
    }

    while(sTop!=0)
    {
        j=stack[sTop--];
        /* get the latest time of veretex */
        for(ptr=graph[j].link;ptr;ptr=ptr->next)
        {
            k=ptr->id;
            if(ltv[k]-ptr->val<ltv[j])
            {
                ltv[j]=ltv[k]-ptr->val;
            }
        }
    }
    /* print etv and ltv */
    printf("e(i) : ");
    for(i=0;i<nCnt;i++)
    {
        printf("%d ",etv[i]);
    }
    printf("\n");
    printf("l(i) : ");
    for(i=0;i<nCnt;i++)
    {
        printf("%d ",ltv[i]);
    }
    printf("\n");

    /* critical path*/
    /*for(i=0;i<nCnt;i++)
    {
        for(ptr=graph[i].link;ptr;ptr=ptr->next)
        {
            k=ptr->id;
            ete=etv[i];
            lte=ltv[k]-ptr->val;
            if(ete==lte)
            {
                printf("[v%d -> v%d] %d\n",i,k,ptr->val);
            }
        }
    }*/
    return;
}

int main()
{
    int i,j,a;
    memset(etv,0,sizeof(etv));

    /* read in the adjacency cost matrix */
    printf("Please enter the number of nodes ( < 999 ) : ");
    scanf("%d",&nCnt);                                              //get the num of node
    init();                                                         // initialize graph[]
    printf("Please enter the adjacency matrix of graph :\n");
    for(i=0;i<nCnt;i++)
    {
        for(j=0;j<nCnt;j++)
        {
            scanf("%d",&a);
            if(a!=0)
            {
                graph[i].link=insert(graph[i].link,j,a);
                graph[j].count++;
            }
        }
    }
    /* find e(i),l(i),and critical path */
    critipath();

    return 0;
}
