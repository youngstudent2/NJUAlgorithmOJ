#include<iostream>
#include<string>
using namespace std;
long long int count = 0;
void mergearray(string a[],int first,int mid,int last,string temp[])
{
	//for(int i=first;i<=last;++i)cout<<a[i]<<" ";
	//cout<<endl;
	int k=0;
	int i=first,j=mid+1;
	while(i<=mid&&j<=last)
        if(a[i]<=a[j]){
            temp[k++]=a[i++];
        }
        else{
            //逆序对存在
			//cout<<"add:"<<mid-i+1<<endl;
            count+=mid-i+1;
            temp[k++]=a[j++];
        }

        
    while(i<=mid)
		temp[k++]=a[i++];
		
    while(j<=last)
		temp[k++]=a[j++];
		
    for(i=0;i<k;i++)a[i+first]=temp[i];
}
void mergesort(string a[],int first,int last,string temp[])
{
	int mid;
	if(first<last)
	{
		mid=(first+last)/2;
		mergesort(a,first,mid,temp);//左有序 
		mergesort(a,mid+1,last,temp);//右有序 
		mergearray(a,first,mid,last,temp);//合并 
	}
}

string num_to_str(int k){ //for test
	char str[11];
	char ch;
	sprintf(str,"%010d",k);
	cout<<str<<endl;
	return str;
}
int main()
{
	cout<<"wo yi yue du guan yu chao xi de shuo ming\n";
	int n;
	cin>>n;
	string *a = new string[n];
	string *b = new string[n];
	for(int i=0;i<n;i++){
		cin>>a[i];
		//a[i]=num_to_str(n-i);
	}
	mergesort(a,0,n-1,b);
	cout<<count;
	return 0;
}
/*
8
4 2 1 3 5 8 6 9
*/