// route.h

struct Coordinate {
    double lat;
    double lon;
};

double** get_curvature(struct Coordinate* coordinates, unsigned int size);

