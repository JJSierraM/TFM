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

typedef struct Vector3Size_t
{
    size_t x;
    size_t y;
    size_t z;
} Vector3Size_t;

inline Vector3Size_t Vector3Size_tAdd (Vector3Size_t a, Vector3Size_t b) {
    return (Vector3Size_t) {a.x+b.x, a.y+b.y, a.z+b.z};
}

inline void Vector3Size_tAddEquals (Vector3Size_t *a, Vector3Size_t b) {
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

inline Vector3Size_t Vector3Size_tSub (Vector3Size_t a, Vector3Size_t b) {
    return (Vector3Size_t) {a.x-b.x, a.y-b.y, a.z-b.z};
}

inline void Vector3Size_tSubEquals (Vector3Size_t *a, Vector3Size_t b) {
    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
}

inline Vector3Size_t Vector3Size_tMult (Vector3Size_t a, Vector3Size_t b) {
    return (Vector3Size_t) {a.x*b.x, a.y*b.y, a.z*b.z};
}

inline void Vector3Size_tMultEquals (Vector3Size_t *a, Vector3Size_t b) {
    a->x *= b.x;
    a->y *= b.y;
    a->z *= b.z;
}

inline Vector3Size_t Vector3Size_tDiv (Vector3Size_t a, Vector3Size_t b) {
    return (Vector3Size_t) {a.x/b.x, a.y/b.y, a.z/b.z};
}

inline void Vector3Size_tDivEquals (Vector3Size_t *a, Vector3Size_t b) {
    a->x /= b.x;
    a->y /= b.y;
    a->z /= b.z;
}

inline Vector3Size_t Vector3Size_tCrossProduct (Vector3Size_t a, Vector3Size_t b) {
    return (Vector3Size_t) { a.y * b.z - a.z * b.x, 
                        a.z * b.x - a.x * b.y, 
                        a.x * b.y - a.y * b.x
                        };
}

inline float Vector2DotProduct (Vector3Size_t a, Vector3Size_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Vector3Size_tNorm (Vector3Size_t a) {
    return sqrtf((float) a.x*a.x + a.y*a.y + a.z*a.z);
}

inline float Vector3Size_tAngleBewteen (Vector3Size_t a, Vector3Size_t b) {
    return acosf(Vector3Size_tDotProduct(a,b) / (Vector3Size_tNorm(a) * Vector3Size_tNorm(b)));
}

inline float Vector3Size_tAngle (Vector3Size_t a) {
    return Vector3Size_tAngleBewteen (a, (Vector3Size_t) {1,0,0});
}