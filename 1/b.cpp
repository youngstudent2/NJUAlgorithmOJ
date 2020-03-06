#include<iostream>
using namespace std;
void quicksort(int left,int right,int date[])
{
	int mid=date[(left+right)/2];
	int i=left,j=right;
	while(i<=j)
	{
		while(date[i]<mid)i++;
		while(date[j]>mid)j--;
		if(i<=j)
		{
			int t=date[i];
			date[i]=date[j];
			date[j]=t;
			i++;j--;		
		}
	}
	if(i<right)quicksort(i,right,date);
	if(j>left)quicksort(left,j,date);
}
int main()
{
    int k,n;
    cin>>k>>n;
    int *a=new int[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    quicksort(0,n-1,a);

    for(int i=n/2-k-1;i<n/2+k;i++)
        cout<<a[i]<<' ';
    


    return 0;
}