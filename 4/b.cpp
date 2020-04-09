#include<iostream>
#include<vector>
using namespace std;

enum Color {White,Black,Grey};

struct Node{
    Color color;
    vector<Node*> neighbors;
    int eft,est;
    int w;
    Node* next;
    int index;
    Node(){
        color = White;
        eft = est = 0;
        next = NULL;
        //this->w = w;
    }
    void rely(Node *node){
        neighbors.push_back(node);
    }
    void print(){
        int next_index = -1;
        if(next)next_index = next->index;
        printf("node%d est:%d eft:%d w:%d next:%d\n",index,est,eft,w,next_index);
    }
};

inline int max(int a,int b){
    return a>b?a:b;
}

void critical_path(Node* node){
    node->color = Grey;
    for(auto n = node->neighbors.begin();n!=node->neighbors.end();++n){
        if((*n)->color == White){
            critical_path(*n);            
        }
        if((*n)->eft>node->est){
            node->est = (*n)->eft;
            node->next = *n;
        }
        //node->est = max(node->est,(*n)->eft);
    }
    node->eft = node->est + node->w;
    node->color = Black;
}

int main()
{
    int n;
    cin>>n;
    Node* nodes = new Node[n+1];
    int index,w;
    for(int i=1;i<=n;++i){
        scanf("%d%d",&index,&w);
        nodes[i].w = w;
        nodes[i].index = index;
    }  
    int index1,index2;
    while(cin>>index1>>index2){
        nodes[index1].rely(&nodes[index2]);
    }
    for(int i=1;i<=n;++i){
        if(nodes[i].color == White){
            critical_path(&nodes[i]);
        }
    }
    
    int ans = 0;
    for(int i=1;i<=n;++i){
        ans = max(ans,nodes[i].eft);
        //nodes[i].print();
    }

    
    printf("I have read the rules about plagiarism punishment\n");
    printf("%d",ans);
    return 0;
}
/*
9
1 10
2 6
3 5
4 1
5 2
6 3
7 4
8 9
9 1
1 9
2 1
2 8
3 5
3 6
3 7
4 2
4 3
5 9
6 9
7 9
8 9
a
*/