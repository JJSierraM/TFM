#include <math.h>
#include <stdlib.h>
#include "Vector.h"

#ifndef STEROGRAPHIC
#define STEROGRAPHIC

inline Vector2 SterographicProject (Vector3 point) {
    return (Vector2) {point.x/(1-point.z), point.y/(1-point.z)};
}

Vector2* SterographicProjectArray (Vector3 *points, size_t n_points) ;

inline Vector2 SterographicProjectInverted (Vector3 point) {
    return (Vector2) {point.x/(point.z), point.y/(point.z)}; 
}

Vector2* SterographicProjectInvertedArray (Vector3 *points, size_t n_points) ;

#endif