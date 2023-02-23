#include <stdio.h>

int string_to_int(char s[]);
int isnum(int c);

int main() {
    char a[]="-99acbc";
    char b[]="99acbc";
    char c[]="ac-99bc";
}

int string_to_int(char s[]) {
    int begin=0;   // 1 = found numbers
    int sign=1;    // 1 = positive, -1 = negative
    int v=0;       // value
    for (int i=0; i<sizeof(s)/sizeof(s[0]); i++) {
        if (isnum(s[i])) {
            begin=1; // found numbers
            if (s[i]=='-')
        }
    }
}

int isnum(int c) {
    if (c == '-') {
        return c;
    }
    if (c >= '0' && c <= '9') {
        return c;
    }
    return 0;
}
