#include<stdio.h> 
int main() 
{ 
    int x[] = {1, 2, 3, 4, 5, 6, 7};

    printf("%d ", *(x + 2));
    printf("%d ", x[0]);
    printf("%d ", 4[x]);
    printf("%d\n", 2[&x[1] + 1]);
    // 3 1 5 5
    
    return 0;
}   