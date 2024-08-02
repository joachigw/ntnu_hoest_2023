#include <stdio.h>
#include <stdlib.h>
#include "topologicalsort.h"

/**
 * Read the file and interpret the graph.
 * @param f 
 * @return
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

int main() {
    // Open and read the file containing the graph
    FILE* graph_file = fopen("ø6g5.txt", "r");
    if (graph_file == NULL) {
        printf("The file could not be opened!\n");
        return 1;
    }
    Graph* G = read_graph_from_file(graph_file);

    // Run the topological sort
    Node* sorted_list = topologicalsort(G);

    // Print the sorted list
    printf("TOPOLOGICAL SORT\n-----------------\n");
    while (sorted_list != NULL) {
        int node_index = sorted_list - G->node;
        printf("%d ", node_index);
        sorted_list = ((TopoList*) (sorted_list->d))->next;
    }
    printf("\n");

    // Close the opened file
    fclose(graph_file);

    return 0;
}