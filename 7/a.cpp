#include <iostream>
using namespace std;

#define INF 0xFFFFFFF	//INF表示∞
inline int max(int a,int b){
    return a>b?a:b;
}


struct node 
{
    int k;//记录当前结点编号 
    struct node *next;
}*v;
void topsort(int n,int *indegree)
{
	int i;
	struct node *p;
	int *stack=(int*)malloc(sizeof(int)*n),top=-1;
	for(i=1;i<=n;i++)
	    if(indegree[i]==0)stack[++top]=i;//入度为0的点入栈 
    while(top>-1)                  //栈非空时循环 
    {
    	p=&v[stack[top--]];        //取出栈顶元素 
    	printf("%d ",stack[top+1]);
    	while(p->next!=NULL)       //枚举该点所有后继 
    	{
    		p=p->next;
	    	if(--indegree[p->k]==0)      //若去除一条边后入度为0则入栈 
	    	    stack[++top]=p->k;		
	    }    	
    }	
}

struct MGraph
{  	
	int **edges;		//邻接矩阵
   	int n;   
    int *indegree;					
    int *dp;
    int *vis;
    MGraph(int n){
        this->n=n;
        edges = new int*[n];
        for(int i=0;i<n;++i){
            edges[i] = new int[n];
            for(int j=0;j<n;++j){
                edges[i][j] = INF;
            }
        }
        dp = new int[n];
        vis = new int[n];
        indegree = new int[n];
        for(int i=0;i<n;++i){dp[i]=-INF;vis[i]=0;indegree[i]=0;v[i].next=NULL;}
        dp[0]=0;
    }
    void initEdges(){
        int a,b,w;
        while(scanf("%d%d%d",&a,&b,&w)==3){
            edges[a][b] = w;
            indegree[b]++;
        }
    }
    int solve(int v){
        if(vis[v])return dp[v];
        vis[v]=1;
        for(int i=0;i<n;i++){
            if(edges[i][v]!=INF)
                dp[v] = max(dp[v],solve(i)+edges[i][v]);
        }
        return dp[v];
    }   
};						




int main()
{
    cout<<"I have read the rules about plagiarism punishment"<<endl;
    int n;
    cin>>n;
	MGraph g(n);
    g.initEdges();
    v = (struct node*)malloc(sizeof(struct node)*n);
	topsort(n,g.indegree);
	
    
    return 0;
}
/*
6
0 1 1
0 3 2
1 2 6
2 4 1
2 5 2
3 4 3
3 1 4
4 5 1
*/
