#include <stdio.h>
#include "Graph.h"

int main(void) {
    Graph G = newGraph(10);
    printf("Vertices in graph are: %d\n", getOrder(G));

    printf("Number of Nodes passed is: %d\n", getOrder(G));
    printf("Number of edges is: %d\n", getNumEdges(G));
    printf("Number of arcs is: %d\n", getNumArcs(G));
    printf("Current source is: %d\n", getSource(G));
    printf("Current parent id: %d\n", getParent(G, 2));
    printf("Current parent id: %d\n", getDist(G, 2));
    printf("\n\n");

    addEdge(G, 1, 2);
    printf("\n");
    addEdge(G, 1, 3);
    printf("\n");
    addEdge(G, 1, 4);

    freeGraph(&G);
    return 0;
}