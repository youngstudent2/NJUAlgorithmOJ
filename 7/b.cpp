#include<iostream>
#define INF 0xFFFFFFF
using namespace std;
int** initGraph(int n){
    int **g = new int*[n];
    for(int i=0;i<n;++i){
        g[i] = new int[n];
        for(int j=0;j<n;++j){
            g[i][j]=INF;
        }
    }

}
int main()
{
    int n,s,t;
    scanf("%d%d%d",&n,&s,&t);
    int **g = initGraph(n);
    int a,b,w;
    while(scanf("%d%d%d",&w,&a,&b)==3){
        g[a][b] = w;
    }
    cout<<"I have read the rules about plagiarism punishment"<<endl;
    
    return 0;
}