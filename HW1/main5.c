#include <stdio.h>

void sort

int main() {
    char a[] = {-9, 8, 7, 6, 5, -4, 3, -2, 1};
    int i = 4;

    int size = sizeof(a) / sizeof(a[0]);
    if (i > size) {
        printf("Warning! You have designated a number i=%d\n", i);
        printf("which is greater than the size of array (%d)\n.", size);
        printf("This program now uses i=%d instead as the argument.\n", size);
        i = size;
    }
    int big[i]; // initialization is not necessary in this alogrithm

    big[0] = a[0];
    for (int j = 1; j < i; j++) {
        for (int k = 0; k < j; k++) {
            if (a[j] > big[])
        }


    }
}
