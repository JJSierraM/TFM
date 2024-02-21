#include <math.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector3i.h"
#include "Matrix.h"
#include "LinkedList.h"

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

inline Vector3i NextCombination(Vector3i prev_combination) {
    Vector3i output;
    if (prev_combination.z+1 != prev_combination.y) {
        output = Vector3iAdd(prev_combination, (Vector3i) {0, 0, 1});
    }
    else if (prev_combination.y+1 != prev_combination.x) {
        output = Vector3iAdd(prev_combination, (Vector3i) {0, 1, -prev_combination.z});
    }
    else {
        output = Vector3iAdd(prev_combination, (Vector3i) {1, 1-prev_combination.y, -prev_combination.z});
    }
    return output;
}

size_t* Triangulation2D(Vector2 *points, size_t n_points) {
    Vector3i combination = (Vector3i) {2, 1, 0};
    LinkedListSize_t indices = LinkedListSize_tNew();
    Vector2 a, b, c, d;
    size_t ok;
    for (size_t i = 0; i < nCr(n_points, 3); i++) {
        a = points[combination.x];
        b = points[combination.y];
        c = points[combination.z];
        ok = 1;
        for (size_t j = 0; j < n_points; j++) {
            if (j==combination.x || j==combination.y || j==combination.z)
                continue;
            d = points[j];
            if (PointInCircle(a, b, c, d)) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            LinkedListSize_tAppend(&indices, combination.x);
            LinkedListSize_tAppend(&indices, combination.y);
            LinkedListSize_tAppend(&indices, combination.z);
        }
        combination = NextCombination(combination);
    }
    size_t *output = LinkedListSize_tToArray(&indices);
    LinkedListSize_tFree(&indices);
    return output;
}