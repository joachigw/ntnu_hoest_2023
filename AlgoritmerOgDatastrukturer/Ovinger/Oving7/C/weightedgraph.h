typedef struct edge_st {
    struct edge_st* next;
    struct edge_st* reverse;
    struct node_st* to;
    int flow;
    int capacity;
} Edge;

typedef struct node_st {
    int node_id;
    Edge* edge1;
    void* d;
} Node;

typedef struct {
    int N, K;
    Node* node;
} Graph;

typedef struct {
    int dist;
    Node* pred;
} Pred;