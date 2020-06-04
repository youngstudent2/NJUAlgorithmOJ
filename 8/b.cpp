#include<iostream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

inline int min(int a, int b) { return a < b ? a : b; }

struct TreeNode {
    vector<int> children;
    int val;
    int visited;
    TreeNode() :val(0) { visited = false; }
    TreeNode(int v) :val(v) { visited = false; }
};

class Tree {
private:
    int n;
    vector<TreeNode> nodes;


public:

    Tree() : n(0) {}
    void getInput() {
        string s;
        TreeNode tmp;

        while (getline(cin, s)) {
            stringstream ss(s);
            ss >> tmp.val;
            int t;
            while (ss >> t) {
                tmp.children.push_back(t);
            }
            
            nodes.push_back(tmp);
            tmp.children.clear();
        }
        n = nodes.size();
    }
    int* d1, * d2;
    void dfs(int x) {
        auto& p = nodes[x];

        p.visited = 1;
        int v;
        for (auto i = p.children.begin(); i != p.children.end(); ++i) {
            if (!nodes[*i].visited) {
                dfs(*i);
                v = nodes[*i].val;
                d1[p.val] += d2[v];
                d2[p.val] += min(d1[v], d2[v]);
            }
        }


    }

    int setGuard() {
        d1 = new int[n];
        d2 = new int[n];
        for (int i = 0; i < n; ++i) {
            d1[i] = 0;
            d2[i] = 1;
        }
        dfs(0);
        return min(d1[0], d2[0]);
    }




};



int main()
{
    Tree tree;
    tree.getInput();
    cout << "I have read the rules about plagiarism punishment" << endl;
    

    cout << tree.setGuard();
    //system("pause");
    return 0;
}
/*

0 1 2
1 3
2 7 8
3 4 5
4
5 6
6
7 9
8
9

0 1
1 2 3
2
3

0 1
1 2
2 3
3 4
4 5
5 6
6

*/