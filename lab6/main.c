#include <stdio.h>

int multi(int i, int j) {
    if (i > 9) {
        return 0;
    }
    printf("%d*%d=%d ", i, j, i*j);
    if (!(j %= 9)) {
        i++;
        printf("\n");
    }
    return multi(i, j+1);
}

int main() {
    multi(1,1);
    return 0;
}
