#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"
#include "Graph.h"


typedef  struct GraphObj {
    int order; // How many vertices (nodes) exits
    List *adj; // Array of nodes per each node that has connections
    int *color; // Used for the BFS visit state
    int *parent; // predecessor in the BFS tree
    int *dist; // Array of shortest distances
    int source; // Source node of current/most recent BFS start vertex
    int numEdges; // Count the edges in undirected Graph
    int numArcs; //Count the edges in directed Graph
} GraphObj;

Graph newGraph(int n) {
    Graph nGraph = malloc(sizeof(GraphObj));

    assert(nGraph != NULL);

    nGraph->order = n;
    nGraph->adj = calloc(n + 1, sizeof(List)); // Allocating enough memory for n + 1 Lists
    // Allocating enough memory for n + 1 amount of ints
    nGraph->color = calloc(n + 1, sizeof(int));
    nGraph->parent = calloc(n + 1, sizeof(int));
    nGraph->dist = calloc(n + 1, sizeof(int));
    nGraph->source = NIL;// sets source to NIL(-1)
    //No edges or arcs on init
    nGraph->numEdges = 0;
    nGraph->numArcs = 0;

    // Setting values to allocated arrays
    for (int i = 1; i <= n; i++) {
        nGraph->adj[i] = newList();
        nGraph->color[i] = 0;
        nGraph->parent[i] = NIL;
        nGraph->dist[i] = INF;
    }

    printf("New Graph has been created\n");
    return nGraph;
}

void freeGraph(Graph* pG) {
    if (pG == NULL || *pG == NULL) {
        fprintf(stderr, "Graph Error: freeGraph(): NULL Graph OR *Graph reference\n");
        exit(EXIT_FAILURE);
    }

    // Freeing the Lists in *adj
    for (int i = 1; i <= getOrder(*pG); i++) {
        freeList(&(*pG)->adj[i]);
        printf("\n");
    }

    //Freeing pointers
    free((*pG)->adj);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->dist);

    if (pG != NULL && *pG != NULL) {
        free(*pG);
        *pG = NULL;
    }

    printf("Graph has been freed\n");
}

int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: getOrder(): NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    return G->order;
}

int getNumEdges(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: getNumEdges(): NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    return G->numEdges;
}

int getNumArcs(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: getNumEdges(): NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    return G->numArcs;
}

int getSource(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: getSource(): NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

// getParent
// Returns the parent of vertex u in the most recently constructed BFS tree
// or returns NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: getParent(): NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (u <= 0) {
        fprintf(stderr, "Graph Error: getParent(): Invalid index (Too low)\n");
        exit(EXIT_FAILURE);
    }

    if (u > getOrder(G)) {
        fprintf(stderr, "Graph Error: getParent(): Invalid index (Too High)\n");
        exit(EXIT_FAILURE);
    }

    return G->parent[u];
}

// getDist()
// Returns the distance from the source vertex to u if BFS() has been called,
// otherwise returns INF.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: getParent(): NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    if (u <= 0) {
        fprintf(stderr, "Graph Error: getDist(): Invalid index (Too low)\n");
        exit(EXIT_FAILURE);
    }

    if (u > getOrder(G)) {
        fprintf(stderr, "Graph Error: getDist(): Invalid index (Too High)\n");
        exit(EXIT_FAILURE);
    }

    return G->dist[u];
}

