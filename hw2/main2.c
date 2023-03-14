#include <stdio.h>

int main() {
    FILE* fp = fopen("main2.c", "r+");
    FILE* wp = fopen("main2.txt", "w+");
    char c;
    int i = 1;
    fprintf(wp, "01 ");
    while ((c = getc(fp)) != EOF) {
        c == '\n' ? fprintf(wp,"\n%02d ", ++i) : fprintf(wp, "%c", c);
    }
    fclose(fp);
    fclose(wp);
    return 0;
}
