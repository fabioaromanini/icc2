#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdlib.h>
#include <bool.h>

// graph implementation using
// a adjacency matrix

// the edges are weighted, so we'll
// represent them with a int
typedef int edge;

typedef struct {
	float x;
	float y;

	bool is_exit;
	bool is_treasure;
} vertex;

typedef struct {
	int n_vtx;
	// contains all the info of a given vertex
	vertex *vtx;
	// maps the weight of a edge
	edge **edg;
} graph_t;

graph_t *graph_init(int n_vertexes);
void graph_destroy(graph_t *g);

#endif