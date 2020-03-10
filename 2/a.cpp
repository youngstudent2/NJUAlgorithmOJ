#include<iostream>
#include<map>
#include<string>
#include<list>
#include<queue>
using namespace std;

unsigned long JSHash(const string& str) {
	unsigned long hash = 1315423911;
	for (int i = 0; i < str.length(); ++i) {
		hash ^= ((hash << 5) + str.at(i) + (hash >> 2));
	}
	return hash;
}


string generate_sign(const string &str){
    unsigned short chs[26]={0};
    for(auto c=str.begin();c!=str.end();++c){
        ++chs[*c-'a'];
    }
    char res[50];
    for(int i=0;i<26;++i){
        if(chs[i]){
            sprintf(res,"%s%c%d",res,'a'+i,chs[i]);
        }
    }
    //cout<<str<<"->"<<res<<endl;
    return res;
}

class HashMap{
    string *mymap;
    list<int> indexTable;
    int size;
public:
    HashMap(int size){
        mymap = new string[size];
        this->size = size;
    }
    void insert(const string &s){
        unsigned long index = JSHash(generate_sign(s))%size;
        if(mymap[index]==""){
            mymap[index]=s;

        }
        else{
            //变位词存在 记录变位词
            //三个变位词会重复记录
            indexTable.push_back(index);
            if(mymap[index]>s){
                mymap[index]=s;
            }
        }
    }
    void printAll(list<string> &box){
        indexTable.sort();
        int last = -1;
        for(auto i=indexTable.begin();i!=indexTable.end();++i){
            while(i!=indexTable.end()&&last==*i)++i;//去重
            box.push_back(mymap[*i]);
            last=*i;
        }
    }
};

int main()
{
    cout<<"wo yi yue du guan yu chao xi de shuo ming"<<endl;
    string str;

    int n;
    
    cin>>n;
    HashMap h(n<<2);
    map<string,string> strmap;
    for(int i=0;i<n;i++){
        cin>>str;
        h.insert(str);
    }
    list<string> ans;
    h.printAll(ans);
    ans.sort();
    cout<<ans.size()<<endl;
    
    for(auto a=ans.begin();a!=ans.end();++a){
        cout<<*a<<endl;
    }

    return 0;
}
/*
15
a ew vc tea we eat zoo el le ozo ooz cv a kka akk
10
aa bb cc aa liu uil uli j as k
*/