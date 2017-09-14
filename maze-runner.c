#include <stdlib.h>
#include <stdio.h>

#include <bool.h>
#include <graph.h>

// in this program, we'll use a graph to represent
// a labyrinth, and find all the possible ways out.
// the edges will represent the passages that links
// two or more vertexes, wich will represent the rooms

// function that links two rooms in the
// labyrinth, creating a edge in the graph.
// if one of the indexes is negative, the weight
// of the edge will be 0, wich indicates that the
// passage is blocked
void link_rooms(graph_t* l, int from, int to) {
	int is_active = from > 0 && to > 0;

	if(to < 0) to = to * -1;
	if(from < 0) from = from * -1;
	
	if(from && to && from <= l->n_vtx && to <= l->n_vtx) {
		l->edg[from][to] = is_active;
		l->edg[to][from] = is_active;
	}
}

int main(int argc, char const *argv[]) {
	int n_vtx;
	scanf("%d ", &n_vtx);

	graph_t *l = graph_init(n_vtx);
	
	// the user will index the rooms from 1 
	// up to the number of rooms in the labyrinht
	for(int i = 1; i <= n_vtx; i++) {
		float x, y;
		scanf("%f %f ", &x, &y);

		l->vtx[i].x = x;
		l->vtx[i].y = y;

		l->vtx[i].is_exit = FALSE;
		l->vtx[i].is_treasure = FALSE;
	}

	int n_rooms;
	scanf("%d ", &n_rooms);
	for(int i = 0; i < n_rooms; i++) {
		int idx;
		bool is_exit;

		scanf("%d %d ", &idx, (int *) &is_exit);

		if(idx > 0 && idx <= n_vtx)
			l->vtx[idx].is_exit = is_exit;
	}
	
	int n_passages;
	scanf("%d ", &n_passages);

	for(int i = 0; i < n_passages; i++) {
		int from, to;
		scanf("%d %d ", &from, &to);

		if(from != to)
			link_rooms(l, from, to);
	}

	int start;
	int treasure_room;
	int treausre_points;
	int n_alterations;
	scanf("%d ", &start);
	
	// if the file ended, there is no treasure room.
	// this means that there will be no treasure points
	// and no alterations will happen in the labyrinth.
	if(!feof(stdin)) {
		treasure_room = start;
		scanf("%d ", &treausre_points);
		scanf("%d ", &n_alterations);

		for(int i = 0; i < n_alterations; i++) {
			int from, to;
			scanf("%d %d ", &from, &to);

			if(from != to)
				link_rooms(l, from, to);
		}
		
		scanf("%d ", &start);
	}

	printf("n_vtx: %d\n", n_vtx);
	printf("n_rooms: %d\n", n_vtx);
	for(int i = 1; i <= n_vtx; i++) {
		printf("Vertex[%d]:\n", i);
		printf("\tx: %f\n", l->vtx[i].x);
		printf("\ty: %f\n", l->vtx[i].y);

		if(l->vtx[i].is_exit)
			printf("This is a exit chamber\n");
		if(l->vtx[i].is_treasure)
			printf("This is a treasure chamber\n");
		printf("\n");
		printf("\n");
	}

	printf("start: %d\n", start);
	if(treasure_room) {
		printf("treasure_room: %d treausre_points: %d\n", treasure_room, treausre_points);
	} else {
		printf("no treasure_room\n");
	}

	for(int i = 1; i <= n_vtx; i++)
		for(int j = 1; j <= n_vtx; j++)
			if(l->edg[i][j]) printf("%d links to %d\n", i, j);	

	graph_destroy(l);
	return 0;
}