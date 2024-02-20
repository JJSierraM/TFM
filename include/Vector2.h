#include<math.h>

typedef struct Vector2
{
    float x;
    float y;
} Vector2;

inline Vector2 Vector2Add (Vector2 a, Vector2 b) ;

inline void Vector2AddEquals (Vector2 *a, Vector2 b) ;

inline Vector2 Vector2Sub (Vector2 a, Vector2 b) ;

inline void Vector2SubEquals (Vector2 *a, Vector2 b) ;

inline Vector2 Vector2Mult (Vector2 a, Vector2 b) ;

inline void Vector2MultEquals (Vector2 *a, Vector2 b) ;

inline Vector2 Vector2Div (Vector2 a, Vector2 b) ;

inline void Vector2DivEquals (Vector2 *a, Vector2 b) ;

inline float Vector2CrossProduct (Vector2 a, Vector2 b) ;

inline float Vector2DotProduct (Vector2 a, Vector2 b) ;

inline float Vector2Norm (Vector2 a) ;

inline float Vector2AngleBewteen (Vector2 a, Vector2 b) ;

inline float Vector2Angle (Vector2 a) ;