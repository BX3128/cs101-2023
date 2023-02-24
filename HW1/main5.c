#define FIN      // finished product
//#define DEBUG    // detailed info for diagnosis
//#define COPILOT  // COPILOT version for comparsion ... see main5.pdf

#ifdef FIN
#include <stdio.h>

int main() {
    char a[] = {-9, 8, 7, 6, 5, -4, 3, -2, 1};
    int i = 4;

    int size = sizeof(a) / sizeof(a[0]);
    if (i > size) {
        printf("Warning! You have designated a number i=%d\n", i);
        printf("which is greater than the size of array (%d)\n.", size);
        printf("Now i=%d is used instead as the argument.\n", size);
        i = size;
    }
    char big[i]; // initialization is not necessary in this alogrithm

    big[0] = a[0];

    for (int j = 1; j < size; j++) {
        int comp = j <= i ? j : i;
        for (int k = 0; k < comp; k++) {
            if (a[j] >= big[k]) {
                for (int m = i-1; m > k; m--) {
                    big[m] = big[m-1];
                }
                big[k] = a[j];
                break;
            } else {
                if (k == comp-1 && comp < i) {
                    big[k+1] = a[j];
                }
            }
        }
    }
    printf("%d\n", big[i-1]);
    return 0;
}
#endif


#ifdef DEBUG
#include <stdio.h>

void inspect(char m[], int n) {
    for (int i=0; i<n; i++) {
        printf("%d ", m[i]);
    }
    printf("\n");
}

int main() {
    char a[] = {-9, 8, 7, 6, 5, -4, 3, -2, 1};
    int i = 4;

    int size = sizeof(a) / sizeof(a[0]);
    if (i > size) {
        printf("Warning! You have designated a number i=%d\n", i);
        printf("which is greater than the size of array (%d)\n.", size);
        printf("Now uses i=%d is used instead as the argument.\n", size);
        i = size;
    }
    char big[i]; // initialization is not necessary in this alogrithm

    printf("Input:\n  a[] = ");
    inspect(a, size);
    printf("  big[] = ");
    inspect(big, i);

    printf("Initialization: store a[0]=%d to big[0]=%d\n", a[0], big[0]);
    big[0] = a[0];
    printf("  big[] = ");
    inspect(big, i);

    for (int j = 1; j < size; j++) {
        printf("index j=%d loop: big[] = ", j);
        inspect(big, i);
        int comp = j <= i ? j : i;
        for (int k = 0; k < comp; k++) {
            if (a[j] >= big[k]) {
                printf("  a[%d]=%d > big[%d]=%d, ", j, a[j], k, big[k]);
                printf("store a[%d]=%d to big[%d]=%d:\n", j, a[j], k, big[k]);
                for (int m = i-1; m > k; m--) {
                    printf("    push big[%d]=%d to big[%d]=%d\n", m-1, big[m-1], m, big[m]);
                    big[m] = big[m-1];
                }
                big[k] = a[j];
                printf("    result: big[] = ");
                inspect(big, i);
                break;
            } else {
                printf("  a[%d]=%d < big[%d]=%d, pass\n", j, a[j], k, big[k]);
                if (k == comp-1 && comp < i) {
                    printf("  store a[%d]=%d to big[%d]=%d\n", j, a[j], k+1, big[k+1]);
                    big[k+1] = a[j];
                    printf("    result: big[] = ");
                    inspect(big, i);
                }
            }
        }
    }
    printf("final result: big[] = ");
    inspect(big, i);
    char seq[][3] = {"st","nd","rd","th"};
    int ith = i%10 < 4 ? i%10-1 : 3; 
    printf("The %d-%s largest element is %d.\n", i, seq[ith], big[i-1]);
}
#endif

#ifdef COPILOT
// find the i-th largest element in an array a[] of integers
// a[] must not be modified
// i=4, a[] = {-9, 8, 7, 6, 5, -4, 3, -2, 1}
// only stdio.h is allowed
// { should be on the same line as the function name or the control structure
#include <stdio.h>
int main() {
    int a[] = {-9, 8, 7, 6, 5, -4, 3, -2, 1};
    int i = 4;
    int n = sizeof(a)/sizeof(a[0]);
    int j, k, t;
    for (j = 0; j < n-1; j++) {
        for (k = j+1; k < n; k++) {
            if (a[j] < a[k]) {
                t = a[j];
                a[j] = a[k];
                a[k] = t;
            }
        }
    }
    printf("The %d-th largest element is %d.\n", i, a[i-1]);
    return 0;
}
#endif
