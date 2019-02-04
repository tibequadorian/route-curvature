// vector.h

#include <math.h>

struct Vector {
    double x;
    double y;
};

void add(struct Vector* v1, struct Vector* v2, struct Vector* r);

void subtract(struct Vector* v1, struct Vector* v2, struct Vector* r);

void multiply(struct Vector* v, double factor, struct Vector* r);

double norm(struct Vector* v);

double distance(struct Vector* v1, struct Vector* v2);

void normalize(struct Vector* v, struct Vector* r);

void scale(struct Vector* v, double length, struct Vector* r);

double cross_product_norm(struct Vector* v1, struct Vector* v2);

