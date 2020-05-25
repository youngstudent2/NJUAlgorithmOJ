#include <iostream>
#include <vector>
using namespace std;

#define INF 0xFFFFFFF	//INF表示∞
inline int max(int a, int b) {
    return a > b ? a : b;
}
struct Edge
{
    int to;
    int length;
    Edge(int to, int length) :to(to), length(length) {}
};

struct Node
{
    int in_d;
    int dis;
    vector<Edge> edges;
    Node() {
        in_d = 0;
        dis = 0;
    }
    void addEdge(int to, int length) {
        edges.push_back(Edge(to, length));
    }
};




class Graph
{
    Node* nodes;
    int n;
public:
    Graph(int n) {
        this->n = n;
        nodes = new Node[n];

    }
    void initEdges() {
        int a, b, w;
        while (scanf("%d%d%d", &a, &b, &w) == 3) {
            nodes[a].addEdge(b, w);
            nodes[b].in_d++;
        }
    }



    void output_path_length(int s) {
        for (auto p = nodes; p != nodes + n; ++p) {
            if (p != nodes + s)
                printf("%d ", p->dis);
        }
    }


    void topsort() {
        vector<int> topOrder;
        int top = 0, p = 0;
        nodes[0].in_d = top;
        for (int i = 0; i < n; ++i) {
            p = top;
            top = nodes[top].in_d;
            for (auto e = nodes[p].edges.begin(); e != nodes[p].edges.end(); ++e) {
                int u = e->to;
                nodes[u].dis = max(nodes[u].dis, nodes[p].dis + e->length);
                nodes[u].in_d--;
                if (nodes[u].in_d == 0) {
                    nodes[u].in_d = top;
                    top = u;
                }

            }
        }

        
    }

    
};




int main()
{
    //cout << "I have read the rules about plagiarism punishment" << endl;
    printf("I have read the rules about plagiarism punishment\n");
    int n;
    scanf("%d", &n);
    Graph g(n);
    g.initEdges();
    g.topsort();
    g.output_path_length(0);
    //cout << endl;
    //system("pause");
    return 0;
}
/*
7
0 1 1
0 3 2
1 2 6
2 4 1
2 5 2
3 4 3
3 1 4
4 5 1
3 6 3
6 4 2

*/
