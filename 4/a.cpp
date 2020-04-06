#include<iostream>
#include<list>
#include<cstdlib>
#include<algorithm>
using namespace std;

int findMedium(int *a,int *b,int len){
    if(len == 0)
        return 0;
    if(len == 1)
        return *a<=*b?*a:*b;
    if(len == 2){
        if(*a<*b){
            ++a;
            return *a<=*b?*a:*b;
        }
        else{
            ++b;
            return *b<=*a?*b:*a;
        }
    }
    int half_len = len/2;
    int mid1 = *(a+half_len);
    int mid2 = *(b+half_len);
    cout<<len<<' '<<mid1<<' '<<mid2<<endl;
    if(mid1>mid2){
        if(len&0x1) return findMedium(a,b+half_len,half_len+1);
        return findMedium(a,b+half_len,half_len);
    }
    else if(mid1<mid2){
        if(len&0x1) return findMedium(a+half_len,b,half_len+1);
        return findMedium(a+half_len,b,half_len);
    }
    else return mid1;
}

void generator(int &n,int*&a,int*&b){
    list<int> la,lb;
    n = rand()%10;
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

int main()
{
    /*
    int n;
    scanf("%d",&n);
    int *a = new int[n];
    int *b = new int[n];
    for(int* i=a;i<a+n;++i)
        scanf("%d",i);
    for(int* i=b;i<b+n;++i)
        scanf("%d",i);
    

    printf("%d",findMedium(a,b,n));
*/
/**/
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
    }
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