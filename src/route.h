// route.h

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>

#include "vector.h"

struct Vector* calc_curvature(struct Vector* data, unsigned int length, bool true_input, int smoothness);

void apply_mercator_projection(struct Vector* v);

double get_curvature(struct Vector* v, unsigned int n);

struct Vector get_center(struct Vector* v1, struct Vector* v2, double r);

