#include <iostream>
#include <vector>
#include <list>
using namespace std;

#define INF 0xFFFFFFF	//INF表示∞
inline int max(int a, int b) {
    return a > b ? a : b;
}

struct Node
{
    int index;
    bool vis;
    int out_d;
    int dis;
    list<Edge> edges; 
    Node() {
        vis = false;
        out_d = 0;
    }
    void addEdge(int to,int length){
        edges.push_back(Edge(to,length));
    }
};

struct Edge
{
    int from;
    int length;
    Edge(int from,int length):from(from),length(length){}
};


class Graph
{
    int** edges;		//邻接矩阵
    Node* nodes;
    int n;
public:
    Graph(int n) {
        this->n = n;
        nodes = new Node[n];
        for (int i = 0; i < n; ++i) {
            nodes[i].index = i;
        }

    }
    void initEdges() {
        int a, b, w;
        while (scanf("%d%d%d", &a, &b, &w) == 3) {
            nodes[b].addEdge(a,w);
        }
    }

    void longest_path_length(int s) {
        for (int i = 0; i < n; ++i) {
            nodes[i].dis = -INF;
        }
        nodes[s].dis = 0;
        list<int>& topOrder = this->topsort();
        for (auto v = topOrder.begin(); v != topOrder.end(); ++v) {
            if (*v != s) {
                for(auto e = nodes[*v].edges.begin();e!=nodes[*v].edges.end();++e){
                    nodes[*v].dis = max(nodes[*v].dis,nodes[e->from].dis+e->length);
                }
            }
        }
    }

    void output_path_length(int s) {
        for (auto p = nodes; p != nodes + n; ++p) {
            if(p!=nodes+s)
                printf("%d ",p->dis);
        }
    }

    list<int>& topsort() {
        list<int>* topOrder = new list<int>;
        for (int i = 0; i < n; ++i) {
            if (!nodes[i].vis && nodes[i].edges.size() == 0) {
                visit(i, *topOrder);
            }
        }

        return *topOrder;
    }
private:
    void visit(int i, list<int>& topOrder) {
        nodes[i].vis = 1;

        for(auto p = nodes[i].edges.begin();p!=nodes[i].edges.end();++p){
            if(!nodes[p->from].vis){
                visit(p->from,topOrder);
            }
        }

        topOrder.push_back(i);
    }
};




int main()
{
    //cout << "I have read the rules about plagiarism punishment" << endl;
    printf("I have read the rules about plagiarism punishment\n");
    int n;
    scanf("%d",&n);
    Graph g(n);
    g.initEdges();
    g.longest_path_length(0);
    g.output_path_length(0);
    //cout << endl;
    //system("pause");
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
