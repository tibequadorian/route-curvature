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

inline void find_nearest_curvature(struct Vector* v1, struct Vector* vn, double min, double max, double* nearest_curvature, double* nearest_deviation) {
    const static double delta = 1E-12; // hard-coded accuracy
    double c, d;
    while (fabs(min-max)/2 > delta) {
        double step = (1.0/4)*(max-min);
        for (int q = 1; q < 4; q++) {
            c = min+q*step;
            d = get_deviation(v1, vn, c);
            if (d < *nearest_deviation) {
                *nearest_deviation = d;
                *nearest_curvature = c;
            }
        }
        min = *nearest_curvature-step;
        max = *nearest_curvature+step;
    }
}

void get_center(struct Vector* v1, struct Vector* v2, double r, struct Vector* center);
