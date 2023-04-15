#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "mat_graph.h"

void kitc_mat_graph_init(mat_graph *g, int max_vertices) {
  g->V = max_vertices;
  g->E = 0;
  size_t num_bytes = max_vertices * max_vertices * sizeof(uint8_t);
  g->adj = malloc(num_bytes);
  memset(g->adj, 0, num_bytes);
}

/*
*  a-a a-b a-c b-a b-b b-c ...
* [ 0   1   0   1   0   1   ]
*/

bool kitc_mat_graph_ins_edge(mat_graph *g, edge e) {
  int v = e.v, w = e.w;
  if (g->adj[(v * g->V) + w] == 1) {
    // if this edge already exists returns insert failed
    // TODO(josh): put reason in errno ?
    return false;
  }
  g->adj[(v * g->V) + w] = 1;
  g->adj[(w * g->V) + v] = 1;
  g->E++;
  return true;
}
