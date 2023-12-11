#include <stdio.h>

typedef int* IP;
typedef IP* IPP;
typedef IPP* IPPP;

int main() {
    int x[] = {1, 2};

    IP p = x;
    IPP pp = &p;
    IPPP ppp = &pp;

    printf("%d\n", (*((**&*ppp) + 1)));
    // 2
    return 0;
}