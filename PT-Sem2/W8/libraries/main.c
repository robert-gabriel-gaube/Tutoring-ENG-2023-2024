#include <stdio.h>
#define N 3

float func(float x) {
    return x * x - 4;
}

int main() {
    printf("\nBisection: ");
    printf("root ~= %f \n\n", bisect(func, 0, 3, 0.0001));

    double A[N][N] = {{4, -2, 2},
                      {-2, 2, -4},
                      {2, -4, 11}};

    double R[N][N];

    printf("Cholesky Decomposition: \n");
    choleskyDecomposition(A, R);

    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%f ", R[i][j]);
        }
        printf("\n");
    }
    

    return 0;
}
