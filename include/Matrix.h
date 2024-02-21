#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Vector2.h"
#include "Vector3.h"

typedef struct Matrix {
    size_t n;
    size_t m;
    float *matrix;
} Matrix;

typedef float Matrix2x2[4];
typedef float Matrix3x3[9];
typedef float Matrix4x4[16];

Matrix MatrixNew(const size_t n, const size_t m) ;

void MatrixDestroy(Matrix *matrix) ;

float MatrixDeterminant(const Matrix *matrix) ;

void Matrix2x2SetRow(Matrix2x2 matrix, const size_t row, const Vector2 vector) ;

void Matrix2x2SetCol(Matrix2x2 matrix, const size_t col, const Vector2 vector) ;

float Matrix2x2Determinant(const Matrix2x2 matrix) ;

void Matrix3x3SetRow(Matrix3x3 matrix, const size_t row, const Vector3 vector) ;

void Matrix3x3SetCol(Matrix3x3 matrix, const size_t col, const Vector3 vector) ;

float Matrix3x3Determinant(const Matrix3x3 matrix) ;

void Matrix4x4SetRow(Matrix4x4 matrix, const size_t row, const Vector4 vector) ;

void Matrix4x4SetCol(Matrix4x4 matrix, const size_t col, const Vector4 vector) ;

float Matrix4x4Determinant(const Matrix4x4 matrix) ;
