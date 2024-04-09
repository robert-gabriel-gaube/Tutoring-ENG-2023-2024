#ifndef __FUNCTION_H__
#define __FUNCTION_H__
struct Point {
    float x;
    float y;
};

#define N 3

float bisect(float (*func)(float), float a, float b, float epsilon);
void choleskyDecomposition(double A[N][N], double R[N][N]);
#endif