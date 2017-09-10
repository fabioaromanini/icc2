#include <stdlib.h>
#include <stdio.h>

#include <bool.h>

typedef struct {
	float x;
	float y;

	bool is_exit;
	bool is_treasure;
} point_t;

typedef struct {
	int n_points;
	point_t *point;
	bool **path;
} graph_t;

graph_t *graph_init(int n_points) {
	graph_t *g = (graph_t *) malloc(sizeof(graph_t));

	g->point = (point_t *) malloc(sizeof(point_t) * (n_points + 1));

	g->path = (bool **)  malloc(sizeof(bool *) * (n_points + 1));
	for(int i = 0; i <= n_points; i++)
		g->path[i] = (bool *) calloc(n_points + 1, sizeof(bool));


	g->n_points = n_points;
	return g;
}

void graph_destroy(graph_t *g) {
	for(int i = 0; i <= g->n_points; i++)
		free(g->path[i]);

	free(g->path);
	free(g->point);
	free(g);
}

void link_points(graph_t* l, int from, int to) {
	bool is_active = from > 0 && to > 0;

	if(to < 0) to = to * -1;
	if(from < 0) from = from * -1;
	
	if(from && to && from <= l->n_points && to <= l->n_points) {
		l->path[from][to] = is_active;
		l->path[to][from] = is_active;
	}
}

int main(int argc, char const *argv[]) {
	int n_points;
	scanf("%d ", &n_points);

	graph_t *l = graph_init(n_points);
	
	for(int i = 1; i <= n_points; i++) {
		float x, y;
		// ignores possible blank spaces
		scanf("%f %f ", &x, &y);

		l->point[i].x = x;
		l->point[i].y = y;

		l->point[i].is_exit = FALSE;
		l->point[i].is_treasure = FALSE;
	}

	int n_chambers;
	scanf("%d ", &n_chambers);
	for(int i = 0; i < n_chambers; i++) {
		int idx;
		bool is_exit;

		scanf("%d %d ", &idx, (int *) &is_exit);

		if(idx > 0 && idx <= n_points)
			l->point[idx].is_exit = is_exit;
	}
	
	int n_edges;
	scanf("%d ", &n_edges);

	for(int i = 0; i < n_edges; i++) {
		int from, to;
		scanf("%d %d ", &from, &to);

		if(from != to)
			link_points(l, from, to);
	}

	int start;
	int treasure_chamber = 0;
	int treasure_val = 0;
	int n_actions = 0;
	scanf("%d ", &start);
	
	if(!feof(stdin)) {
		treasure_chamber = start;
		scanf("%d ", &treasure_val);
		scanf("%d ", &n_actions);

		for(int i = 0; i < n_actions; i++) {
			int from, to;
			scanf("%d %d ", &from, &to);

			if(from != to)
				link_points(l, from, to);
		}
		
		scanf("%d ", &start);
	}

	printf("n_points: %d\n", n_points);
	printf("n_chambers: %d\n", n_points);
	for(int i = 1; i <= n_points; i++) {
		printf("Vertex[%d]:\n", i);
		printf("\tx: %f\n", l->point[i].x);
		printf("\ty: %f\n", l->point[i].y);

		if(l->point[i].is_exit)
			printf("This is a exit chamber\n");
		if(l->point[i].is_treasure)
			printf("This is a treasure chamber\n");
		printf("\n");
		printf("\n");
	}

	printf("start: %d\n", start);
	if(treasure_chamber) {
		printf("treasure_chamber: %d treasure_val: %d\n", treasure_chamber, treasure_val);
	} else {
		printf("no treasure_chamber\n");
	}

	for(int i = 1; i <= n_points; i++)
		for(int j = 1; j <= n_points; j++)
			if(l->path[i][j]) printf("%d links to %d\n", i, j);	

	graph_destroy(l);
	return 0;
}