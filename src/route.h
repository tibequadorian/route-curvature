// route.h

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#include "vector.h"

struct Vector* calc_curvature(struct Vector* data, unsigned int length, bool true_input, int smoothness);

void apply_mercator_projection(struct Vector* v);

double get_curvature(struct Vector* v1, struct Vector* vn);

double get_deviation(struct Vector* v1, struct Vector* vn, double c);

#include <stdio.h>
inline void find_nearest_curvature(struct Vector* v1, struct Vector* vn, double min, double max, double* nearest_curvature, double* nearest_deviation) {
    for (double i = min; fabs(i) < fabs(max); i += (max-min)/1000) {
        if (get_deviation(v1, vn, i) < *nearest_deviation) {
            *nearest_curvature = i;
            *nearest_deviation = get_deviation(v1, vn, i);
        }
    }
}

void get_center(struct Vector* v1, struct Vector* v2, double r, struct Vector* center);

