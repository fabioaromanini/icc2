// in this program, we'll use a graph to represent
// a labyrinth, and, given a starting point, search
// trough the rooms in the labyrinth, printing all 
// the possible paths and it's distance from the starting point.
// in the proccess we may find a treasure room, wich gives us
// a certain amount of bonus, and unlock/block passages.
// if it happens, we'll then backtrack trough the labyrinth, 
// searching for new ways out,now that we unlocked new rooms.

#include <stdlib.h>
#include <stdio.h>

#include <bool.h>
#include <graph.h>
#include <stack.h>

// this enum is used to compose the answer to the problem: 
// each found path is stored as an array of integers conaining
// the number of points in the path, it's geodesical distance,
// the score, given by the equation score = bonus_points - distance,
// and finally, the indexes of the points in the path. as the 3 first
// properties have a fixed position, we'll use a enum to make the code
// easier to understand

enum {
	N_POINTS,
	DISTANCE,
	SCORE
};

// this define helps to label which room is the first we visited
// in the labyrinth, and wich were not explored yet in our 
// searching algorithm's executions

#define ROOT -1
#define NOT_VISITED 0
#define MAX_PATH_N 2000

// FUNCTIONS

// function that links two rooms in the
// labyrinth, creating a edge in the graph.
// this edge's weight will represent the distance between
// the two rooms. if one of the indexes is negative, the weight
// of the edge will be negative, wich indicates that there
// is a passage, but it's blocked
void link_rooms(graph_t* l, int from, int to) {
	float distance = 1;
	if(from < 0 || to < 0) distance = -1;

	// makes sure both the indexes will be >= 0
	to = (int) abs(to);
	from = (int) abs(from);
	
	// validates the indexes
	if(from && to && (from <= l->n_vtx && to <= l->n_vtx)) {
		distance = distance *  get_distance(l, from, to);
		l->edg[from][to] = distance;
		l->edg[to][from] = distance;
	}
}

int *new_path(graph_t *l, stack_t *path_stack, int exit, int score) {
	int path_size = path_stack->size + 1;
	int *path = (int *) malloc(sizeof(int) * (path_size + 3));

	// even tough DISTANCE and SCORE are in the beginning of the 
	// array, we'll calculate them in the loop that copy the path in
	// the stack to the array
	float distance = 0;
	path[N_POINTS] = path_size;
	
	// we manually put the starting point in the path in order
	// to simplify the distance part in the following loop
	path[3] = get_elmnt_at(path_stack, 0);
	int last_room = path[3];
	for(int i = 1; i < path_stack->size; i++) {
		int actual_room = get_elmnt_at(path_stack, i);
		path[i + 3] = actual_room;
		// // printf("last_room %d\n", last_room);
		// // printf("actual_room %d\n", actual_room);
		distance += (int) l->edg[last_room][actual_room];
		last_room = actual_room;
	}

	path[path_size + 2] = exit;
	distance += (int) l->edg[last_room][exit];


	path[DISTANCE] = distance;
	path[SCORE] = score - distance;


	return path;
}

void print_path(int *path) {
	printf("%d", path[N_POINTS]);

	for(int i = 0; i < path[0]; i++)
		printf(" %d",  path[3 + i]);

	printf(" %d", path[DISTANCE]);
	printf(" %d\n", path[SCORE]);
}

