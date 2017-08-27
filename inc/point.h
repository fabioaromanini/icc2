#ifndef _POINT_H
#define _POINT_H

#include <stdlib.h>
#include <stdio.h>

// As every point is an array of 3 doubles, the plain
// point_t is a dynamic type, thus, should be freed
typedef double * point_t;

enum {
	X,
	Y,
	Z,
	N_AXES,
};

point_t *read_points(int);
void print_point(point_t);
void free_point(point_t);

#endif
