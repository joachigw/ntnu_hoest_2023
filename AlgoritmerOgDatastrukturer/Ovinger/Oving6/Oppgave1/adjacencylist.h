typedef struct edge_st {
    struct edge_st* next;
    struct node_st* to;
} Edge;

typedef struct node_st {
    Edge* edge1;
    void* d;
} Node;

typedef struct graph_st {
    int N;
    int K;
    Node* node;
} Graph;

typedef struct {
    int dist;
    Node* pred;
} Pred;
