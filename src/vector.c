#include "vector.h"

void add(struct Vector* v1, struct Vector* v2, struct Vector* r) {
    r->x = v1->x+v2->x;
    r->y = v1->y+v2->y;
}

void subtract(struct Vector* v1, struct Vector* v2, struct Vector* r) {
    r->x = v1->x-v2->x;
    r->y = v1->y-v2->y;
}

void multiply(struct Vector* v, double factor, struct Vector* r) {
    r->x = v->x*factor;
    r->y = v->y*factor;
}

double norm(struct Vector* v) {
    return hypot(v->x, v->y);
}

double distance(struct Vector* v1, struct Vector* v2) {
    struct Vector v;
    subtract(v1, v2, &v);
    return norm(&v);
}

void normalize(struct Vector* v, struct Vector* r) {
    multiply(v, 1/norm(v), r);
}

void scale(struct Vector* v, double length, struct Vector* r) {
    normalize(v, r);
    multiply(r, length, r);
}

double cross_product_norm(struct Vector* v1, struct Vector* v2) {
    return v1->x*v2->y-v1->y*v2->x;
}

