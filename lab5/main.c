#include <stdio.h>

typedef int (*CALC)(int, int);

//int calc(int (*fun_ptr)(int, int), int x, int y) { // without typedef
int calc(CALC fun_ptr, int x, int y) {               // using typedef
    return fun_ptr(x, y);
}

int add(int x, int y) {
    return x + y;
}

int sub(int x, int y) {
    return x - y;
}

int mul(int x, int y) {
    return x * y;
}

int div(int x, int y) {
    return x / y;
}

int main() {
    printf("sum = %d\n", calc(add, 4, 2));
    printf("dif = %d\n", calc(sub, 4, 2));
    printf("product = %d\n", calc(mul, 4, 2));
    printf("quotient = %d\n", calc(div, 4, 2));
    return 0;
}
