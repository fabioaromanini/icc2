#include <point.h>

point_t *read_points(int n_rows) {
	point_t *points = (point_t *) malloc(sizeof(point_t) * n_rows);
	for(int i = 0; i < n_rows; i++) {
		points[i] = (point_t) malloc(sizeof(double) * N_AXES);
		scanf("%lf%*c%lf%*c%lf%*c", &(points[i][X]), &(points[i][Y]), &(points[i][Z]));
	}

	return points;
}

void print_point(point_t *p) {
	printf("%lf %lf %lf\n\n", *p[X], *p[Y], *p[Z]);
}

void free_point(point_t *p) {
	free(*p);
}
