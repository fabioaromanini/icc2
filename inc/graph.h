#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdlib.h>
#include <math.h>

#include <bool.h>

// graph implementation using
// a adjacency matrix


// the problem as specified in the pdf, does not consider every 
// point in the labyrinth to be a room. but, in order to make 
// the data structures simpler, i'm representing both the
// points and the rooms as vertexes in the graph l.
// the edges will represent the passages that links
// two or more points. a existing passage between to points
// may be blocked, in this case, we'll use the weight of the
// graph's edges to represent wheter the passage is available
// or not.

// the edges are weighted, so we'll
// represent them with a float
typedef float edge;

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
	// maps the edges and their respective weight
	edge **edg;
} graph_t;

graph_t *graph_init(int n_vertexes);
float get_distance(graph_t *l, int node1, int node2);
void graph_destroy(graph_t *g);

#endif