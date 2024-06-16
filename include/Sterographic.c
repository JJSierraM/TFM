#include "Sterographic.h"

extern Vector2 SterographicProject (Vector3 point) ;

Vector2* SterographicProjectArray (Vector3 *points, size_t n_points) {
    Vector2 *output = (Vector2*) malloc(n_points * sizeof(Vector2));
    #pragma omp parallel for
    for (size_t i = 0; i < n_points ; i++) {
        // DEBUG_PRINTLN("x: %f, y: %f, z: %f", points[i].x, points[i].y, points[i].z)
        output[i] = SterographicProject(points[i]);
        // DEBUG_PRINTLN("x: %f, y: %f", output[i].x, output[i].y)
    }
    return output;
}

Vector2* SterographicProjectArrayLowerHalf (Vector3 *points, size_t n_points) {
    Vector2 *output = (Vector2*) malloc(n_points * sizeof(Vector2));
    #pragma omp parallel for
    for (size_t i = 0; i < n_points ; i++) {
        // DEBUG_PRINTLN("x: %f, y: %f, z: %f", points[i].x, points[i].y, points[i].z)
        output[i] = points[i].z <=0 ? SterographicProject(points[i]) : (Vector2) {nanf(""), nanf("")} ;
        // DEBUG_PRINTLN("x: %f, y: %f", output[i].x, output[i].y)
    }
    return output;
}

ArrayVector2 SterographicProjectArrayVector2 (ArrayVector3 *points) {
    ArrayVector2 output = ArrayVector2New(points->size);
    #pragma omp parallel for
    for (size_t i = 0; i < points->size ; i++) {
        // DEBUG_PRINTLN("x: %f, y: %f, z: %f", points[i].x, points[i].y, points[i].z)
        output.array[i] = SterographicProject(points->array[i]);
        // DEBUG_PRINTLN("x: %f, y: %f", output[i].x, output[i].y)
    }
    return output;
}

extern Vector2 SterographicProjectInverted (Vector3 point) ;

Vector2* SterographicProjectInvertedArray (Vector3 *points, size_t n_points) {
    Vector2 *output = (Vector2*) malloc(n_points * sizeof(Vector2));
    #pragma omp parallel for
    for (size_t i = 0; i < n_points ; i++) {
        output[i] = SterographicProjectInverted(points[i]);
    }
    return output;
}

ArrayVector2 SterographicProjectInvertedArrayVector2 (ArrayVector3 *points) {
    ArrayVector2 output = ArrayVector2New(points->size);
    #pragma omp parallel for
    for (size_t i = 0; i < points->size ; i++) {
        // DEBUG_PRINTLN("x: %f, y: %f, z: %f", points[i].x, points[i].y, points[i].z)
        output.array[i] = SterographicProjectInverted(points->array[i]);
        // DEBUG_PRINTLN("x: %f, y: %f", output[i].x, output[i].y)
    }
    return output;
}
