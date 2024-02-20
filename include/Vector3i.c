#include "Vector3i.h"

typedef struct Vector3i
{
    int x;
    int y;
    int z;
} Vector3i;

inline Vector3i Vector3iAdd (Vector3i a, Vector3i b) {
    return (Vector3i) {a.x+b.x, a.y+b.y, a.z+b.z};
}

inline void Vector3iAddEquals (Vector3i *a, Vector3i b) {
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

inline Vector3i Vector3iSub (Vector3i a, Vector3i b) {
    return (Vector3i) {a.x-b.x, a.y-b.y, a.z-b.z};
}

inline void Vector3iSubEquals (Vector3i *a, Vector3i b) {
    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
}

inline Vector3i Vector3iMult (Vector3i a, Vector3i b) {
    return (Vector3i) {a.x*b.x, a.y*b.y, a.z*b.z};
}

inline void Vector3iMultEquals (Vector3i *a, Vector3i b) {
    a->x *= b.x;
    a->y *= b.y;
    a->z *= b.z;
}

inline Vector3i Vector3iDiv (Vector3i a, Vector3i b) {
    return (Vector3i) {a.x/b.x, a.y/b.y, a.z/b.z};
}

inline void Vector3iDivEquals (Vector3i *a, Vector3i b) {
    a->x /= b.x;
    a->y /= b.y;
    a->z /= b.z;
}

inline Vector3i Vector3iCrossProduct (Vector3i a, Vector3i b) {
    return (Vector3i) { a.y * b.z - a.z * b.x, 
                        a.z * b.x - a.x * b.y, 
                        a.x * b.y - a.y * b.x
                        };
}

inline float Vector2DotProduct (Vector3i a, Vector3i b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Vector3iNorm (Vector3i a) {
    return sqrtf((float) a.x*a.x + a.y*a.y + a.z*a.z);
}

inline float Vector3iAngleBewteen (Vector3i a, Vector3i b) {
    return acosf(Vector3iDotProduct(a,b) / (Vector3iNorm(a) * Vector3iNorm(b)));
}

inline float Vector3iAngle (Vector3i a) {
    return Vector3iAngleBewteen (a, (Vector3i) {1,0,0});
}