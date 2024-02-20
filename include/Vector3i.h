#include<math.h>

typedef struct Vector3i
{
    int x;
    int y;
    int z;
} Vector3i;

inline Vector3i Vector3iAdd (Vector3i a, Vector3i b) ;

inline void Vector3iAddEquals (Vector3i *a, Vector3i b) ;

inline Vector3i Vector3iSub (Vector3i a, Vector3i b) ;

inline void Vector3iSubEquals (Vector3i *a, Vector3i b) ;

inline Vector3i Vector3iMult (Vector3i a, Vector3i b) ;

inline void Vector3iMultEquals (Vector3i *a, Vector3i b) ;

inline Vector3i Vector3iDiv (Vector3i a, Vector3i b) ;

inline void Vector3iDivEquals (Vector3i *a, Vector3i b) ;

inline Vector3i Vector3iCrossProduct (Vector3i a, Vector3i b) ;

inline float Vector2DotProduct (Vector3i a, Vector3i b) ;

inline float Vector3iNorm (Vector3i a) ;

inline float Vector3iAngleBewteen (Vector3i a, Vector3i b) ;

inline float Vector3iAngle (Vector3i a) ;