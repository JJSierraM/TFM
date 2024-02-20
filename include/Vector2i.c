#include "Vector2i.h"

typedef struct Vector2ii
{
    int x;
    int y;
} Vector2i;

inline Vector2i Vector2iAdd (Vector2i a, Vector2i b) {
    return (Vector2i) {a.x+b.x, a.y+b.y};
}

inline void Vector2iAddEquals (Vector2i *a, Vector2i b) {
    a->x += b.x;
    a->y += b.y;
}

inline Vector2i Vector2iSub (Vector2i a, Vector2i b) {
    return (Vector2i) {a.x-b.x, a.y-b.y};
}

inline void Vector2iSubEquals (Vector2i *a, Vector2i b) {
    a->x -= b.x;
    a->y -= b.y;
}

inline Vector2i Vector2iMult (Vector2i a, Vector2i b) {
    return (Vector2i) {a.x*b.x, a.y*b.y};
}

inline void Vector2iMultEquals (Vector2i *a, Vector2i b) {
    a->x *= b.x;
    a->y *= b.y;
}

inline Vector2i Vector2iDiv (Vector2i a, Vector2i b) {
    return (Vector2i) {a.x/b.x, a.y/b.y};
}

inline void Vector2iDivEquals (Vector2i *a, Vector2i b) {
    a->x /= b.x;
    a->y /= b.y;
}

inline int Vector2iCrossProduct (Vector2i a, Vector2i b) {
    return a.x * b.y - a.y * b.x;
}

inline int Vector2iDotProduct (Vector2i a, Vector2i b) {
    return a.x * b.x + a.y * b.y;
}

inline float Vector2iNorm (Vector2i a) {
    return sqrtf((float) a.x*a.x + a.y*a.y);
}

inline float Vector2iAngleBewteen (Vector2i a, Vector2i b) {
    return acosf(Vector2iDotProduct(a,b) / (Vector2iNorm(a) * Vector2iNorm(b)));
}

inline float Vector2iAngle (Vector2i a) {
    return Vector2iAngleBewteen (a, (Vector2i) {1,0});
}