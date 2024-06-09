#include <math.h>
#include <omp.h>
#include "Vector.h"
#include "Matrix.h"
#include "LinkedList.h"
#include "Sterographic.h"

#ifndef TRIANGULATE
#define TRIANGULATE

#define PI 3.14159265358979323846

inline size_t nCr (size_t n, size_t r){
    size_t output = 1;
    if (n<r) {output = 0;}
    else {
        size_t i;
        for (i=1; i<r+1; i++) {output=(output*(i+n-r))/i;}
    }
    return output;
}

//Return 1.0 if a,b,c are in right hand pattern, -1.0 if otherwise
inline float RightHand (Vector2 a, Vector2 b, Vector2 c) {
    Vector2 ab = Vector2Sub(b, a);
    Vector2 bc = Vector2Sub(c, b);
    float cros = Vector2CrossProduct(ab, bc);
    return cros/fabs(cros);
}

//Checks if point p is inside circle described by points a, b and c
inline int PointInCircle (Vector2 a, Vector2 b, Vector2 c, Vector2 p) {
    Matrix3x3 matrix = {
        a.x-p.x,    a.y-p.y,    powf(a.x-p.x,2)+powf(a.y-p.y,2),
        b.x-p.x,    b.y-p.y,    powf(b.x-p.x,2)+powf(b.y-p.y,2),
        c.x-p.x,    c.y-p.y,    powf(c.x-p.x,2)+powf(c.y-p.y,2),
    };
    float output = Matrix3x3Determinant(matrix) * RightHand(a, b, c);
    return output >= 0.0;
}

inline Vector3Size_t NextCombination (Vector3Size_t *prev_combination) {
    if (prev_combination->z+1 < prev_combination->y) {
        *prev_combination = Vector3Size_tAdd(*prev_combination, (Vector3Size_t) {0, 0, 1});
    }
    else if (prev_combination->y+1 < prev_combination->x) {
        *prev_combination = Vector3Size_tAdd(*prev_combination, (Vector3Size_t) {0, 1, -prev_combination->z});
    }
    else {
        *prev_combination = Vector3Size_tAdd(*prev_combination, (Vector3Size_t) {1, 1-prev_combination->y, -prev_combination->z});
    }
    return *prev_combination;
}

ArraySize_t Triangulation2D (Vector2 *points, size_t n_points) ;

ArraySize_t GetRimPoints (Vector2 *points, size_t n_points, ArraySize_t *indices) ;

ArraySize_t convert_indices(ArraySize_t *indices, ArraySize_t *conversion) ;

ArraySize_t SphereTriangulate (Vector3 *points, size_t n_points) ;

#endif