#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge {
    int x, y;
    int cost;
    friend istream& operator>>(istream& in, Edge& e) {
        in >> e.x >> e.y >> e.cost;
        return in;
    }
    Edge& operator=(const Edge& e){
		x = e.x;
		y = e.y;
		cost = e.cost;
		return *this;
	}
};
class Union {
private:
    int *eles;
public:
    Union(int n) {
        eles = new int[n];
        for (int i = 0; i < n; i++) {
            eles[i] = i;
        }
    }
    int find(int x) {
        int fx = eles[x];
        if (x != fx) {
            eles[x] = find(fx);
        }
 
        return eles[x];
    }
    void unionSet(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        eles[ry] = rx;
    }
    bool inUnion(int x, int y) {
        return find(x) == find(y);
    }
};

bool cmp(const Edge& e1, const Edge& e2){
	return e1.cost < e2.cost;
}
int main()
{
    long long int total_cost = 0;
    vector<Edge> edges;
    int n;
    cin >> n;
    Union u(n);
    //input edges
    for (Edge tmp; cin>>tmp; edges.push_back(tmp));
     
    //sort edges
	/* OJ 不支持 lambda表达式
    sort(edges.begin(), edges.end(),
        [](const Edge& e1, const Edge& e2)->bool {return e1.cost < e2.cost; }
    );*/

	sort(edges.begin(), edges.end(), cmp);

    //Kruskal build MST
    for (int i = 0; i < edges.size(); i++) {
        if (!u.inUnion(edges[i].x, edges[i].y)) {
            u.unionSet(edges[i].x, edges[i].y);
            total_cost += edges[i].cost;
        }
    }
    cout << total_cost;
    //system("pause");
    return 0;
}
/*
6
0 1 6
0 2 1
0 3 5
1 2 5
1 4 3
2 3 7
2 4 5
2 5 4
3 5 2
4 5 6
*/