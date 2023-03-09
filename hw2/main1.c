#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ONSCREEN     // display the result on the screen
//#define EXPORT       // export the result to the file

#define MAXLOT 69    // max lottery number
#define SPLOT 10     // max special lottery number
                     // min lottery number must be 1
#define NORMAL 6     // how many normal lot number
                     // only 1 special lot number allowed
#define MAX_GEN 5    // max lot number tuples to be generated

int lot[MAXLOT];     // global, lottery tickets

void init_lot(void); // initialize lot[]
void shuf_lot(void); // shuffle the lot[]
void sort_lot(void); // sort the first NORMAL lot numbers
int sp_lot(void);    // find the special number


int main() {
    srand((unsigned) time(NULL));

    time_t curtime;
    int n;
    FILE* fp;

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &n);
    printf("已為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);

    #ifdef ONSCREEN
    printf("======== lotto649 =========\n");
    #endif
    #ifdef EXPORT
    fp = fopen("lotto.txt", "w+");
    fprintf(fp, "======== lotto649 =========\r\n");
    #endif

    time(&curtime);
    #ifdef ONSCREEN
    printf("= %s =\n", ctime(&curtime));
    #endif
    #ifdef EXPORT
    fprintf(fp, "= %s =\r\n", ctime(&curtime));
    #endif

    init_lot();

    for (int i=0; i<MAX_GEN; i++) {
        shuf_lot();
        sort_lot();
        #ifdef ONSCREEN
        printf("[%d]: ",i+1);
        #endif
        for (int j=0; j<NORMAL; j++) {
            if (i<n) {
                #ifdef ONSCREEN
                printf("%02d ", lot[j]);
                #endif
            } else {
                printf("-- ");
            }
        }
        if (i<n) {
            #ifdef ONSCREEN
            printf("%02d\n", sp_lot());
            #endif
        } else {
            printf("--\n");
        }
    }

    #ifdef ONSCREEN
    printf("======== cise@CGU =========\n");
    #endif

    return 0;
}

void init_lot(void) {
    for (int i=0; i<MAXLOT; i++) {
        lot[i]=i+1;
    }
}

void shuf_lot(void) {
    int tmp, k;
    for (int i=MAXLOT-1; i>0; i--) {
        k = rand() % (i+1);
        tmp = lot[i];
        lot[i] = lot[k];
        lot[k] = tmp;
    }
}

int sp_lot(void) {
    for (int i=NORMAL; i<MAXLOT; i++) {
        if (lot[i] <= SPLOT) {
            return lot[i];
        }
    }
    return -1;
}

void sort_lot(void) {
    int tmp;
    for (int i=0; i<NORMAL; i++) {
        for (int j=0; j<NORMAL; j++) {
            if (lot[i] < lot[j]) {
                tmp = lot[i];
                lot[i] = lot[j];
                lot[j] = tmp;
            }
        }
    }
}

// Random But No Repeat
// Adapted algorithm: pencil-and-paper method (modern approach)
// reference:
//   https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#Modern_method
