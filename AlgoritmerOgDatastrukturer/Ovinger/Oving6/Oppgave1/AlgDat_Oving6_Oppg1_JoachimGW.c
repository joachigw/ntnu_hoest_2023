#include <stdio.h>
#include <stdlib.h>
#include "adjacencylist.h"
#include "queue.h"

#define INFINITE 1000000000

/**
 * Read the file and interpret its graph.
 * @param f the file to read.
 * @return the read graph.
 */
Graph* read_graph_from_file(FILE* f) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    fscanf(f, "%i %i\n", &graph->N, &graph->K);
    graph->node = (Node*) calloc(graph->N, sizeof(Node));
    for (int i = 0; i < graph->K; ++i) {
        int from, to;
        Edge* edge = (Edge*) malloc(sizeof(Edge));
        fscanf(f, "%i %i\n", &from, &to);
        edge->to = &graph->node[to];
        edge->next = graph->node[from].edge1;
        graph->node[from].edge1 = edge;
    }
    return graph;
}

/**
 * Allocates a Pred (predecessor) struct.
 * @return the Pred struct.
 */
Pred* new_pred() {
    Pred* p = calloc(1, sizeof(Pred));
    p->dist = INFINITE;
    return p;
}

/**
 * Initializes all the nodes's Pred struct in the given graph.
 * @param graph the graph.
 * @param s the start node.
 */
void init_pred(Graph* graph, Node* s) {
    for (int i = graph->N; i--;) {
        graph->node[i].d = new_pred();
    }
    ((Pred*) s->d)->dist = 0;
}

/**
 * Breadth-first-search on the given graph.
 * @param graph the graph to search.
 * @param s the node to start the search from.
 */
void bfs(Graph* graph, Node* s) {
    init_pred(graph, s);
    Queue* queue = new_queue(graph->N-1);
    add_to_queue(queue, s);
    while (!empty_queue_check(queue)) {
        Node* n = next_in_queue(queue);
        for (Edge* edge = n->edge1; edge; edge = edge->next) {
            Pred* p = edge->to->d;
            if (p->dist == INFINITE) {
                p->dist = ((Pred*) n->d)->dist + 1;
                p->pred = n;
                add_to_queue(queue, edge->to);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Open the file containing the graph
    FILE* graph_file = fopen("ø6g5.txt", "r");
    if (graph_file == NULL) {
        printf("The file could not be opened!\n");
        return 1;
    }
    Graph* graph = read_graph_from_file(graph_file);


    int starting_node = 0;
    // Check for command line arguments when the program is run from the terminal
    if (argc > 1) {
        if (sscanf(argv[1], "%d", &starting_node) != 1 || starting_node < 0) {
            printf("Invalid input for starting node. Please enter a valid non-zero integer.\n");
            return 1;
        }
    }

    // Set the starting node for the BFS search
    if (starting_node >= graph->N) {
        printf("The graph does not have a node %d!\nPlease try again.\n", starting_node);
        exit(1);
    }
    Node* start_node = &graph->node[starting_node];

    // Run the BFS search
    bfs(graph, start_node);

    // Print the results of the BFS search
    // A node's predecessor value 'pred' is set to -1 if it is either unreachable or the starting node itself
    printf("BFS SEARCH, START NODE: %d\n--------------------------\n", starting_node);
    printf("Node  Forgj  Dist\n");
    for (int i = 0; i < graph->N; ++i) {
        Pred* p = (Pred*) graph->node[i].d;
        int pred = p->pred ? (int)((Node*)p->pred - graph->node) : -1;
        printf("%d     %d      %d\n", i, pred, p->dist);
    }

    // Close the graph file
    fclose(graph_file);

    return 0;
}
