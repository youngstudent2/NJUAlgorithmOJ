#include<iostream>
#include<vector>
using namespace std;
struct Node{
    int value;
    int vis;
    int minvalue;
    vector<Node*> neighbour;
    Node():vis(0){}
};
inline int min(int a,int b){
    return a<b?a:b;
}
void dfs(Node* nodes){
    nodes->vis = 1;
    nodes->minvalue = nodes->value;
    for(auto p = nodes->neighbour.begin();p!=nodes->neighbour.end();++p){
        auto w = *p;
        if(!w->vis){
            dfs(w);
            nodes->minvalue = min(nodes->minvalue,w->minvalue);
        }
        else{
            nodes->minvalue = min(nodes->minvalue,w->minvalue);
        }
    }
}
int main(){

    int n,m;
    scanf("%d%d",&n,&m);
    Node *nodes = new Node[n+1];
    int v,value;
    for(int i=0;i<n;++i){
        cin>>v>>value;
        nodes[v].value = value;
    }
    int s,t;
    for(int i=0;i<m;++i){
        cin>>s>>t;
        nodes[s].neighbour.push_back(nodes+t);
    }

    for(int i=1;i<=n;++i){
        if(!nodes[i].vis){
            dfs(nodes+i);
        }
    }

    for(int i=1;i<=n;++i){
        cout<<nodes[i].minvalue<<' ';
    }

    return 0;
}
/*
6 6
1 2
2 3
3 6
4 1
5 4
6 5
1 3
2 4
3 5
3 6
4 5
4 6

6 6
1 2
2 3
3 6
4 1
5 1
6 5
1 3
2 4
3 5
3 6
4 5
4 6

*/