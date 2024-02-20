#include <math.h>
#include "Vector2.h"
#include "Vector3.h"

//Return 1.0 if a,b,c are in right hand pattern, -1.0 if otherwise
inline float right_hand (Vector2 a, Vector2 b, Vector2 c) {
    Vector2 ab = Vector2Sub(b, a);
    Vector2 bc = Vector2Sub(c, b);
    float cros = Vector2CrossProduct(ab, bc);
    return cros/fabs(cros);
}
