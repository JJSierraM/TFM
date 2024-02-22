#include<math.h>
#include <stdlib.h>

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

inline Vector3i Vector3iAdd (Vector3i a, Vector3i b) ;

inline void Vector3iAddEquals (Vector3i *a, Vector3i b) ;

inline Vector3i Vector3iSub (Vector3i a, Vector3i b) ;

inline void Vector3iSubEquals (Vector3i *a, Vector3i b) ;

inline Vector3i Vector3iMult (Vector3i a, Vector3i b) ;

inline void Vector3iMultEquals (Vector3i *a, Vector3i b) ;

inline Vector3i Vector3iDiv (Vector3i a, Vector3i b) ;

inline void Vector3iDivEquals (Vector3i *a, Vector3i b) ;

inline Vector3i Vector3iCrossProduct (Vector3i a, Vector3i b) ;

inline float Vector3iDotProduct (Vector3i a, Vector3i b) ;

inline float Vector3iNorm (Vector3i a) ;

inline float Vector3iAngleBewteen (Vector3i a, Vector3i b) ;

inline float Vector3iAngle (Vector3i a) ;

inline Vector3Size_t Vector3Size_tAdd (Vector3Size_t a, Vector3Size_t b) ;

inline void Vector3Size_tAddEquals (Vector3Size_t *a, Vector3Size_t b) ;

inline Vector3Size_t Vector3Size_tSub (Vector3Size_t a, Vector3Size_t b) ;

inline void Vector3Size_tSubEquals (Vector3Size_t *a, Vector3Size_t b) ;

inline Vector3Size_t Vector3Size_tMult (Vector3Size_t a, Vector3Size_t b) ;

inline void Vector3Size_tMultEquals (Vector3Size_t *a, Vector3Size_t b) ;

inline Vector3Size_t Vector3Size_tDiv (Vector3Size_t a, Vector3Size_t b) ;

inline void Vector3Size_tDivEquals (Vector3Size_t *a, Vector3Size_t b) ;

inline Vector3Size_t Vector3Size_tCrossProduct (Vector3Size_t a, Vector3Size_t b) ;

inline float Vector3Size_tDotProduct (Vector3Size_t a, Vector3Size_t b) ;

inline float Vector3Size_tNorm (Vector3Size_t a) ;

inline float Vector3Size_tAngleBewteen (Vector3Size_t a, Vector3Size_t b) ;

inline float Vector3Size_tAngle (Vector3Size_t a) ;