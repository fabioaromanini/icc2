#include <graph.h>

graph_t *graph_init(int n_vtx) {
	graph_t *g = (graph_t *) malloc(sizeof(graph_t));

	g->vtx = (vertex *) malloc(sizeof(vertex) * (n_vtx + 1));

	g->edg = (float **)  malloc(sizeof(float *) * (n_vtx + 1));
	for(int i = 1; i <= n_vtx; i++)
		g->edg[i] = (float *) calloc(n_vtx + 1, sizeof(float));

	g->n_vtx = n_vtx;
	return g;
}


float get_distance(graph_t *l, int node1, int node2) {
	return sqrt(pow(l->vtx[node1].x - l->vtx[node2].x, 2) +
				pow(l->vtx[node1].y - l->vtx[node2].y, 2));
}

void graph_destroy(graph_t *g) {
	for(int i = 1; i <= g->n_vtx; i++)
		free(g->edg[i]);

	free(g->edg);
	free(g->vtx);
	free(g);
}