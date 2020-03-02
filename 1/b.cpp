#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int k,n;
    cin>>k>>n;
    int *a=new int[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    sort(a,a+n);
    /*
    for(int i=0;i<n;i++)cout<<a[i]<<' ';
    cout<<endl;*/
    for(int i=n/2-k-1;i<n/2+k;i++)
        cout<<a[i]<<' ';
    


    return 0;
}