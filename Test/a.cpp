#include<iostream>
using namespace std;

inline int max(int a, int b) {
    return a > b ? a : b;
}
int maxd = 0;
int dis = 0;
int solve(int* pre, int* pend, int* in, int* iend) {
    int root = pre[0];
    //cout << root << ' ';
    if (pend - pre <= 1) {
        return 0;
    }
    int* rootIn = in;
    while (rootIn != iend && *rootIn != root)++rootIn;
    int l = rootIn - in;
    int r = iend - in-l;
    int ld=-1, rd=-1;
    if (l)
        ld = solve(pre + 1, pend, in, rootIn - 1);
    if (r)
        rd = solve(pre + l + 1, pend, rootIn + 1, iend);
    int curd = max(ld, rd) + 1;

    maxd = max(maxd,curd);
    dis = max(dis,ld + rd+2);
    return curd;
}

int main() {

    int n;

    cout << "I have read the rules about plagiarism punishment" << endl;
    cin >> n;
    int* pre = new int[n];
    int* in = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> pre[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> in[i];
    }

    solve(pre, pre + n, in, in + n);
    cout << maxd << endl << dis;
    //system("pause");
    return 0;
}