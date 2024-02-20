#include "Vector3.h"

typedef struct Vector3
{
    float x;
    float y;
    float z;
} Vector3;

inline Vector3 Vector3Add (Vector3 a, Vector3 b) {
    return (Vector3) {a.x+b.x, a.y+b.y, a.z+b.z};
}

inline void Vector3AddEquals (Vector3 *a, Vector3 b) {
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

inline Vector3 Vector3Sub (Vector3 a, Vector3 b) {
    return (Vector3) {a.x-b.x, a.y-b.y, a.z-b.z};
}

inline void Vector3SubEquals (Vector3 *a, Vector3 b) {
    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
}

inline Vector3 Vector3Mult (Vector3 a, Vector3 b) {
    return (Vector3) {a.x*b.x, a.y*b.y, a.z*b.z};
}

inline void Vector3MultEquals (Vector3 *a, Vector3 b) {
    a->x *= b.x;
    a->y *= b.y;
    a->z *= b.z;
}

inline Vector3 Vector3Div (Vector3 a, Vector3 b) {
    return (Vector3) {a.x/b.x, a.y/b.y, a.z/b.z};
}

inline void Vector3DivEquals (Vector3 *a, Vector3 b) {
    a->x /= b.x;
    a->y /= b.y;
    a->z /= b.z;
}

inline Vector3 Vector3CrossProduct (Vector3 a, Vector3 b) {
    return (Vector3) {  a.y * b.z - a.z * b.x, 
                        a.z * b.x - a.x * b.y, 
                        a.x * b.y - a.y * b.x
                        };
}

inline float Vector2DotProduct (Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Vector3Norm (Vector3 a) {
    return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z);
}

inline float Vector3AngleBewteen (Vector3 a, Vector3 b) {
    return acosf(Vector3DotProduct(a,b) / (Vector3Norm(a) * Vector3Norm(b)));
}

inline float Vector3Angle (Vector3 a) {
    return Vector3AngleBewteen (a, (Vector3) {1.0,0.0});
}