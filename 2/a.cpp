#include<iostream>
#include<map>
#include<string>
#include<list>
#include<queue>
using namespace std;

template<class A>
inline A insertSort(A s) {
	for (auto i = s.begin() + 1; i < s.end(); ++i) {
		auto tmp = *i;
		string::reverse_iterator j(i);
		for (; j != s.rend() && *j > tmp; ++j) {
			*(j - 1) = *j;
		}
		*(j - 1) = tmp;
	}
	return s;
}

string generate_sign(const string & str) {
	return insertSort<string>(str);
}

typedef map<string, string>::iterator It;
class cmp {
public:
	bool operator()(const It& i1, const It& i2)const {
		return i1->second < i2->second;
	}
};
struct String {
	string str;
	int count;
	String():count(0){}
	String(string s):count(1),str(s){}
};

int main()
{
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	string str;

	int n;
	cin >> n;
	map<string, String> strmap;

	for (int i = 0; i < n; i++) {
		cin >> str;
		string s = generate_sign(str);
		//cout<<str<<'-'<<s<<endl;
		auto it = strmap.find(s);
		if (it != strmap.end()) { //变位词已存在
			it->second.count++;
			if (it->second.str > str) //更新字典序更小的变位词
				it->second.str = str;

		}
		else { //未存在变位词,装入容器中
			strmap[s] = str;
		}
	}
	list<string> l;
	for (auto it = strmap.begin(); it != strmap.end(); ++it) {
		if (it->second.count >= 2) {
			l.push_back(it->second.str);
		}
	}
	l.sort();
	cout << l.size() << endl;
	for (auto it = l.begin(); it != l.end(); ++it) {
		cout << *it << endl;
	}
	//system("pause");
	return 0;
}
/*
20
a ew vc tea we ew we ew we eat zoo hjjh hjhj jhjh ozo ooz cv a kka akk
*/