void toggle_alterations(graph_t *l, int **alterations, int n_alterations) {
	// printf("BEFORE ALTERATIONS!\n");
	// for(int i = 1; i <= l->n_vtx; i++) {
	// 	for(int j = 1; j <= l->n_vtx; j++) {
	// 		printf("%f ", l->edg[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");

	// for(int i = 0; i < n_alterations; i++) {
	// 	printf("%d - %d \n", alterations[i][0], alterations[i][1]);
	// }
	// printf("\n");

	for(int i = 0; i < n_alterations; i++) {
		int from = alterations[i][0];
		int to  = alterations[i][1];
		bool will_block = to < 0 || from < 0;
		
		from = (int) abs(from);
		to  = (int) abs(to);
		if(from == 0 || to == 0)
			continue;

		bool is_active = l->edg[from][to] > 0;

		if(is_active && will_block) {
			l->edg[from][to] *= -1;
			l->edg[to][from] *= -1;

			alterations[i][0] = (int) abs(from);
			alterations[i][1] = (int) abs(to);

		} else if(!is_active && !will_block) {
			if(l->edg[from][to] == 0) {
				l->edg[from][to] -= get_distance(l, from, to);
				l->edg[to][from] -= get_distance(l, from, to);
			}

			l->edg[from][to] *= -1;
			l->edg[to][from] *= -1;

			alterations[i][0] = (int) (abs(from) * -1);
			alterations[i][1] = (int) (abs(to) * -1);
		}

	}

	// printf("AFTER ALTERATIONS!\n");
	// for(int i = 1; i <= l->n_vtx; i++) {
	// 	for(int j = 1; j <= l->n_vtx; j++) {
	// 		printf("%f ", l->edg[i][j]);
	// 	}
	// 	printf("\n");
	// }
	
	// for(int i = 0; i < n_alterations; i++) {
	// 	printf("%d - %d \n", alterations[i][0], alterations[i][1]);
	// }
	// printf("\n");
}

