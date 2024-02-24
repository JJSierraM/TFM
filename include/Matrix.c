#include "Matrix.h"

Matrix MatrixNew(const size_t n, const size_t m) {
    Matrix output;
    output.n = n;
    output.m = m;
    output.matrix = (float*) malloc(n*m*sizeof(float));
    return output;
}

void MatrixDestroy(Matrix *matrix) {
    free(matrix->matrix);
    free(matrix);
}

float MatrixDeterminant(const Matrix *matrix) {
    float output = 0.0, diag;
    int row, col;

    //Error handling
    if (matrix->n != matrix->m) {
        printf("\nERROR: Matrix rows and columns are not equal!\nReturned nan\n");
        return nanf("");
    }
    
    for (size_t i = 0; i < matrix->m; i++) {
        diag = 1.0;
        for (size_t j = 0; j < matrix->m; j++) {
            row = j;
            col = (i+j)%matrix->m;
            diag *= matrix->matrix[row * matrix->m + col];
        }
        output += diag;
    }
    for (size_t i = 0; i < matrix->m; i++) {
        diag = 1.0;
        for (size_t j = 0; j < matrix->m; j++) {
            row = j;
            col = matrix->m - (i+j);
            col += matrix->m * (col < 0);
            diag *= matrix->matrix[row * matrix->m + col];
        }
        output -= diag;
    }
    return output;
}

void Matrix2x2SetRow(Matrix2x2 matrix, const size_t row, const Vector2 vector) {
    if (row > 1) {
        printf("\nERROR: You can not set a number of row over index 1!\n");
        return;
    }
    matrix[2*row] = vector.x;
    matrix[2*row+1] = vector.y;
}

void Matrix2x2SetCol(Matrix2x2 matrix, const size_t col, const Vector2 vector) {
    if (col > 1) {
        printf("\nERROR: You can not set a number of column over index 1!\n");
        return;
    }
    matrix[col] = vector.x;
    matrix[2+col] = vector.y;
}

float Matrix2x2Determinant(const Matrix2x2 matrix) {
    float output = 0.0, diag;
    size_t row, col;
    
    #pragma unroll(2)
    for (size_t i = 0; i < 2; i++) {
        diag = 1.0;
        #pragma unroll(2)
        for (size_t j = 0; j < 2; j++) {
            row = j;
            col = (i+j)%2;
            diag *= matrix[row * 2 + col];
        }
        output += diag;
    }
    #pragma unroll(2)
    for (size_t i = 0; i < 2; i++) {
        diag = 1.0;
        #pragma unroll(2)
        for (size_t j = 0; j < 2; j++) {
            row = j;
            col = 1 - (i+j);
            col += 2 * (col > 1);
            diag *= matrix[row * 2 + col];
        }
        output -= diag;
    }
    return output;
}

void Matrix3x3SetRow(Matrix3x3 matrix, const size_t row, const Vector3 vector) {
    if (row > 2) {
        printf("\nERROR: You can not set a number of row over index 2!\n");
        return;
    }
    matrix[3*row] = vector.x;
    matrix[3*row+1] = vector.y;
    matrix[3*row+2] = vector.z;
}

void Matrix3x3SetCol(Matrix3x3 matrix, const size_t col, const Vector3 vector) {
    if (col > 2) {
        printf("\nERROR: You can not set a number of column over index 2!\n");
        return;
    }
    matrix[col] = vector.x;
    matrix[3+col] = vector.y;
    matrix[6+col] = vector.z;
}

float Matrix3x3Determinant(const Matrix3x3 matrix) {
    float output = 0.0, diag;
    size_t row, col;
    
    #pragma unroll(3)
    for (size_t i = 0; i < 3; i++) {
        diag = 1.0;
        #pragma unroll(3)
        for (size_t j = 0; j < 3; j++) {
            row = j;
            col = (i+j)%3;
            diag *= matrix[row * 3 + col];
        }
        output += diag;
    }
    #pragma unroll(3)
    for (size_t i = 0; i < 3; i++) {
        diag = 1.0;
        #pragma unroll(3)
        for (size_t j = 0; j < 3; j++) {
            row = j;
            col = 2 - (i+j);
            col += 3 * (col > 2);
            diag *= matrix[row * 3 + col];
        }
        output -= diag;
    }
    return output;
}

void Matrix4x4SetRow(Matrix4x4 matrix, const size_t row, const Vector4 vector) {
    if (row > 3) {
        printf("\nERROR: You can not set a number of row over index 3!\n");
        return;
    }
    matrix[4*row] = vector.x;
    matrix[4*row+1] = vector.y;
    matrix[4*row+2] = vector.z;
    matrix[4*row+3] = vector.w;
}

void Matrix4x4SetCol(Matrix4x4 matrix, const size_t col, const Vector4 vector) {
    if (col > 3) {
        printf("\nERROR: You can not set a number of column over index 3!\n");
        return;
    }
    matrix[col] = vector.x;
    matrix[4+col] = vector.y;
    matrix[8+col] = vector.z;
    matrix[12+col] = vector.w;
}

float Matrix4x4Determinant(const Matrix4x4 matrix) {
    float output = 0.0, diag;
    size_t row, col;
    
    #pragma unroll(4)
    for (size_t i = 0; i < 4; i++) {
        diag = 1.0;
        #pragma unroll(4)
        for (size_t j = 0; j < 4; j++) {
            row = j;
            col = (i+j)%4;
            diag *= matrix[row * 4 + col];
        }
        output += diag;
    }
    #pragma unroll(4)
    for (size_t i = 0; i < 4; i++) {
        diag = 1.0;
        #pragma unroll(4)
        for (size_t j = 0; j < 4; j++) {
            row = j;
            col = 3 - (i+j);
            col += 4 * (col > 3);
            diag *= matrix[row * 4 + col];
        }
        output -= diag;
    }
    return output;
}
