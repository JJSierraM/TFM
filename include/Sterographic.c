#include "Sterographic.h"

inline Vector2 SterographicProject (Vector3 point) {
    return (Vector2) {point.x/(1-point.z), point.y/(1-point.z)}; 
}

Vector2* SterographicProjectArray (Vector3 *points, size_t n_points) {
    Vector2 *output = (Vector2*) malloc(n_points * sizeof(Vector2));
    #pragma omp parallel for
    for (size_t i; i < n_points ; i++) {
        output[i] = SterographicProject(points[i]);
    }
    return output;
}

inline Vector2 SterographicProjectInverted (Vector3 point) {
    return (Vector2) {point.x/(point.z), point.y/(point.z)}; 
}

Vector2* SterographicProjectInvertedArray (Vector3 *points, size_t n_points) {
    Vector2 *output = (Vector2*) malloc(n_points * sizeof(Vector2));
    #pragma omp parallel for
    for (size_t i; i < n_points ; i++) {
        output[i] = SterographicProjectInverted(points[i]);
    }
    return output;
}

