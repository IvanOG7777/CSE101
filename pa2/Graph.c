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

// getPath()
// If vertex u is reachable from the source, appends the vertices of a shortest
// source-u path to List L. Otherwise, appends NIL to L.
// Pre: 1 <= u <= getOrder(G), getSource(G) != NIL
void getPath(List L, Graph G, int u) {
    if (L == NULL) {
        fprintf(stderr, "Graph Error: getPath(): NULL List Reference\n");
        exit(EXIT_FAILURE);
    }

    if (G == NULL) {
        fprintf(stderr, "Graph Error: getPath(): NULL Graph Reference\n");
        exit(EXIT_FAILURE);
    }

    if (u <= 0) {
        fprintf(stderr, "Graph Error: getPath(): Invalid index (Too low)\n");
        exit(EXIT_FAILURE);
    }

    if (u > getOrder(G)) {
        fprintf(stderr, "Graph Error: getPath(): Invalid index (Too High)\n");
        exit(EXIT_FAILURE);
    }

    if (u == getSource(G)) {
        append(L, u);
        return;
    }
    if (getParent(G, u) == NIL) {
        return;
    }
        getPath(L, G, getParent(G, u));
        append(L, u);
}

// makeNull()
// Resets G to its initial state.
void makeNull(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: makeNull(): NULL Graph reference \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= getOrder(G); i++) {
        freeList(&G->adj[i]);
    }

    G->numEdges = 0;
    G->numArcs = 0;
    G->source = NIL;

    for (int i = 1; i <= getOrder(G); i++) {
        G->adj[i] = newList();
        G->color[i] = 0;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }
}

void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: addEdge(): NULL Graph reference \n");
        exit(EXIT_FAILURE);
    }

    if (u <= 0 || v <= 0) {
        fprintf(stderr, "Graph Error: addEdge(): Invalid index U or V is too How \n");
        exit(EXIT_FAILURE);
    }

    if (u > getOrder(G) || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: addEdge(): Invalid index U or V is too High \n");
        exit(EXIT_FAILURE);
    }

    append(G->adj[u], v);
    append(G->adj[v], u);
    G->numEdges++;
}

void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: addArc(): NULL Graph reference \n");
        exit(EXIT_FAILURE);
    }

    if (u <= 0 || v <= 0) {
        fprintf(stderr, "Graph Error: addArc(): Invalid index U or V is too How \n");
        exit(EXIT_FAILURE);
    }

    if (u > getOrder(G) || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: addArc(): Invalid index U or V is too High \n");
        exit(EXIT_FAILURE);
    }
    append(G->adj[u], v);
    G->numArcs++;
}

// BFS()
// Runs the Breadth First Search algorithm on G with source vertex s.
void BFS(Graph G, int s) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: BFS(): NULL Graph reference \n");
        exit(EXIT_FAILURE);
    }



}