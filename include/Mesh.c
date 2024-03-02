#include <math.h>
#include <stdio.h>
#include "Vector.h"

//  WIP

typedef struct Point
{
    Vector3 position;
    size_t n_neighbours;
    size_t *neighbours;
};


typedef struct Mesh
{
    Vector3 *points;
};

