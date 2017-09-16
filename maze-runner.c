#include <stdlib.h>
#include <stdio.h>

#include <bool.h>
#include <graph.h>
#include <stack.h>


// in this program, we'll use a graph to represent
// a labyrinth, and, given a starting point, search
// trough the rooms in the labyrinth, printing all 
// the possible paths and it's distance from the starting point.
// in the proccess we may find a treasure room, wich gives us
// a certain amount of points, and unlock/block passages.
// if it happens, we'll then backtrack trough the labyrinth, 
// searching for new ways out,now that we unlocked new rooms.

// the problem as described in the pdf, does not consider every 
// point in the labyrinth to be a room. but, in order to make 
// the data structures simpler, i'm representing both the
// points and the rooms as vertexes in the graph l.
// the edges will represent the passages that links
// two or more points. a existing passage between to points
// may be blocked, in this case, we'll use the weight of the
// graph's edges to represent the 


// FUNCTIONS

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
	
	// inputs:
	int n_points;
	scanf("%d ", &n_points);

	graph_t *l = graph_init(n_points);
	
	// the input will index the rooms from 1 
	// up to the number of rooms
	for(int i = 1; i <= n_points; i++) {
		float x, y;
		scanf("%f %f ", &x, &y);

		l->vtx[i].x = x;
		l->vtx[i].y = y;

		l->vtx[i].is_exit = false;
		l->vtx[i].is_treasure = false;
	}

	int n_rooms;
	scanf("%d ", &n_rooms);
	for(int i = 0; i < n_rooms; i++) {
		int idx;
		bool is_exit;

		scanf("%d %d ", &idx, (int *) &is_exit);

		if(idx > 0 && idx <= n_rooms)
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
	scanf("%d ", &start);

	int treasure_room = -1;
	int treasure_points = 0;
	int n_alterations = 0;

	// if the file ended, there is no treasure room.
	// this means that there will be no treasure points
	// and no alterations will happen in the labyrinth.
	if(!feof(stdin)) {
		treasure_room = start;
		scanf("%d ", &treasure_points);
		scanf("%d ", &n_alterations);

		for(int i = 0; i < n_alterations; i++) {
			int from, to;
			scanf("%d %d ", &from, &to);

			if(from != to)
				link_rooms(l, from, to);
		}
		
		scanf("%d ", &start);
	}

	stack_t *next_rooms = stack_init(n_points);

	// outputs:
	// printf("%d %d\n", treasure_room, treasure_points);

	// LOG
	// printf("n_points: %d\n", n_points);
	// printf("n_rooms: %d\n", n_rooms);
	// for(int i = 1; i <= n_points; i++) {
	// 	printf("Vertex[%d]:\n", i);
	// 	printf("\tx: %f\n", l->vtx[i].x);
	// 	printf("\ty: %f\n", l->vtx[i].y);

	// 	if(l->vtx[i].is_exit)
	// 		printf("This is a exit chamber\n");
	// 	if(l->vtx[i].is_treasure)
	// 		printf("This is a treasure chamber\n");
	// 	printf("\n");
	// 	printf("\n");
	// }

	// printf("start: %d\n", start);
	// if(treasure_room) {
	// 	printf("treasure_room: %d treasure_points: %d\n", treasure_room, treasure_points);
	// } else {
	// 	printf("no treasure_room\n");
	// }

	// printf("links:\n\n");
	// for(int i = 1; i <= n_points; i++)
	// 	for(int j = 1; j <= n_points; j++)
	// 		if(l->edg[i][j]) printf("%d links to %d\n", i, j);

	// printf("stack test:\n\n");
	// for(int i = 0; i < n_points; i++) {
	// 	push(next_rooms, i);
	// }
	// printf("stack size: %d\n", next_rooms->size);
	// printf("stack max_size: %d\n\n", next_rooms->max_size);

	// while(is_not_empty(next_rooms)) {
	// 	printf("%d\n", pop(next_rooms));
	// 	printf("stack size: %d\n", next_rooms->size);
	// 	printf("stack max_size: %d\n\n", next_rooms->max_size);
	// }

	// printf("stack size: %d\n", next_rooms->size);
	// printf("stack max_size: %d\n\n", next_rooms->max_size);		

	graph_destroy(l);
	stack_destroy(next_rooms);
	return 0;
}