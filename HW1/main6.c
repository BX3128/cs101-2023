#include <stdio.h>

int main() {
    char a[] = "81c8g8u168";
    char r[][5] = {
        "I", "II", "III", "IV", "V",
        "VI", "VII", "VIII", "IX"
        };
    int size = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < size; i++) {
        if (a[i]>='0' && a[i]<='9') {
            printf("%s", r[a[i]-'1']);
        } else {
            printf("%c", a[i]);
        }
        printf(" ");
    }
    printf("\n");
    return 0;    
}

// HW#1 main6.c
// Purpose:
//   Transcript numbers (1-9) into Roman numbers.
//   1: I    2: II    3: III   4: IV    5: V
//   6: VI   7: VII   8: VIII  9: IX
//
//  Features:
//    (1) N/A
//
//  Notes:
//    (1) N/A
