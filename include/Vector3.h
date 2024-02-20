#include<math.h>

typedef struct Vector3
{
    float x;
    float y;
    float z;
} Vector3;

inline Vector3 Vector3Add (Vector3 a, Vector3 b) ;

inline void Vector3AddEquals (Vector3 *a, Vector3 b) ;

inline Vector3 Vector3Sub (Vector3 a, Vector3 b) ;

inline void Vector3SubEquals (Vector3 *a, Vector3 b) ;

inline Vector3 Vector3Mult (Vector3 a, Vector3 b) ;

inline void Vector3MultEquals (Vector3 *a, Vector3 b) ;

inline Vector3 Vector3Div (Vector3 a, Vector3 b) ;

inline void Vector3DivEquals (Vector3 *a, Vector3 b) ;

inline Vector3 Vector3CrossProduct (Vector3 a, Vector3 b) ;

inline float Vector2DotProduct (Vector3 a, Vector3 b) ;

inline float Vector3Norm (Vector3 a) ;

inline float Vector3AngleBewteen (Vector3 a, Vector3 b) ;

inline float Vector3Angle (Vector3 a) ;