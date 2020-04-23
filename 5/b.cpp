#include<iostream>
#include<vector>
using namespace std;
enum Color {White,Black,Grey};
struct Node{
    Color color;
    vector<Node*> neighbors;
    Node* next;
    int index;
    Node(){
        color = White;
        next = NULL;
    }
    
};

void link(Node* na,Node* nb){
    na->neighbors.push_back(nb);
    nb->neighbors.push_back(na);
}

int main()
{

    return 0;
}