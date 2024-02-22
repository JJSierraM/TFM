#include <math.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector3i.h"
#include "Matrix.h"
#include "LinkedList.h"
#include "Sterographic.h"

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

inline Vector3Size_t NextCombination (Vector3Size_t prev_combination) {
    Vector3Size_t output;
    if (prev_combination.z+1 != prev_combination.y) {
        output = Vector3Size_tAdd(prev_combination, (Vector3Size_t) {0, 0, 1});
    }
    else if (prev_combination.y+1 != prev_combination.x) {
        output = Vector3Size_tAdd(prev_combination, (Vector3Size_t) {0, 1, -prev_combination.z});
    }
    else {
        output = Vector3Size_tAdd(prev_combination, (Vector3Size_t) {1, 1-prev_combination.y, -prev_combination.z});
    }
    return output;
}

ArraySize_t Triangulation2D (Vector2 *points, size_t n_points) {
    Vector3Size_t combination = (Vector3Size_t) {2, 1, 0};
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
    return LinkedListSize_tToArrayAndFree(&indices);
}

ArraySize_t GetRimPoints (Vector2 *points, size_t n_points, ArraySize_t *indices) {
    size_t n_tris = indices->size / 3;
    float *angles = (float*) calloc(n_points, sizeof(float));
    size_t prev, next;
    Vector2 ab, ac;
    float angle;

    for (size_t i = 0; i < n_tris; i++) {
        for (size_t j = 0; j < 3; j++) {
            prev = j-1;
            prev += 3 * (prev < 0);
            next = (j+1) % 3;
            ab = Vector2Sub(points[indices->array[3*i + prev]], points[indices->array[3*i + j]]);
            ac = Vector2Sub(points[indices->array[3*i + next]], points[indices->array[3*i + j]]);
            angle = fabsf(Vector2Angle(ac) - Vector2Angle(ab));
            angle += 2*(PI-angle) * (angle > PI);
            angles[indices->array[3*i + j]] += angle;
        }
    }
    LinkedListSize_t rim_points = LinkedListSize_tNew();
    for (size_t i = 0; i < n_points; i++) {
        if (angles[i] < 2*PI-0.05) {
            LinkedListSize_tAppend(&rim_points, i);
        }
    }
    free(angles);
    return LinkedListSize_tToArrayAndFree(&rim_points);
}

ArraySize_t convert_indices(ArraySize_t *indices, ArraySize_t *conversion) {
    LinkedListSize_t converted = LinkedListSize_tNew();
    for (size_t i = 0; i < indices->size; i++) {
        LinkedListSize_tAppend(&converted, conversion->array[indices->array[i]]);
    }
    return LinkedListSize_tToArrayAndFree(&converted);
}

ArraySize_t SphereTriangulate (Vector3 *points, size_t n_points) {
    Vector2 *points_stero = SterographicProjectArray(points, n_points);
    ArraySize_t indices = Triangulation2D(points_stero, n_points);

    ArraySize_t final_points_indices = GetRimPoints(points_stero, n_points, &indices);
    if (final_points_indices.size > 0) {
        Vector3 *final_points = malloc(final_points_indices.size * sizeof(Vector3));
        for (size_t i = 0; i < final_points_indices.size; i++) {
            final_points[i] = points[final_points_indices.array[i]];
        }
        Vector2 *final_points_stero = SterographicProjectInvertedArray(final_points, final_points_indices.size);
        ArraySize_t final_indices_pre = Triangulation2D(final_points_stero, final_points_indices.size);
        ArraySize_t final_indices = convert_indices(&final_indices_pre, &final_points_indices);
        indices = ArraySize_tAppendArrays(&indices, &final_indices);
        ArraySize_tFree(&final_points);
        free(final_points);
        ArraySize_tFree(&final_indices_pre);
        ArraySize_tFree(&final_indices);
    }
    free(points_stero);
    ArraySize_tFree(&final_points_indices);
    return indices;
}