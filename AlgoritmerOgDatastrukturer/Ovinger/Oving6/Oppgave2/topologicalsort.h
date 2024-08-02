#include <stdlib.h>

/**
 * Struct defining an edge.
 */
typedef struct edge_st {
    struct edge_st* next;
    struct node_st* to;
} Edge;

/**
 * Struct defining a node.
 */
typedef struct node_st {
    Edge* edge1;
    void* d;
} Node;

/**
 * Struct defining a graph (of nodes and edges).
 */
typedef struct graph_st {
    int N;
    int K;
    Node* node;
} Graph;

/**
 * Struct defining a topological list.
 */
typedef struct {
    int found;
    Node* next;
} TopoList;

/**
 * Depth-first traversal made for the topological sort.
 * @param n the node to start the search from.
 * @param l the list containing the found nodes.
 * @return returns the current node.
 */
Node* df_topo(Node* n, Node* l) {
    TopoList* nd = n->d;
    if (nd->found) return l;
    nd->found = 1;
    for (Edge* e = n->edge1; e; e = e->next) {
        l = df_topo(e->to, l);
    }
    nd->next = l;
    return n;
}

/**
 * Topologically sorts the given graph.
 * @param G the graph to topologically sort.
 * @return the sorted graph as a node (array).
 */
Node* topologicalsort(Graph* graph) {
    Node* l = 0;
    for (int i = graph->N; i--;) {
        graph->node[i].d = calloc(sizeof(TopoList), 1);
    }
    for (int i = graph->N; i--;) {
        l = df_topo(&graph->node[i], l);
    }
    return l;
}