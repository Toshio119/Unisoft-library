/*
===================================================
       U!nisoft Libarary's 
       Utility at it's peak
---------------------------------------------------
  ##    ##  ##   ##        ##   #####
  ##    ##  ##   ##             ##   #
  ##    ##  ##   ##        ##   ##   #
  ##    ##  ##   ##        ##   #####
  ##    ##  ##   ##        ##   ##   #
  ##    ##       ##        ##   ##   #
    ####    ##   ########  ##   #####
---------------------------------------------------
© 2024 Unisoft .All rights reserved.
For support, contact: toshiojp119@gmail.com
===================================================
*/

#ifndef MATUTIL_H
#define MATUTIL_H

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX_ROWS 100
#define MAX_COLS 100

void parseMatrix(const char *input);
int parseNumber(const char **str);
char nextNonWhitespaceChar(const char **str);

void parseMatrix(const char *input) {
    const char *ptr = input;

    // Skip initial characters to find the start of the matrix data
    while (*ptr && *ptr != '[') ptr++;
    if (*ptr == '\0') {
        fputs("Error: No matrix data found.\n", stderr);
        return;
    }
    ptr++; // Skip '['

    // Variables to track matrix dimensions
    int rows = 0, cols = 0;
    int data[MAX_ROWS][MAX_COLS];

    // Initialize matrix to zero
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            data[i][j] = 0.0;
        }
    }

    while (*ptr && *ptr != ']') {
        // Skip whitespace
        ptr += strspn(ptr, " \t\r\n");

        // Check for end of row
        if (*ptr == ';') {
            rows++;
            cols = 0;
            ptr++;
            continue;
        }

        // Parse numbers in the row
        while (*ptr && *ptr != ';' && *ptr != ']') {
            if (cols < MAX_COLS) {
                data[rows][cols++] = parseNumber(&ptr);
            } else {
                printf("Error: Too many columns in row %d.\n", rows + 1);
                return;
            }
        }

        // Update max_cols if needed
        if (cols > MAX_COLS) {
            fputs("Error: Too many columns in the matrix.\n", stderr);
            return;
        }
    }

    // Update matrix dimensions
    rows++; // Count the last row
    if (rows > MAX_ROWS) {
        fputs("Erroputsr: Too many rows in the matrix.\n", stderr);
        return;
    }

    printf("Matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
}

int parseNumber(const char **str) {
    char buffer[100];
    int i = 0;
    while (isspace(**str)) (*str)++;
  
    while (isdigit(**str) || **str == '.' || **str == '-' || **str == '+') {
        buffer[i++] = **str;
        (*str)++;
    }
    buffer[i] = '\0';
    return atoi(buffer);
}

char nextNonWhitespaceChar(const char **str) {
    while (isspace(**str)) (*str)++;
    return **str;
}


