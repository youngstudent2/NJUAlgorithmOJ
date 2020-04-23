#include<iostream>
#include<stdlib.h>
using namespace std;
int cmp(const void *a,const void *b){
    return *(int*)a-*(int*)b;
}
int triple_sum(int target, int *a, int n){
    if(n<3)return 0;
    int *l, *r;
    int ans = 0;
    for(int i=0;i<n;++i){
        register int targetSum = target - a[i];
        l = a+i;
        r = a+n-1;
        while(l<r){
            int lrSum = *l+*r;
            if(lrSum>targetSum){
                --r;
            }
            else if(lrSum<targetSum){
                ++l;
            }
            else{
                //cout<<a[i]<<' '<<*l<<' '<<*r<<endl;
                ++ans;
                ++l;
                --r;
            }
        }
    }
    return ans;
}

int main(){
    printf("wo yi yue du guan yu chao xi de shuo ming\n");
    int n;
    int target;
    scanf("%d%d",&n,&target);
    int *a = new int[n];
    for(int *p = a;p<a+n;++p)
        scanf("%d",p);
    qsort(a,n,sizeof(int),cmp);
    
    printf("%d",triple_sum(target,a,n));

    return 0;
}
/*
6 3
8 0 -5 -2 6 -1


*/