#include<iostream>
/*
#include<list>
#include<cstdlib>
#include<algorithm>*/
using namespace std;

int findMedium(int *a,int *b,int len){
    int i = len>>1;
    int j = len - i;
    int left = 0;
    int right = len;
    while(1){
        if(((i>0&&j<len)?(a[i-1]<=b[j]):true)
        &&((j>0&&i<len)?(b[j-1]<=a[i]):true)){
            return a[i-1]>b[j-1]?a[i-1]:b[j-1];
        }
        else if((i>0&&j<len)?(a[i-1]>b[j]):false){
            right = i-1;
            i = left+(i-left)/2;
            j = len - i;
        }
        else{
            left = i+1;
            i = i+(right-i+1)/2;
            j = len - i;
        }
    }
    return -1;
}
/*调试用 对拍
void generator(int &n,int*&a,int*&b){
    list<int> la,lb;
    n = rand()%1000;
    for(int i=0;i<n;i++){
        la.push_back(rand()%200);
        lb.push_back(rand()%200);
    }
    la.sort();
    lb.sort();
    a = new int[n];
    b = new int[n];
    int i=0;
    for(auto pa = la.begin();pa!=la.end();++pa){
        a[i++]=*pa;
    }
    i=0;
    for(auto pb = lb.begin();pb!=lb.end();++pb){
        b[i++]=*pb;
    }
}

void print(int n,int* a,int* b){
    printf("\n%d\n",n);
    for(int i=0;i<n;++i){
        printf("%d ",a[i]);
    }
    printf("\n");
    for(int i=0;i<n;++i){
        printf("%d ",b[i]);
    }
}

int rightMedium(int* a,int *b,int len){
    int *l = new int [len<<1];
    int k=0;
    for(int i=0;i<len;++i)
        l[k++]=a[i];
    for(int i=0;i<len;++i)
        l[k++]=b[i];
    sort(l,l+len*2);
    int ans = l[len-1];
    free(l);
    return ans;

}
*/
int main()
{
    
    int n;
    scanf("%d",&n);
    int *a = new int[n];
    int *b = new int[n];
    for(int* i=a;i<a+n;++i)
        scanf("%d",i);
    for(int* i=b;i<b+n;++i)
        scanf("%d",i);
    

    printf("%d",findMedium(a,b,n));
/*
    srand(100);
    int n,*a,*b;
    for(int i=0;i<500;++i){
        generator(n,a,b);
        int ans1 = findMedium(a,b,n);
        int ans2 = rightMedium(a,b,n);
        if(ans1!=ans2){
            print(n,a,b);
            printf("\n%d %d\n",ans1,ans2);
            break;
        }
        free(a);
        free(b);
    }*/
    return 0;
}
/*
4
1 13 19 23
8 11 12 20

3 
1 3 9
2 4 6
*/