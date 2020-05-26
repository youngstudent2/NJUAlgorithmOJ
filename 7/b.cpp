#include<iostream>
#include<queue>
#include<vector>
//#define DEBUG_MODE
#define INF 0xFFFFFFF
using namespace std;
inline int max(int a, int b) {
    return a > b ? a : b;
}
/*
template<class T>
class MinHeap {
public:
    MinHeap(int size);
    MinHeap(T arr[], int n);
    bool insert(T ele);
    bool pop();
    bool isFull();
    bool isEmpty();
    void print();
    int Size();
    T top();
protected:
    T* heap;
    int currentSize;
    int maxHeapSize;
    void siftDown(int start, int end);
    void siftUp(int start);
    inline int LEFT(int index) {
        return 2 * index + 1;
    }
    inline int RIGHT(int index) {
        return 2 * index + 2;
    }
    inline int PARENT(int index) {
        return (index - 2) / 2;
    }
    void fix(int p) {
        int l = LEFT(p);
        int r = RIGHT(p);
        int next = p;
        if (l<currentSize && heap[l]>heap[p])
            next = l;
        if (r<currentSize && heap[r]>heap[next])
            next = r;
        if (next != p) {
            swap(heap[p], heap[next]);
            fix(next);
        }

    }
};

template<class T>
MinHeap<T>::MinHeap(int size) {
    maxHeapSize = size;
    heap = new T[size];
    currentSize = 0;
    maxHeapSize = size;
}

template<class T>
MinHeap<T>::MinHeap(T arr[], int n) {
    maxHeapSize = n;
    heap = new T[maxHeapSize];
    currentSize = n;
    for (int i = 0; i < n; i++) {
        heap[i] = arr[i];
    }
    int currentPos = (n - 2) / 2;
    while (currentPos >= 0) {
        siftDown(currentPos, currentSize - 1);
        currentPos--;
    }
}

template<class T>
bool MinHeap<T>::isFull() {
    return currentSize == maxHeapSize;
}

template<class T>
bool MinHeap<T>::isEmpty() {
    return currentSize == 0;
}

template<class T>
void MinHeap<T>::siftDown(int start, int end) {
    T tmp = heap[start];
    int i = start;
    int j = i * 2 + 1;
    while (j <= end) {
        if (j<end && heap[j]>heap[j + 1])j++;
        if (tmp > heap[j]) {
            heap[i] = heap[j];
            i = j;
            j = i * 2 + 1;
        }
        else {
            break;
        }
    }
    heap[i] = tmp;
}

template<class T>
void MinHeap<T>::siftUp(int start) {
    T tmp = heap[start];
    int j = start, i = (j - 1) / 2;
    while (j > 0) {
        if (heap[i] > tmp) {
            heap[j] = heap[i];
            j = i;
            i = (j - 1) / 2;
        }
        else {
            break;
        }
    }
    heap[j] = tmp;
}

template<class T>
bool MinHeap<T>::pop() {
    if (this->isEmpty())return false;
    heap[0] = heap[currentSize - 1];
    siftDown(0, --currentSize - 1);
    return true;
}

template<class T>
bool MinHeap<T>::insert(T ele) {
    if (this->isFull())return false;
    heap[currentSize] = ele;
    siftUp(currentSize++);
    return true;
}

template<class T>
void MinHeap<T>::print() {
    for (int i = 0; i < currentSize; i++) {
        cout << heap[i] << ' ';
    }
    cout << endl;
}

template<class T>
int MinHeap<T>::Size() {
    return currentSize;
}

template<class T>
T MinHeap<T>::top() {
    return heap[0];
}

template<class T>
class Priority_Queue :public MinHeap<T> {
public:
    Priority_Queue(int size) :MinHeap<T>(size) {}
    T extract_min() {
        if (this->empty()) {
            throw exception("queue is empty");
        }
        T tmp = this->heap[0];
        this->heap[0] = this->heap[this->currentSize];
        this->currentSize--;
        this->fix(0);
        return tmp;
    }
    bool decreaseKey(int i, T key) {
        if (key < this->heap[i])
            return false;
        this->heap[i] = key;
        int p = this->PARENT(i);
        while (i > 0 && this->heap[i] > this->heap[p]) {
            swap(this->heap[i], this->heap[p]);
            i = p;
            p = this->PARENT(p);
        }
    }
    bool push(T ele) {
        return this->insert(ele);
    }

};
*/
struct Edge
{
    int to;
    int length;
    Edge(int to, int length) :to(to), length(length) {}

    friend bool operator<(const Edge e1, const Edge e2);
};

bool operator<(const Edge e1, const Edge e2) {
    return e1.length > e2.length;
}


struct Node
{
    bool vis;
    int dis;
    vector<Edge> edges;
    Node() {
        vis = 0;
        dis = 0;
    }
    void addEdge(int to, int length) {
        edges.push_back(Edge(to, length));
    }
};

void init(Node* nodes) {
    int a, b, w;
    while (scanf("%d%d%d", &w, &a, &b) == 3) {
        nodes[a].addEdge(b, w);
        nodes[b].addEdge(a, w);
    }
}
#ifdef DEBUG_MODE
void output_queue(priority_queue<Edge>& q) {
    cout << "queue:" << endl;
    vector<Edge> container;
    while (!q.empty()) {
        container.push_back(q.top());
        q.pop();
    }
    for (auto& e : container) {
        cout << e.to << ' ' << e.length << endl;
        q.push(e);
    }
}
#else
inline void output_queue(priority_queue<Edge>& q) {
    //empty;
}
#endif
void update_fringe(Node* nodes, int v, priority_queue<Edge>& q) {
    for (auto e = nodes[v].edges.begin(); e != nodes[v].edges.end(); ++e) {
        auto w = e->to;
        int newPriority = max(nodes[v].dis, e->length);
        if (!nodes[w].vis) {
            nodes[w].vis = 1;
            nodes[w].dis = newPriority;
            q.push(Edge(w,newPriority));
        }
        else {
            if (newPriority < nodes[w].dis) {
                //q.decreaseKey(w,newPriority);
                nodes[w].dis = newPriority;
                q.push(Edge(w, newPriority));
            }
        }
    }
}

void dijkstra(Node* nodes, int s, int t) {
    priority_queue<Edge> q;
    nodes[s].dis = 0;
    for (auto e = nodes[s].edges.begin(); e != nodes[s].edges.end(); ++e) {
        q.push(*e);
        nodes[e->to].dis = e->length;
    }
    output_queue(q);
    while (!q.empty()) {
        auto x = q.top();
        q.pop();
        update_fringe(nodes, x.to, q);
        output_queue(q);
    }
}

int main()
{
    int n, s, t;
    scanf("%d%d%d", &n, &s, &t);

    Node* nodes = new Node[n];
    init(nodes);

    cout << "I have read the rules about plagiarism punishment" << endl;

    dijkstra(nodes, s, t);

    cout << nodes[t].dis;


    //system("pause");


    return 0;
}
/*
7 0 5
5 0 1
1 1 2
2 2 3
2 0 4
2 1 4
2 2 5
4 3 5
1 4 5
1 0 6
1 6 5

*/