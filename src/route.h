// route.h

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

struct Vector {
    double x;
    double y;
};

struct Vector* calc_curvature(struct Vector* data, unsigned int length, bool true_input, int smoothness);

void apply_mercator_projection(struct Vector* v);

double distance(struct Vector* v1, struct Vector* v2);

double get_curvature(struct Vector* v, unsigned int n);

