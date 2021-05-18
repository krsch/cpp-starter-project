#include "lib.h"
#include <stdlib.h>
#include <string.h>

int calc(void) {
    int a[] = {1, 2, 3, 4};
    int b[3] = {1, 2}; // b[2] = 0
    int c[a[0]];       // Только в C
    c[0] = 0;
    int len = sizeof(a) / sizeof(a[0]); // Длина массива
    return a[0] + b[0] + c[0] + len;
}

int sum(int arr[3]) { return arr[0] + arr[1] + arr[2]; }

int str(void) {
    char *s = "123";
    char s2[] = "123"; // {'1', '2', '3', '\0'}
    return (int)(strlen(s) + sizeof(s2) / sizeof(s2[0]));
}

int *make_buf(unsigned size) {
    int *res = malloc(sizeof(int) * size);
    return res; // Освобождать память с помощью free(res)
}

int call_c(int (*fun)(int), int arg) { return fun(arg); }

int call_void(int (*fun)(void *), void *arg) { return fun(arg); }
