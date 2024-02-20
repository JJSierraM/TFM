#include<math.h>

typedef struct Vector2ii
{
    int x;
    int y;
} Vector2i;

inline Vector2i Vector2iAdd (Vector2i a, Vector2i b) ;

inline Vector2i Vector2iAddEquals (Vector2i *a, Vector2i b) ;

inline Vector2i Vector2iSub (Vector2i a, Vector2i b) ;

inline Vector2i Vector2iSubEquals (Vector2i *a, Vector2i b) ;

inline Vector2i Vector2iMult (Vector2i a, Vector2i b) ;

inline Vector2i Vector2iMultEquals (Vector2i *a, Vector2i b) ;

inline Vector2i Vector2iDiv (Vector2i a, Vector2i b) ;

inline Vector2i Vector2iDivEquals (Vector2i *a, Vector2i b) ;

inline int Vector2iCrossProduct (Vector2i a, Vector2i b) ;

inline int Vector2iDotProduct (Vector2i a, Vector2i b) ;

inline float Vector2iNorm (Vector2i a) ;

inline float Vector2iAngleBewteen (Vector2i a, Vector2i b) ;

inline float Vector2iAngle (Vector2i a) ;