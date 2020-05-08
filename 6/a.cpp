#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<stack>
using namespace std;

enum Color { White, Black, Grey };
struct Node {
    Color color;
    vector<Node*> neighbors;
    int index;
    int back, discoverTime;
    int scc;
    Node() {
        color = White;
    }
    void visit_sign(int time) {
        this->color = Grey;
        this->discoverTime = time;
        this->back = this->discoverTime;
    }
    void visited() {
        this->color = Black;
    }
    void scc_sign(int x) {
        scc = x;
    }
};

struct SCCNode{
    Color color;
    bool* to;
    int index;
    int impact;
    int* source_impact;
    vector<int> source_nodes;
    SCCNode() {
        color = White;
        impact = 0;
        
    }
    void align(int n) {
        to = new bool[n];
        for (int i = 0; i < n; ++i)to[i] = 0;          
    }
    void source_impact_init(int n) {     
        source_impact = new int[n];
        for (int i = 0; i < n; ++i)source_impact[i] = 0;
        impact = source_nodes.size();
        source_impact[index] = source_nodes.size();
    }
    void visit_sign() {
        this->color = Grey;
    }
    void visited() {
        this->color = Black;
    }
    void update_impact_source(const SCCNode& v,int n) {
        for (int i = 0; i < n; i++) {
            if (v.source_impact[i] > source_impact[i]) {
                impact += v.source_impact[i] - source_impact[i];
                source_impact[i] = v.source_impact[i];
                
            }
                
        }
    }
};

inline int min(int a, int b) {
    return a > b ? b : a;
}
inline int max(int a, int b) {
    return a > b ? a : b;
}
void tarjan(Node& v, int& time, stack<Node*> &s,int &count) {
    v.visit_sign(time++);
    s.push(&v);
    for (auto n = v.neighbors.begin(); n != v.neighbors.end(); ++n) {
        auto &u = *n;
        if (u->color == White) {
            tarjan(*u, time, s, count);
            v.back = min(v.back, u->back);
        }
        else {
            if (u->color == Grey) {
                v.back = min(v.back, u->discoverTime);
            }
        }

    }
    if (v.discoverTime == v.back) {
        //cout << "count " << count << ':';
        while (s.top() != &v) {
            //cout << s.top()->index << ' ';
            s.top()->scc_sign(count);
            s.pop();
        }
        //cout << v.index << endl;
        s.top()->scc_sign(count++);
        s.pop();
    }
    v.visited();
}

void scc_dfs(SCCNode& v,int n,SCCNode * nodes) {
    v.visit_sign();
    for (int i = 0; i < n; i++) {
        if (v.to[i]) {
            auto& u = nodes[i];
            if (u.color == White) {
                scc_dfs(u,n,nodes);
                v.update_impact_source(u,n);
            }
            else {
                v.update_impact_source(u, n);
            }
        }
    }
    v.visited();
}


int main()
{
    Node* nodes;
    string str;
    vector<string> buf;
    while (getline(cin, str))
        buf.push_back(str);
    int n = buf.size();
    nodes = new Node[n];
    for (int i = 0; i < n; i++)nodes[i].index = i;
    auto node = nodes;
    for (auto i = buf.begin(); i != buf.end(); ++i, ++node) {
        istringstream iss(*i);
        int neighbourNode;
        while (iss >> neighbourNode) {
            node->neighbors.push_back(nodes + neighbourNode);
        }
    }
    buf.clear();
    
    // find all scc
    int scc_num = 0;
    int time = 0;
    stack<Node*> s;
    for (node = nodes; node != nodes + n; ++node) {
        if (node->color == White)
            tarjan(*node, time, s, scc_num);
    }

    //cout << endl << scc_num << endl;

    // build scc sub graph
    SCCNode* scc_nodes = new SCCNode[scc_num];
    for (int i = 0; i < scc_num; ++i) {
        scc_nodes[i].index = i;
        scc_nodes[i].align(scc_num);
    }
        
    for (node = nodes; node != nodes + n; ++node) {
        auto& v = scc_nodes[node->scc];
        v.source_nodes.push_back(node->index);
        // add new edge
        for (auto n = node->neighbors.begin(); n != node->neighbors.end(); ++n) {
            auto &u = *n;
            v.to[u->scc] = 1;
        }
        // remove self edge
        v.to[v.index] = 0;
    }

    delete[] nodes;

    for (int i = 0; i < scc_num; ++i) {
        scc_nodes[i].source_impact_init(scc_num);
    }

    /*
    print SCC
    
    cout << "scc nodes:" << endl;
    for (int i = 0; i < scc_num; ++i) {
        cout << scc_nodes[i].index << ':';
        for (auto& v : scc_nodes[i].source_nodes) {
            cout << v << ' ';
        }
        cout << endl;
    }
*/
    //print sub graph
    /*
    for (int i = 0; i < scc_num; ++i) {
        auto& u = scc_nodes[i];
        for (int j = 0; j < scc_num; ++j) {
            //cout << u.to[j] << ' ';
            cout << u.source_impact[j] << ' ';
        }
        cout << endl;
    }
    */


    // dfs scc graph
    for (auto node = scc_nodes; node != scc_nodes + scc_num; ++node) {
        if (node->color == White) {
            scc_dfs(*node,scc_num,scc_nodes);
        }
    }

    // get max nodes
    int max_impact = -1;
    for (int i = 0; i < scc_num; ++i) {
        //cout << scc_nodes[i].impact << ' ';
        max_impact = max(scc_nodes[i].impact, max_impact);
    }
    //cout << endl;
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << max_impact - 1 << endl;
    for (int i = 0; i < scc_num; ++i) {
        if (max_impact == scc_nodes[i].impact) {
            for (auto node = scc_nodes[i].source_nodes.begin(); node != scc_nodes[i].source_nodes.end(); ++node) {
                auto& u = *node;
                cout << u << ' ';
            }
        }
    }
    
    //system("pause");
    return 0;
}
/*
1
2 3
0
4
5
3

1 5
2
3
1 4

6
5 4
1 5

*/