#include <math.h>
#include <stdio.h>

#ifndef VECTOR
#define VECTOR

typedef struct Vector2
{
    float x;
    float y;
} Vector2;

typedef struct Vector2i
{
    int x;
    int y;
} Vector2i;

typedef struct Vector3
{
    float x;
    float y;
    float z;
} Vector3;

typedef struct Vector3i
{
    int x;
    int y;
    int z;
} Vector3i;

typedef struct Vector3Size_t
{
    size_t x;
    size_t y;
    size_t z;
} Vector3Size_t;

typedef struct Vector4
{
    float x;
    float y;
    float z;
    float w;
} Vector4;

inline Vector2 Vector2Add (Vector2 a, Vector2 b) {
    return (Vector2) {a.x+b.x, a.y+b.y};
}

inline void Vector2AddEquals (Vector2 *a, Vector2 b) {
    a->x += b.x;
    a->y += b.y;
}

inline Vector2 Vector2Sub (Vector2 a, Vector2 b) {
    return (Vector2) {a.x-b.x, a.y-b.y};
}

inline void Vector2SubEquals (Vector2 *a, Vector2 b) {
    a->x -= b.x;
    a->y -= b.y;
}

inline Vector2 Vector2Mult (Vector2 a, Vector2 b) {
    return (Vector2) {a.x*b.x, a.y*b.y};
}

inline void Vector2MultEquals (Vector2 *a, Vector2 b) {
    a->x *= b.x;
    a->y *= b.y;
}

inline Vector2 Vector2Div (Vector2 a, Vector2 b) {
    return (Vector2) {a.x/b.x, a.y/b.y};
}

inline void Vector2DivEquals (Vector2 *a, Vector2 b) {
    a->x /= b.x;
    a->y /= b.y;
}

inline float Vector2CrossProduct (Vector2 a, Vector2 b) {
    return a.x * b.y - a.y * b.x;
}

inline float Vector2DotProduct (Vector2 a, Vector2 b) {
    return a.x * b.x + a.y * b.y;
}

inline float Vector2Norm (Vector2 a) {
    return sqrtf(a.x*a.x + a.y*a.y);
}

inline float Vector2AngleBewteen (Vector2 a, Vector2 b) {
    return acosf(Vector2DotProduct(a,b) / (Vector2Norm(a) * Vector2Norm(b)));
}

inline float Vector2Angle (Vector2 a) {
    if (a.y == 0)
        if (a.x >=0)
            return 0;
        else
            return 3.14159265358979323846;
    return Vector2AngleBewteen (a, (Vector2) {1.0,0.0}) * a.y/fabsf(a.y);
}

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

inline float Vector3iDotProduct (Vector3i a, Vector3i b) {
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

inline float Vector3Size_tDotProduct (Vector3Size_t a, Vector3Size_t b) {
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

#endif