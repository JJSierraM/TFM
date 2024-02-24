#include "include/Triangulate.h"

Vector3* IcosahedronVertices() {
    const float phi = 1.61803398875;
    Vector3 *vertices = (Vector3*) malloc(12 * sizeof(Vector3));
    vertices[0] = (Vector3) {   0,   1, phi};
	vertices[1] = (Vector3) {   0,  -1, phi};
	vertices[2] = (Vector3) {   0,   1,-phi};
	vertices[3] = (Vector3) {   0,  -1,-phi};
	vertices[4] = (Vector3) {   1, phi,   0};
	vertices[5] = (Vector3) {  -1, phi,   0};
	vertices[6] = (Vector3) {   1,-phi,   0};
	vertices[7] = (Vector3) {  -1,-phi,   0};
	vertices[8] = (Vector3) { phi,   0,   1};
	vertices[9] = (Vector3) { phi,   0,  -1};
	vertices[10] = (Vector3) {-phi,   0,   1};
	vertices[11] = (Vector3) {-phi,   0,  -1};

    for (size_t i = 0; i < 12; i++) {
       Vector3DivEquals(&vertices[i], (Vector3) {1.902113033, 1.902113033, 1.902113033});
    }
    return vertices;
}

int main() {
    Vector3 *points = IcosahedronVertices();

    // Vector2 a = (Vector2) {1,0};
    // Vector2 b = (Vector2) {0,0};
    // Vector2 c = (Vector2) {0,1};
    // Vector2 d = (Vector2) {1.5,0.5};

    // int rh = RightHand(a, b, c);
    // int pic = PointInCircle(a, b, c, d);
    // printf("Right hand? %d\n", rh);
    // printf("Point in circle? %d\n", pic);

    ArraySize_t indices = SphereTriangulate(points, 12);

    ArraySize_tPrint(&indices);

    return 0;
}