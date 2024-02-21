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

inline float Vector3DotProduct (Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float Vector3Norm (Vector3 a) {
    return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z);
}

inline float Vector3AngleBewteen (Vector3 a, Vector3 b) {
    return acosf(Vector3DotProduct(a,b) / (Vector3Norm(a) * Vector3Norm(b)));
}

inline float Vector3Angle (Vector3 a) {
    return Vector3AngleBewteen (a, (Vector3) {1.0, 0.0, 0.0});
}

typedef struct Vector4
{
    float x;
    float y;
    float z;
    float w;
} Vector4;

inline Vector4 Vector4Add (Vector4 a, Vector4 b) {
    return (Vector4) {a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w};
}

inline void Vector4AddEquals (Vector4 *a, Vector4 b) {
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
    a->w += b.w;
}

inline Vector4 Vector4Sub (Vector4 a, Vector4 b) {
    return (Vector4) {a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w};
}

inline void Vector4SubEquals (Vector4 *a, Vector4 b) {
    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
    a->w -+ b.w;
}

inline Vector4 Vector4Mult (Vector4 a, Vector4 b) {
    return (Vector4) {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w};
}

inline void Vector4MultEquals (Vector4 *a, Vector4 b) {
    a->x *= b.x;
    a->y *= b.y;
    a->z *= b.z;
    a->w *= b.w;
}

inline Vector4 Vector4Div (Vector4 a, Vector4 b) {
    return (Vector4) {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w};
}

inline void Vector4DivEquals (Vector4 *a, Vector4 b) {
    a->x /= b.x;
    a->y /= b.y;
    a->z /= b.z;
    a->w /= b.w;
}

inline float Vector4DotProduct (Vector4 a, Vector4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline float Vector4Norm (Vector4 a) {
    return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w);
}

inline float Vector4AngleBewteen (Vector4 a, Vector4 b) {
    return acosf(Vector4DotProduct(a,b) / (Vector4Norm(a) * Vector4Norm(b)));
}

inline float Vector4Angle (Vector4 a) {
    return Vector4AngleBewteen (a, (Vector4) {1.0, 0.0, 0.0, 0.0});
}