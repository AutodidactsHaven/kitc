#ifndef KITC_MAT_GRAPH_H
#define KITC_MAT_GRAPH_H
#include <stdint.h>
#include <stdbool.h>

typedef struct edge {
  int v;
  int w;
} edge;

typedef struct graph {
  int V;
  int E;
  uint8_t* adj;
} mat_graph;


/*
 * initialises a graph backed by adjacency matrix.
 * all memory is allocated for the max. # of vertices upfront for simplicity
 * @param n_vertices maximum number of vertices the graph can hold
 */
void kitc_mat_graph_init(mat_graph* graph, int n_vertices);

/*
 * insert an edge between two vertices into the graph
 */
bool kitc_mat_graph_ins_edge(mat_graph* graph, edge edge);

#endif
