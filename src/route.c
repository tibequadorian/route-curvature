#include "route.h"

struct Vector* calc_curvature(struct Vector* data, unsigned int length, bool true_input, int smoothness) {
    if (!true_input) {
        for (int i = 0; i < length; i++)
            apply_mercator_projection(&data[i]);
    }
    int result_length = length-smoothness+1;
    struct Vector* result_data = (struct Vector*)malloc(result_length*sizeof(struct Vector));
    double d = 0;
    for (int i = 0; i < smoothness-2; i++)
        d += distance(&data[i], &data[i+1])/2;
    for (int i = 0; i < result_length; i++) {
        d += distance(&data[i+smoothness-2], &data[i+smoothness-1])/2;
        result_data[i].x = d;
        result_data[i].y = get_curvature(&data[i], smoothness);
        d += distance(&data[i], &data[i+1])/2;
    }
    return result_data;
}

void apply_mercator_projection(struct Vector* v) {
    v->x *= M_PI / 180;
    v->y = asinh(tan(v->y * (M_PI / 180)));
}

double distance(struct Vector* v1, struct Vector* v2) {
    return hypot(v1->x-v2->x, v1->y-v2->y);
}

double get_curvature(struct Vector* v, unsigned int n) {
    return 0.;
}

