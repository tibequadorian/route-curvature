// route.h

#include <stddef.h>
#include <stdbool.h>

struct Coordinate {
    double lat;
    double lon;
};

double** calc_curvature(double** data, unsigned int length, bool true_input, unsigned int* result_length);

