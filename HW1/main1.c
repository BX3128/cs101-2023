#include <stdio.h>

int main() {
    char a[]="AABBBCCCCddd";
    int f[256]={0};
    for (int i=0; i<sizeof(a)/sizeof(a[0])-1; i++) {
        f[a[i]]++;
    }
    for (int i=0; i<sizeof(f)/sizeof(f[0]); i++) {
        if (f[i]>0) {
            printf("%c%d", i, f[i]);
        }
    }
    printf("\n");
    return 0;
}
// HW#1 main1.c
// Purpose:
//     Run-length encoding "AABBBCCCCddd".
//     output: "A2B3C4d3"
//
// Features:
// (1) The input, char array (string) a[], can be
//     (a) in any length, 
//     (b) any combination of ASCII code chars, and
//     (c) using any sequence.
//
// Notes:
// (1) Length of string in C is at least 1
//     because it uses \0
//     to indicate the end of a string.
//     Therefore, reading only the content concerned,
//     we shall ignore the last element, \0,
//     as it must be content-irrelevant.
// (2) By using DP (Dynamic Programming) algorithm,
//     this code is easy to understand but runs sparsely.
//     More efforts to make to reduce memory usage.