// Helper function to convert a matrix string into a 2D array
static void stringToMatrix(const char *input, int mat[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
    const char *ptr = input;
    *rows = 0;
    *cols = 0;

    while (*ptr && *ptr != '[') ptr++;
    if (*ptr == '\0') {
        fputs("Error: No matrix data found.\n", stderr);
        return;
    }
    ptr++;

    int tempCols = 0;
    while (*ptr && *ptr != ']') {
        ptr += strspn(ptr, " \t\r\n");
        if (*ptr == ';') {
            (*rows)++;
            if (*cols < tempCols) *cols = tempCols;
            tempCols = 0;
            ptr++;
            continue;
        }

        while (*ptr && *ptr != ';' && *ptr != ']') {
            if (tempCols < MAX_COLS) {
                mat[*rows][tempCols++] = (int)parseNumber(&ptr);
            } else {
                printf("Error: Too many columns in row %d.\n", *rows + 1);
                return;
            }
        }
    }
    (*rows)++;
    if (*cols < tempCols) *cols = tempCols;
    if (*rows > MAX_ROWS) {
        fputs("Error: Too many rows in the matrix.\n", stderr);
        return;
    }
}

// Add matrices
void addMatrices(const char *matrix1, const char *matrix2) {
    int mat1[MAX_ROWS][MAX_COLS], mat2[MAX_ROWS][MAX_COLS];
    int rows1, cols1, rows2, cols2;

    stringToMatrix(matrix1, mat1, &rows1, &cols1);
    stringToMatrix(matrix2, mat2, &rows2, &cols2);

    if (rows1 != rows2 || cols1 != cols2) {
        fputs("Error: Matrix dimensions do not match for addition.\n", stderr);
        return;
    }

    int result[MAX_ROWS][MAX_COLS];
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }

    printf("Sum of matrices (%d x %d):\n", rows1, cols1);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

// Subtract matrices
void subtractMatrices(const char *matrix1, const char *matrix2) {
    int mat1[MAX_ROWS][MAX_COLS], mat2[MAX_ROWS][MAX_COLS];
    int rows1, cols1, rows2, cols2;

    stringToMatrix(matrix1, mat1, &rows1, &cols1);
    stringToMatrix(matrix2, mat2, &rows2, &cols2);

    if (rows1 != rows2 || cols1 != cols2) {
        fputs("Error: Matrix dimensions do not match for subtraction.\n", stderr);
        return;
    }

    int result[MAX_ROWS][MAX_COLS];
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }

    printf("Difference of matrices (%d x %d):\n", rows1, cols1);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

// Multiply matrices
void multiplyMatrices(const char *matrix1, const char *matrix2) {
    int mat1[MAX_ROWS][MAX_COLS], mat2[MAX_ROWS][MAX_COLS];
    int rows1, cols1, rows2, cols2;

    stringToMatrix(matrix1, mat1, &rows1, &cols1);
    stringToMatrix(matrix2, mat2, &rows2, &cols2);

    if (cols1 != rows2) {
        fputs("Error: Incompatible matrix dimensions for multiplication.\n", stderr);
        return;
    }

    int result[MAX_ROWS][MAX_COLS] = {0};
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    printf("Product of matrices (%d x %d):\n", rows1, cols2);
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

// Transpose matrix
void transposeMatrix(const char *matrix) {
    int mat[MAX_ROWS][MAX_COLS];
    int rows, cols;

    stringToMatrix(matrix, mat, &rows, &cols);

    int result[MAX_COLS][MAX_ROWS];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = mat[i][j];
        }
    }

    printf("Transpose of matrix (%d x %d):\n", cols, rows);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

// Invert matrix (using Gaussian elimination)
int invertMatrix(const char *matrix) {
    double mat[MAX_ROWS][MAX_COLS];
    int size;
    double result[MAX_ROWS][MAX_COLS];
    double identity[MAX_ROWS][MAX_COLS] = {0};

    stringToMatrix(matrix, (int (*)[MAX_COLS])mat, &size, &size);

    for (int i = 0; i < size; i++) {
        identity[i][i] = 1.0;
    }

    double temp[MAX_ROWS][MAX_COLS];
    memcpy(temp, mat, sizeof(temp));

    for (int i = 0; i < size; i++) {
        double maxEl = fabs(temp[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < size; k++) {
            if (fabs(temp[k][i]) > maxEl) {
                maxEl = fabs(temp[k][i]);
                maxRow = k;
            }
        }

        if (i != maxRow) {
            for (int k = 0; k < size; k++) {
                double tmp = temp[i][k];
                temp[i][k] = temp[maxRow][k];
                temp[maxRow][k] = tmp;
                tmp = identity[i][k];
                identity[i][k] = identity[maxRow][k];
                identity[maxRow][k] = tmp;
            }
        }

        if (fabs(temp[i][i]) < 1e-10) {
            fputs("Error: Matrix is singular and cannot be inverted.\n", stderr);
            return 0;
        }

        for (int k = 0; k < size; k++) {
            identity[i][k] /= temp[i][i];
            temp[i][k] /= temp[i][i];
        }

        for (int k = 0; k < size; k++) {
            if (k == i) continue;
            double factor = temp[k][i];
            for (int j = 0; j < size; j++) {
                temp[k][j] -= factor * temp[i][j];
                identity[k][j] -= factor * identity[i][j];
            }
        }
    }

    memcpy(result, identity, sizeof(result));

    printf("Inverse of matrix (%d x %d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%f ", result[i][j]);
        }
        printf("\n");
    }

    return 1;
}


#define creatematrix(x) parseMatrix(#x);
#define addmat(x, y) addMatrices(#x, #y);
#define submat(x, y) subtractMatrices(#x, #y);
#define mulmat(x, y) multiplyMatrices(#x, #y);
#define transpose(x) transposeMatrix(#x);
#define invert(x) invertMatrix(#x);

#endif
