#include <math.h>
#include <stdio.h>
#include "functions.h"

float bisect(float (*func)(float), float a, float b, float epsilon) {
    if(func(a) * func(b) > 0) {
        printf("Invalid interval func(a) * func(b) should be < 0\n");
        return -1;
    } 

    float c = (a + b) / 2.0;
    
    while (b - a > epsilon) {
        if (func(c) == 0.0) {
            return c;
        }
        
        if (func(a) * func(c) < 0) {
            b = c;
        } else {
            a = c;
        }
        
        c = (a + b) / 2.0;
    }
    
    return c;
}

void choleskyDecomposition(double A[N][N], double R[N][N]) {
    // Verify that A is symetric
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < i; ++j) {
            if(A[i][j] != A[j][i]) {
                printf("Matrix is not symetric\n");
                return;
            }
        }
    }

    // Initialize the matrix R
    for(int i = 0; i < N; ++i) {
        for(int j = i; j < N; ++j) {
            R[i][j] = A[i][j];
        }
    }

    for(int i = 0; i < N; ++i) {
        if(R[i][i] < 0) {
            printf("Matrix is not positive definite\n");
            return;
        }

        R[i][i] = sqrt(R[i][i]);

        // Normalize the line elements
        for(int j = i + 1; j < N; ++j) {
            R[i][j] = R[i][j] / R[i][i];
        }

        // Update the remaining matrix
        for(int j = i + 1; j < N; ++j) {
            for(int k = j; k < N; ++k) {
                R[j][k] = R[j][k] - R[i][j] * R[i][k];
            }
        }
    }
}
