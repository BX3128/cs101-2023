#include <stdio.h>
#define SIZE(a) sizeof(a)/sizeof(a[0])-1

int string_to_int(char s[], int size);
int isnum(int c);

int main() {
    char a[] = "-99acbc"; // -99
    char b[] = "99acbc";  // 99
    char c[] = "ac-99bc"; // -99
    string_to_int(a, SIZE(a));
    string_to_int(b, SIZE(b));
    string_to_int(c, SIZE(c));

    /* Extended Tests
    char d[] = "-99a-8c"; // -99
    char e[] = "-a99abc"; // 99
    char f[] = "--99abc"; // -99
    string_to_int(d, SIZE(d));
    string_to_int(e, SIZE(e));
    string_to_int(f, SIZE(f));
    */
}

int string_to_int(char s[], int size) {
    int begin = -1; // index that number begins
    int v = 0;      // converted value
    for (int i = 0; i < size; i++) {
        int c = isnum(s[i]);
        if (c >= 0) {
            if (begin < 0) {
                begin = i;
            }
            v = v*10 + c;
        } else {
            if (begin >= 0) {
                break;
            }
        }
    }
    if (s[begin-1]=='-') {
        v *= -1;
    }
    printf("%d\n", v);
    return v;
}

// '0' to '9' are number characters
int isnum(int c) {
    if (c >= '0' && c <= '9') {
        return c-'0';
    }
    return -2;  // error code: not a number character
}

// HW#1 main4.c
// Purpose: 
//   Convert a string to an integer (int).
//   Maybe a positive number or a negative number.
//   Print out the integer.
//
//   (Given) Designated Tests:
//     -99acbc -> -99
//     99acbc  ->  99
//     ac-99bc -> -99
//
//   (Not Given) Extended Tests:
//     -99a-8c -> -99 (leftmost number)
//     -a99abc ->  99 (leftmost and meaningful number)
//     --99abc -> -99
//
//   Overview:
//     Based on the given tests, number to be extracted
//     must be a series of continuous characters
//     containing the negative sign '-' or '0' to '9'.
//
// Features:
//   (1) #define
//   (2) function prototype
//   (3) passing array to a function
//
// Notes:
//   (1) When passing an array to a funciton,
//       it is passing the array but the address of
//       0th element of the array.
//       In short, the information about the actual
//       size of an array is lost especially when
//       doing so -- array as a parameter of a function.
//       So, (probably) the only solution is to pass
//       the size of array as well.
