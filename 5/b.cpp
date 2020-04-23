#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

enum Color {White,Black,Grey};
struct Node{
    Color color;
    vector<Node*> neighbors;
    Node* father;
    int index;
    int back,discoverTime;
    Node(){
        color = White;
        father = NULL;
    }
    void visit_sign(int time){
        this->color = Grey;
        this->discoverTime = time;
        this->back = this->discoverTime;
    }
    void visited(){
        this->color = Black;
    }
};

void link(Node* na,Node* nb){
    na->neighbors.push_back(nb);
    nb->neighbors.push_back(na);
}

inline int min(const int&a,const int&b){return a<b?a:b;}

int articulation_point_dfs(Node* curNode,int &time,vector<int> &res){
    curNode->visit_sign(++time);
    for(int i=0;i<curNode->neighbors.size();++i){
        auto &w = curNode->neighbors[i];
        if(w->color==White){
            w->father = curNode;
            w->back = articulation_point_dfs(w,time,res);
            if(w->back>=curNode->discoverTime){
                //articulation point curNode found
                res.push_back(curNode->index);
            }
            curNode->back=min(curNode->back,w->back);
        }
        else{
            if(w->color==Grey && curNode->father!=w){
                curNode->back=min(curNode->back,w->discoverTime);
            }
        }
    }
    curNode->visited();
    return curNode->back;
}

struct Edge{
    int u,v;
    Edge(int a,int b){
        if(a<b){
            u = a;
            v = b;
        }
        else{
            u = b;
            v = a;
        }
    }
};

int bridge_dfs(Node*curNode,int &time,vector<Edge*> &res){
    curNode->visit_sign(++time);
    for(int i=0;i<curNode->neighbors.size();++i){
        auto &w = curNode->neighbors[i];
        if(w->color==White){
            w->father = curNode;
            bridge_dfs(w,time,res);
            curNode->back = min(curNode->back,w->back);
            if(w->back>curNode->discoverTime){
                // bridge curNode-w found
                res.push_back(new Edge(curNode->index,w->index));
            }
        }
        else{
            if(w->color == Grey && curNode->father!=w){
                curNode->back = min(curNode->back,w->discoverTime);
            }
        }
    }
    curNode->visited();
    return curNode->back;
}

bool cmp1(const Edge* e1,const Edge* e2){return e1->u<e2->u;}


int main()
{
    printf("wo yi yue du guan yu chao xi de shuo ming\n");
    int n;
    cin>>n;
    Node *nodes = new Node[n];
    for(int i=0;i<n;++i)nodes[i].index = i;
    int n1,n2;
    while(cin>>n1>>n2){
        link(nodes+n1,nodes+n2);
    }
    int time = 0;
    vector<int> res_nodes;
    vector<Edge*> res_bridges;
    articulation_point_dfs(nodes,time,res_nodes);

    time = 0;
    for(int i=0;i<n;++i){
        nodes[i].color = White;
        nodes[i].father = NULL;
    }   
    bridge_dfs(nodes,time,res_bridges);

    sort(res_nodes.begin(),res_nodes.end());
    //sort(res_bridges.begin(),res_bridges.end(),[](Edge* &e1,Edge* &e2)->bool{return e1->u<e2->u;});
    sort(res_bridges.begin(),res_bridges.end(),cmp1);
    int count = 0;
    for(int i=0;i<n;i++)
        if(nodes[i].father==&nodes[0])
            ++count;
    int c = 0;
    if(count<=1&&res_nodes[0]==0)c=1;
    for(int i=c;i<res_nodes.size();i++)cout<<res_nodes[i]<<endl;
    for(int i=0;i<res_bridges.size();++i)cout<<res_bridges[i]->u<<' '<<res_bridges[i]->v<<endl;
    return 0;
}
/*
5
1 2
1 3
2 4
0 1
0 2
*/