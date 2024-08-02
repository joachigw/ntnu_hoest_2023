#include <stdio.h>
#include <stdlib.h>
#include "weightedgraph.h"
#include "queue.h"

#define INFINITE 1000000
#define MIN(a, b) (a < b ? a : b)

Graph* new_graph(FILE* f) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    fscanf(f, "%i %i\n", &graph->N, &graph->K);
    graph->node = (Node*)calloc(graph->N, sizeof(Node));

    for (int i = 0; i < graph->K; ++i) {
        int from, to;
        Edge* edge = (Edge*)malloc(sizeof(Edge));
        fscanf(f, "%i %i %i\n", &from, &to, &edge->capacity);
        edge->to = &graph->node[to];
        edge->next = (Edge*)graph->node[from].edge1;
        graph->node[from].edge1 = edge;

        // Create the reverse edge if not found
        Edge* reverse_edge = graph->node[to].edge1;
        Edge* found_reverse_edge = NULL;
        while (reverse_edge) {
            if (reverse_edge->to == &graph->node[from]) {
                found_reverse_edge = reverse_edge;
                break;
            }
            reverse_edge = reverse_edge->next;
        }

        if (found_reverse_edge == NULL) {
            // Create a new reverse edge
            Edge* new_reverse_edge = (Edge*)malloc(sizeof(Edge));
            new_reverse_edge->to = &graph->node[from];
            new_reverse_edge->capacity = 0;  // Set initial capacity to 0
            new_reverse_edge->next = (Edge*)graph->node[to].edge1;
            graph->node[to].edge1 = new_reverse_edge;

            edge->reverse = new_reverse_edge;
            new_reverse_edge->reverse = edge;
        } else {
            // Use the found reverse edge
            edge->reverse = found_reverse_edge;
            found_reverse_edge->reverse = edge;
        }
    }

    return graph;
}



Pred* new_pred() {
    Pred* p = calloc(1, sizeof(Pred));
    p->dist = INFINITE;
    return p;
}

void init_pred(Graph* graph, Node* s) {
    for (int i = graph->N; i--;) {
        graph->node[i].d = new_pred();
        graph->node[i].node_id = i;
    }
    ((Pred*) s->d)->dist = 0;
}


void bfss(Graph* graph, Node* source) {
    init_pred(graph, source);
    Queue* queue = new_queue(graph->N-1);
    add_to_queue(queue, source);
    while (!empty_queue_check(queue)) {
        Node* n = next_in_queue(queue);
        for (Edge* edge = n->edge1; edge; edge = edge->next) {
            Pred* p = edge->to->d;
            if (p->dist == INFINITE && edge->capacity > 0) {
                p->dist = ((Pred*) n->d)->dist + 1;
                p->pred = n;
                add_to_queue(queue, edge->to);
            }
        }
    }
}

int max_flow_edmond_karp(Graph* graph, Node* source, Node* sink) {
    int flow = 0;
    Pred* path_pred;

    while (1) {
        bfs(graph, source);

        path_pred = sink->d;
        if (path_pred->dist == INFINITE) break;
        int bottleneck_capacity = INFINITE;

        Node* current = sink;
        while (current != source) {
            Pred* pred = current->d;
            Edge* edge = pred->pred->edge1;
            while (edge) {
                if (edge->to == current) {
                    bottleneck_capacity = MIN(bottleneck_capacity, edge->capacity);
                    break;
                }
                edge = edge->next;
            }
            current = pred->pred;
        }

        if (bottleneck_capacity == 0) break;

        printf("   %d   :   %d", bottleneck_capacity, source->node_id);

        current = sink;
        int path[graph->N];
        int path_length = 0;

        while (current != source) {
            Pred* pred = current->d;
            path[path_length++] = current->node_id;
            current = pred->pred;
        }

        for (int i = path_length - 1; i >= 0; i--) {
            printf(" %d", path[i]);
        }
        printf("\n");

        current = sink;
        while (current != source) {
            Pred* pred = (Pred*) current->d;
            Edge* edge = pred->pred->edge1;
            while (edge) {
                if (edge->to == current) {
                    edge->capacity -= bottleneck_capacity;
                    edge->reverse->capacity += bottleneck_capacity;  // Update reverse edge capacity
                    edge->flow += bottleneck_capacity;  // Update forward edge's flow
                    break;
                }
                edge = edge->next;
            }

            edge = (Edge*) malloc(sizeof(Edge));
            edge->to = pred->pred;
            edge->capacity = bottleneck_capacity;
            edge->next = (Edge*) current->edge1;
            current->edge1 = edge;
            current = pred->pred;
        }

        flow += bottleneck_capacity;
    }
    return flow;
}


int maain() {
    FILE* file = fopen("flytgraf1.txt", "r");
    Graph* graph = new_graph(file);
    fclose(file);

    Node* source = &graph->node[0];
    Node* sink = &graph->node[7];

    printf("\nIncrease : Flow-increasing path\n");

    int max_flow = max_flow_edmond_karp(graph, source, sink);
    printf("\nMax flow from source node %d to sink node %d with Edmond-Karp: %d   \n", source->node_id, sink->node_id, max_flow);

    return 0;
}