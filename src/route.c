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
    double lat = v->x, lon = v->y;
    v->x = lon*(M_PI/180);
    v->y = asinh(tan(lat*(M_PI/180)));
}

double get_curvature(struct Vector* v0, unsigned int n) {
    // TODO
    return 0.;
}

struct Vector get_center(struct Vector* v1, struct Vector* v2, double r) {
    struct Vector v = subtract(v1, v2);
    v = multiply(&v, 0.5);
    double d = length(&v);
    double sign = copysign(1.0, r);
    struct Vector u = { sign*v.y, -sign*v.x };
    u = scale(&u, sin(acos(d/r)*r));
    v = add(&v, &u);
    return add(v1, &v);
}

