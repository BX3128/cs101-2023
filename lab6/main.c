#include <stdio.h>

int multiplication(int i, int j) {
    if (i > 9) {
        return 0;
    }
    printf("%d*%d=%d ", i, j, i*j);
    if (!(j %= 9)) {
        i++;
        printf("\n");
    }
    return multiplication(i, j+1);
}

int main() {
    multiplication(1, 1);
    return 0;
}
