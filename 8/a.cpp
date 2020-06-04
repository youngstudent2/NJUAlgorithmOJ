#include<iostream>
#include<vector>
using namespace std;


inline int max(int a,int b){
    if(a>b)return a;
    return b;
}

class TriArray{
    int *p;
    int n;
public:
    TriArray(int n){
        int length = n*(n+1)/2;
        p = new int[length];
        this->n = n;
    }
    int get(int x,int y){
        return p[Index(x,y)]; 
    } 
    void set(int x,int y,int newValue){
        p[Index(x,y)] = newValue;
    }
private:
    inline int Index(int x,int y){
        return y+(2*n-x-1)*x/2;
    }
};


int main()
{
    char ch;
    vector<char> a;
    while(scanf("%c",&ch)!=EOF){
        if(ch!=' '&&ch!='\n')
            a.push_back(ch);
    }

    printf("I have read the rules about plagiarism punishment\n");
    int n = a.size();
    /*
    int **dp = new int*[n];
    for(int i=0;i<n;++i){
        dp[i] = new int[n];
        dp[i][i] = 1;
    }
    */
    TriArray dp(n);
    for(int i=0;i<n;++i){
        dp.set(i,i,1);
    }

    for(int i=n-2;i>=0;--i){
        for(int j=i+1;j<n;++j){
            if(a[i]==a[j])
                //dp[i][j] = dp[i+1][j-1]+2;
                dp.set(i,j,dp.get(i+1,j-1)+2);
            else
                //dp[i][j] = max(dp[i+1][j],dp[i][j-1]);
                dp.set(i,j,max(dp.get(i+1,j),dp.get(i,j-1)));
        }
    }

    printf("%d",dp.get(0,n-1));
    return 0;
}
/*

A C G T G T C A A A A T C G

a d f e x e f d a

*/