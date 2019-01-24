// vector.h

#include <math.h>

struct Vector {
    double x;
    double y;
};

struct Vector add(struct Vector* v1, struct Vector* v2);

struct Vector subtract(struct Vector* v1, struct Vector* v2);

struct Vector multiply(struct Vector* v, double factor);

double length(struct Vector* v);

double distance(struct Vector* v1, struct Vector* v2);

struct Vector normalize(struct Vector* v);

struct Vector scale(struct Vector* v, double length);

