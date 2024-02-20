#include "Vector2.h"

typedef struct Vector2
{
    float x;
    float y;
} Vector2;

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
    return Vector2AngleBewteen (a, (Vector2) {1.0,0.0});
}