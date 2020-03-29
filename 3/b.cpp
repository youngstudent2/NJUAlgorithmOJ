#include<iostream>
#include<vector>
#include<string>
using namespace std;
template<class T>
class MinHeap{
public:
    MinHeap(int size);
    MinHeap(T arr[],int n);
    bool insert(T ele);
    bool pop();
    bool isFull();
    bool isEmpty();
    void print();
    int Size();
    T top();
private:
    T *heap;
    int currentSize;
    int maxHeapSize;
    void siftDown(int start,int end);
    void siftUp(int start);
};

template<class T>
MinHeap<T>::MinHeap(int size){
    maxHeapSize=size;
    heap=new T[size];
    currentSize=0;
    maxHeapSize=size;
}

template<class T>
MinHeap<T>::MinHeap(T arr[],int n){
    maxHeapSize=n;
    heap=new T[maxHeapSize];
    currentSize=n;
    for(int i=0;i<n;i++){
        heap[i]=arr[i];
    }
    int currentPos=(n-2)/2;
    while(currentPos>=0){
        siftDown(currentPos,currentSize-1);
        currentPos--;
    }
}

template<class T>
bool MinHeap<T>::isFull(){
    return currentSize==maxHeapSize;
}

template<class T>
bool MinHeap<T>::isEmpty(){
    return currentSize==0;
}

template<class T>
void MinHeap<T>::siftDown(int start,int end){
    T tmp=heap[start];
    int i=start;
    int j=i*2+1;
    while(j<=end){
        if(j<end&&heap[j]>heap[j+1])j++;
        if(tmp>heap[j]){
           heap[i]=heap[j];
           i=j;
           j=i*2+1; 
        }
        else{
            break;
        }
    }
    heap[i]=tmp;
}

template<class T>
void MinHeap<T>::siftUp(int start){
    T tmp=heap[start];
    int j=start,i=(j-1)/2;
    while(j>0){
        if(heap[i]>tmp){
            heap[j]=heap[i];
            j=i;
            i=(j-1)/2;
        }
        else{
            break;
        }
    }
    heap[j]=tmp;
}

template<class T>
bool MinHeap<T>::pop(){
    if(this->isEmpty())return false;
    heap[0]=heap[currentSize-1];
    siftDown(0,--currentSize-1);
    return true;
}

template<class T>
bool MinHeap<T>::insert(T ele){
    if(this->isFull())return false;
    heap[currentSize]=ele;
    siftUp(currentSize++);
    return true;
}

template<class T>
void MinHeap<T>::print(){
    for(int i=0;i<currentSize;i++){
        cout<<heap[i]<<' ';
    }
    cout<<endl;
}

template<class T>
int MinHeap<T>::Size(){
    return currentSize;
}

template<class T>
T MinHeap<T>::top(){
    return heap[0];
}

struct lessInCome{
    string val;
    bool operator>(lessInCome& x){
        return val<x.val;
    }
    friend bool operator<(const string x,const lessInCome& y){
        return x<y.val;
    }
    lessInCome(string v):val(v){}
    lessInCome(){}
    friend ostream& operator<<(ostream& out,const lessInCome& c){
        out<<c.val;
        return out;
    }
};
struct moreInCome{
    string val;
    bool operator>(moreInCome& x){
        return val>x.val;
    }

    friend bool operator>(const string x,const moreInCome& y){
        return x>y.val;
    }
    moreInCome(string v):val(v){}
    moreInCome(){}
    friend ostream& operator<<(ostream& out,const moreInCome& c){
        out<<c.val;
        return out;
    }
};

inline void swap(string& s1,string& s2){
    string tmp = s1;
    s1 = s2;
    s2 = tmp;
}
int findMidStr(int left,int right,vector<string> &strs,int count){

/*
    for(int i=left;i<=right;++i)
        cout<<strs[i]<<' ';
    cout<<endl;*/
    string key=strs[right];
	int i=left,j=right-1;
	while(i<=j)
	{
		while(strs[i]<key)i++;
		while(strs[j]>key)j--;
		if(i<=j)
			swap(strs[i++],strs[j--]);				
	}
    int leftSize = i - left;
    int newCount = count - leftSize;
    /*
    cout<<"leftSize:"<<leftSize<<" count:"<<count<<endl;
    for(int i=left;i<=right;++i)
        cout<<strs[i]<<' ';
    cout<<endl;
    */

    if(newCount==0)return right;
    else if(newCount>0)return findMidStr(i,right - 1,strs,newCount-1);
    else return findMidStr(left,j,strs,count);


    
}

int main()
{
    int n,k;
    cin>>n>>k;
    vector<string> strs(n);
    for(auto p = strs.begin();p!=strs.end();++p)
        cin>>*p;

    MinHeap<lessInCome> minHeap(n);
    MinHeap<moreInCome> maxHeap(n);

    int midIndex = findMidStr(0,n-1,strs,(n-1)/2);
    string key = strs[midIndex];
    //cout<<"mid str is "<<key<<endl;
    for(int i=0;i<strs.size();++i)
        if(strs[i]<key){
            minHeap.insert(strs[i]);
        }
        else{
            if(i==midIndex)continue;
            maxHeap.insert(strs[i]);
        }
    /*
    cout<<"max heap is :"<<endl;
    maxHeap.print();
    cout<<"min heap is :"<<endl;
    minHeap.print();
    */

    string *ans = new string[k*2+1];
    ans[k] = strs[midIndex];
    for(int i=k-1;i>=0;--i){
        ans[i] = minHeap.top().val;
        minHeap.pop();
    }
    for(int i=k+1;i<2*k+1;++i){
        ans[i] = maxHeap.top().val;
        maxHeap.pop();
    }    

    for(int i=0;i<2*k+1;i++){
        cout<<ans[i]<<' ';
    }
    //cout<<endl;
    return 0;
}
/*
10 2
7 2 9 4 5 1 3 8 6 0
*/