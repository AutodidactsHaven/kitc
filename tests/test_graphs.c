#include <stdio.h>
#include "../src/graphs/mat_graph.h"

int main() {
  mat_graph g;
  kitc_mat_graph_init(&g, 10);

  edge e0 = { .v = 0, .w = 1 };
  kitc_mat_graph_ins_edge(&g, e0);

  printf("Num edges: %d\n", g.E);

  return 0;
}
