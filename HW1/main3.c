#include <stdio.h>

int main() {
    char a[]="ABCabcABC";
    int shift=4;

    printf("%s\n", a);
    printf("%d\n", shift);
    for (int i=shift; i<sizeof(a)/sizeof(a[0])-1; i++) {
        printf("%c", a[i]);
    }
    for (int i=0; i<shift; i++) {
        printf("%c", a[i]);
    }
    printf("\n");
    return 0;
}

// HW#1 main3.c
// Purpose:
//   Shift Array.
//   For example, the input, a char array a[]="ABC123",
//   (a) if shift=1, then output "BC123A"
//   (b) if shift=2, then output "C123AB"
//   --> use a[]='ABCabcABC' as the default input
//   --> and the defualt shift=4
//   --> then the output shall be "bcABCABCa"
//
// Features:
//   (1) No need to generate a new array.
//
// Notes:
//   (1) char array (string) ends with \0
