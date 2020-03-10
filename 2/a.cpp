#include<iostream>
#include<map>
#include<string>
#include<set>
#include<queue>
using namespace std;

template<class A>
inline A insertSort(A s){
    for(auto i=s.begin()+1;i<s.end();++i){
        auto tmp = *i;
        auto j = i-1;
        for(;j>=s.begin()&&*j>tmp;--j){
            *(j+1)=*j;
        }
        *(j+1)=tmp;
    }
    return s;
}

string generate_sign(const string &str){
    return insertSort<string>(str);
}

typedef map<string,string>::iterator It;
class cmp{
public:
    bool operator()(const It &i1,const It &i2)const {
        return i1->second<i2->second;
    }
};

bool operator>(const It &i1,const It &i2)const {
    return i1->second<i2->second;
}

int main()
{
    cout<<"wo yi yue du guan yu chao xi de shuo ming"<<endl;
    string str;

    int n;
    cin>>n;
    map<string,string> strmap;
    priority_queue <It,vector<It>,greater<string> > q;
    for(int i=0;i<n;i++){
        cin>>str;
        string s = generate_sign(str);
        //cout<<str<<'-'<<s<<endl;
        auto it = strmap.find(s);
        if(it!=strmap.end()){ //变位词已存在
            q.push(it);
            if(it->second>str) //更新字典序更小的变位词
                it->second=str;
                
        }
        else{ //未存在变位词,装入容器中
            strmap[s]=str;
        }
    }
    //ans.sort();
    
    cout<<ans.size()<<endl;
    for(auto i=ans.begin();i!=ans.end();++i){
        q.push((*i)->second);
    }
    for(;!q.empty();q.pop()){
        cout<<q.top()<<endl;
    }
    return 0;
}
/*
15
a ew vc tea we eat zoo el le ozo ooz cv a kka akk
*/