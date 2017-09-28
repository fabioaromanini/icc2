#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdlib.h>
#include <math.h>

#include <bool.h>

// graph implementation using
// a adjacency matrix

// the edges are weighted, so we'll
// represent them with a float
typedef float edge;

typedef struct {
	// float x;
	// float y;
} vertex;

typedef struct {
	int n_vtx;
	// contains all the info of a given vertex
	vertex *vtx;
	// maps the edges and their respective weight
	edge **edg;
} graph_t;

graph_t *graph_init(int n_vertexes);
void graph_destroy(graph_t *g);

#endif