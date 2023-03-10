#include <stdio.h>

int main() {
    FILE* fp = fopen(__FILE__, "r");
    char c;
    int i = 1;
    printf("01 ");
    while (fread(&c, 1, 1, fp) == 1) {
        c == '\n' ? printf("\n%02d ", ++i) : printf("%c", c);
    }
    fclose(fp);
    printf("\n");
    return 0;
}
