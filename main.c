#include "include/Triangulate.h"

Vector3 Sphr2Cart(const Vector3 point) {
    Vector3 output;
	output.x = point.x * sinf(point.y)*cosf(point.z);
	output.y = point.x * sinf(point.y)*sinf(point.z);
	output.z = point.x * cosf(point.y);
    return output;
}

Vector3 *FibonacciVertices(size_t n_points) {
    const float phi = 1.61803398875;
    float x, y, theta, fi, theta_s, fi_s;
    float residue;
    Vector3 *output = (Vector3*) malloc(n_points * sizeof(Vector3));
    for (size_t i = 0; i < n_points; i++) {
        x = modff(i/phi, &residue);
        y = 1.0 * i / (n_points);
        theta = acosf(1-2*x);
        fi = 2*PI*y;
        output[i] = Sphr2Cart((Vector3) {.x= 1.0, .y=theta, .z=fi});
    }
    return output;
}

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
	vertices[10]= (Vector3) {-phi,   0,   1};
	vertices[11]= (Vector3) {-phi,   0,  -1};

    for (size_t i = 0; i < 12; i++) {
       Vector3DivEquals(&vertices[i], (Vector3) {1.902113033, 1.902113033, 1.902113033});
    }
    return vertices;
}

int main() {
    Vector3 *points = IcosahedronVertices();
    const size_t vertices = 12;
    // Vector3 *points = FibonacciVertices(vertices);
    
    ArraySize_t indices = SphereTriangulate(points, vertices, 1);

    ArraySize_tPrint(&indices);
    printf("%u\n",indices.size);
    return 0;
}
