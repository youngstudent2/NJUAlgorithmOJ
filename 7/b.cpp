#include<iostream>
#include<queue>
#define INF 0xFFFFFFF
using namespace std;
struct Edge
{
    int to;
    int length;
    Edge(int to, int length) :to(to), length(length) {}
    bool operator<(const Edge& e){
        return length<e.length;
    }
};

struct Node
{
    bool vis;
    int dis;
    vector<Edge> edges;
    Node() {
        vis = 0;
        dis = 0;
    }
    void addEdge(int to, int length) {
        edges.push_back(Edge(to, length));
    }
};

void init(Node* nodes){
    int a,b,w;
    while(scanf("%d%d%d",&w,&a,&b)==3){
        nodes[a].addEdge(b,w);
    }
}

void update_fringe(Node* nodes,int v,priority_queue<Edge>& q){
    for(auto e = nodes[v].edges.begin(); e != nodes[v].edges.end(); ++e){
        auto w = e->to;
        int newPriority = max(nodes[v].dis,e->length);
        if(!nodes[w].vis){
            nodes[w].vis = 1;
            q.push(*e);
        }
        else{
            if(newPriority>nodes[w].dis){
                q.decreaseKey();
            }
        }
    }
}

void dijkstra(Node* nodes,int s,int t){
    priority_queue<Edge> q;
    nodes[s].dis = 0;
    for(auto e = nodes[s].edges.begin(); e != nodes[s].edges.end(); ++e){
        q.push(*e);
    }
    while(!q.empty()){
        auto x = q.top();
        q.pop();
        nodes[x.to].dis = x.length;
        update_fringe(nodes,x.to,q);
    }
}

int main()
{
    int n,s,t;
    scanf("%d%d%d",&n,&s,&t);

    Node* nodes = new Node[n];
    init(nodes);

    cout<<"I have read the rules about plagiarism punishment"<<endl;
    






    return 0;
}