int sort_score(const void *a, const void *b) {
	int *p1 = *(int **) a;
	int *p2 = *(int **) b;

	if(p2[SCORE] != p1[SCORE])
		return p2[SCORE] - p1[SCORE];
	
	if(p2[DISTANCE] != p1[DISTANCE])
		return p2[DISTANCE] - p1[DISTANCE];
	else {
		int i = 4;
		while(p1[i] != p2[i]) {
			i++;
		}
		return p2[i] - p1[i];
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
		int is_exit;

		scanf("%d %d ", &idx, &is_exit);

		if(idx > 0 && idx <= n_rooms)
			l->vtx[idx].is_exit = (bool) is_exit;
	}
	
	int n_passages;
	scanf("%d ", &n_passages);
	for(int i = 0; i < n_passages; i++) {
		int from, to;
		scanf("%d %d ", &from, &to);

		if(from != to)
			link_rooms(l, from, to);
	}

	int treasure_room;
	scanf("%d ", &treasure_room);
	l->vtx[treasure_room].is_treasure = true;
	int treasure_bonus;
	scanf("%d ", &treasure_bonus);
	int n_alterations = 0;
	scanf("%d ", &n_alterations);
	int **alterations = (int **) malloc(n_alterations * sizeof(int *));
	for(int i = 0; i < n_alterations; i++) {
		alterations[i] = (int *) malloc(2 * sizeof(int));
		int from, to;
		scanf("%d %d ", &from, &to);

		if(from != to) {
			alterations[i][0] = from;
			alterations[i][1] = to;
		} else {
			alterations[i][0] = 0;
			alterations[i][1] = 0;
		}
	}
	int start;
	scanf("%d ", &start);
	l->vtx[start].is_exit = true;

	// initialization of our auxiliar data:

	bool *leads_to_exit = (bool *) calloc(n_points + 1, sizeof(bool));
	bool *old_leads_to_exit = NULL;

	// stores the paths wich lead to an exit, in order to
	// further sort it according to the specification
	int **paths = (int **) malloc(sizeof(int *) * MAX_PATH_N); 
	// adds trivial solution
	paths[0] = (int *) malloc(sizeof(int) * 4);
	paths[0][N_POINTS] = 1;
	paths[0][DISTANCE] = 0;
	paths[0][SCORE] = start == treasure_room ? treasure_bonus : 0;
	paths[0][3] = start;

	int n_paths = 1;

	int score = 0;

	// stores the rooms wich we have access, and where not yet explored
	stack_t *path = stack_init(MAX_PATH_N);

	bool **has_explored_from = (bool **) malloc((n_points + 1) * sizeof(bool *));
	bool **old_has_explored_from = NULL;
	for(int i = 1; i <= n_points; i++) has_explored_from[i] = (bool *) calloc((n_points + 1), sizeof(bool));

	bool *in_path = (bool *) calloc(n_points + 1, sizeof(bool));
	bool *old_in_path = NULL;
	for(int node = 1; node <= n_points; node++) {
		if(l->vtx[node].is_exit) {
			int exit = node;
			push(path, start);
			// printf("exit : %d\n", exit);
			in_path[start] = true;
			bool treasure_active = false;
			while(!is_empty(path)) {
				int curr_room = top(path);
				// printf("curr_room : %d\n", curr_room);

				if(l->vtx[curr_room].is_treasure && !treasure_active) {
					treasure_active = true;
					// printf("TREASURE! %d\n", curr_room);
					score = treasure_bonus;
					toggle_alterations(l, alterations, n_alterations);

					// saves old state
					old_leads_to_exit = leads_to_exit;
					leads_to_exit = (bool *) calloc(n_points + 1, sizeof(bool));

					old_in_path = in_path;
					in_path = (bool *) calloc(n_points + 1, sizeof(bool));
					in_path[curr_room] = true;

					old_has_explored_from = has_explored_from;
					has_explored_from = (bool **) malloc((n_points + 1) * sizeof(bool *));
					for(int i = 1; i <= n_points; i++) has_explored_from[i] = (bool *) calloc((n_points + 1), sizeof(bool));
				}

				bool found_next = false;
				for(int i = 1; i <= n_points; i++) {
					// printf("analysing path bet %d and %d\n", curr_room, i);
					if(!in_path[i] && l->edg[curr_room][i] > 0) {
						// printf("%d links to %d with weight %f\n", curr_room, i, l->edg[curr_room][i]);
						if(i != exit) {
							// printf("%d is not exit\n", i);
							if(!has_explored_from[curr_room][i]) {
								// printf("the next room is %d\n", i);
								in_path[i] = true;
								// printf("BEFORE PUSH =  %d\n", top(path));
								push(path, i);
								// printf("AFTER PUSH =  %d\n", top(path));
								has_explored_from[curr_room][i] = true;
								found_next = true;
								break;
							}
						} else {
							if(!leads_to_exit[curr_room]) {
								// printf("Found a way!\n");
								paths[n_paths++] = new_path(l, path, exit, score);
								// printf("Registered the path!\n");
								if(!treasure_active) leads_to_exit[curr_room] = true;
							}
							// printf("%d is exit, but been here before\n", i);
							continue;
						}
					}
				}

				if(found_next) continue;

				// printf("popping %d\n", curr_room);
				for(int i = 1; i <= n_points; i++) has_explored_from[curr_room][i] = false;
				if(l->vtx[curr_room].is_treasure) {
					treasure_active = false;
					score = 0;
					toggle_alterations(l, alterations, n_alterations);
					
					free(leads_to_exit);
					leads_to_exit = old_leads_to_exit;

					free(in_path);
					in_path = old_in_path;

					for(int i = 1; i <= n_points; i++) {
						free(has_explored_from[i]);
					}
					free(has_explored_from);
					has_explored_from = old_has_explored_from;
				}
				in_path[curr_room] = false;
				pop(path);
			}

			for(int i = 1; i <= n_points; i++) leads_to_exit[i] = false;
		}
	}

	stack_destroy(path);
	for(int i = 1; i <= n_points; i++) free(has_explored_from[i]);
	free(has_explored_from);
	free(leads_to_exit);
	free(in_path);

	for(int i = 0; i < n_alterations; i++) free(alterations[i]);
	free(alterations);
	graph_destroy(l);

	// sort paths:
	// qsort(paths, n_paths, sizeof(int *), sort_score);

	// outputs:
	printf("%d %d\n", treasure_room, treasure_bonus);

	for(int i = 0; i < n_paths; i++) {
		print_path(paths[i]);
		free(paths[i]);
	}
	free(paths);

	return 0;
}