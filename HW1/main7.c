#include <stdio.h>
#define T(a,n) t[a[n]-'0'][a[n+1]-'0'][a[n+2]-'0'][a[n+3]-'0']
#define P(a) printf("%c%c\n", T(a,0), T(a,4))

// function prototype
char n2c(int n);

// main()
int main() {
    char a[] = "10001111";
    char b[] = "10011110";

    // creat a 4D table
    int c = 0;
    char t[2][2][2][2] = {0};
    for (int i1=0; i1<2; i1++) {
        for (int i2=0; i2<2; i2++) {
            for (int i3=0; i3<2; i3++) {
                for (int i4=0; i4<2; i4++) {
                    t[i1][i2][i3][i4] = n2c(c++);
                }
            }
        }
    }
    P(a);
    P(b);
    return 0;
}

// convert a number (0-15) to 0-9 and A-F
char n2c(int n) {
    if (n < 10) {
        return n+'0';
    } else {
        return n+'A'-10;
    }
}

// HW#1 main7.c
// Purpose:
//   Transcript binary string to hex numbers
//   and print it out.
//
// Features:
//   (1) #define
//   (2) stacked #define
//   (3) function prototype
//
// Notes:
//   (1) N/A
