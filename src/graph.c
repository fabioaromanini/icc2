#include <graph.h>

graph_t *graph_init(int n_vtx) {
	graph_t *g = (graph_t *) malloc(sizeof(graph_t));

	g->vtx = (vertex *) malloc(sizeof(vertex) * (n_vtx + 1));

	g->edg = (int **)  malloc(sizeof(int *) * (n_vtx + 1));
	for(int i = 1; i <= n_vtx; i++)
		g->edg[i] = (int *) calloc(n_vtx + 1, sizeof(int));


	g->n_vtx = n_vtx;
	return g;
}

void graph_destroy(graph_t *g) {
	for(int i = 1; i <= g->n_vtx; i++)
		free(g->edg[i]);

	free(g->edg);
	free(g->vtx);
	free(g);
}