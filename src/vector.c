#include "vector.h"

struct Vector add(struct Vector* v1, struct Vector* v2) {
    struct Vector r = { v1->x+v2->x, v1->y+v2->y };
    return r;
}

struct Vector subtract(struct Vector* v1, struct Vector* v2) {
    struct Vector r = { v1->x-v2->x, v1->y-v2->y };
    return r;
}

struct Vector multiply(struct Vector* v, double factor) {
    struct Vector r = { v->x*factor, v->y*factor };
    return r;
}

double norm(struct Vector* v) {
    return hypot(v->x, v->y);
}

double distance(struct Vector* v1, struct Vector* v2) {
    struct Vector v = subtract(v1, v2);
    return norm(&v);
}

struct Vector normalize(struct Vector* v) {
    return multiply(v, 1/norm(v));
}

struct Vector scale(struct Vector* v, double length) {
    struct Vector u = normalize(v);
    return multiply(&u, length);
}

double cross_product_norm(struct Vector* v1, struct Vector* v2) {
    return v1->x*v2->y-v1->y*v2->x;
}

