#include <math.h>
#include <stdlib.h>
#include <Vector2.h>
#include <Vector3.h>

inline Vector2 SterographicProject (Vector3 point) ;

Vector2* SterographicProjectArray (Vector3 *points, size_t n_points) ;

inline Vector2 SterographicProjectInverted (Vector3 point) ;

Vector2* SterographicProjectInvertedArray (Vector3 *points, size_t n_points) ;

