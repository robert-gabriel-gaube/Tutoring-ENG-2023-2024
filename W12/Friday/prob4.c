#include <stdio.h>
#include <stdlib.h>

void throw_error(const char *s) {
    printf("ERROR: %s\n", s);
    exit(EXIT_FAILURE);
}

void myprintf(const char *format, void *params[]) {
    const char *ptr = format;
    void **param = params;

    while(*ptr) {
        if(*ptr != '%') {
            printf("%c", *ptr);
        }
        else {
            ++ptr;
            if(*ptr == 0) return;
            switch (*ptr)
            {
            case 'd':
                if(*param == NULL) throw_error("Param is null");
                printf("%d", *(int*)(*param));
                param++;
                break;
            case 'f':
                if(*param == NULL) throw_error("Param is null");
                printf("%.2f", *(float*)(*param));
                param++;
                break;
            case 's':
                if(*param == NULL) throw_error("Param is null");
                printf("%s", (char*)(*param));
                param++;
                break;
            case '%':
                printf("%%");
                break;

            default:
                printf("\n\tCombination %%%c is not accepted\n", *ptr);
                break;
            }
        }
        ++ptr;
    }

}

int main() {
    int a = 11;
    float f = 12.12;
    char s[] = "scoala";
    void *params[] = {&a, &f, &s, NULL};
    myprintf("Ana are %d mere si %f lei si merge la %s %%", params);
    return 0;
}
