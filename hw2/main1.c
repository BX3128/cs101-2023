#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// build parameters
//#define ONSCREEN   // Remark this line to export the messages to file.
                     // Otherwise, they will be on the screen. 

// program parameters
#define MAXLOT 69    // max lottery number
#define SPLOT 10     // max special lottery number
                     // lottery number must begin with 1
#define NORMAL 6     // how many normal lot number
                     // only 1 special lot number allowed
#define MAX_GEN 5    // max lot number tuples to be generated

// global variables
int lot[MAXLOT];     // lottery tickets

// function prototypes
void init_lot(void); // initialize lot[]
void shuf_lot(void); // shuffle the lot[]
void sort_lot(void); // sort the first NORMAL lot numbers
void swap_lot(int i, int j); // swap the i and j elements of lot[]
int sp_lot(void);    // find the special number

// main()
int main(int argc, char* argv[]) {
    srand((unsigned) time(NULL)); // random seed

    time_t curtime;
    char time_str[80];  // string buffer to store current time
    int n;              // how many tuples of lot to buy?

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &n);
    printf("已為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);

    #ifdef ONSCREEN
        #define fp stdout
    #else
        FILE* fp;
        fp = fopen("lotto.txt", "w+");
    #endif
    fprintf(fp, "========= lotto649 =========\r\n");

    time(&curtime);
    // ctime() attaches a newline (0x0A) charaacter, i.e., "%s\n"
    // We got to remove it manually.
    strcpy(time_str, ctime(&curtime));
    for (int i=0; i<sizeof(time_str)/sizeof(time_str[0]); i++) {
        if (time_str[i] == '\0') {
            time_str[i-1] = '\0';
            break;
        }
    }
    fprintf(fp, "= %s =\r\n", time_str);

    init_lot();  // initialize the lot[] array

    for (int i=0; i<MAX_GEN; i++) {
        shuf_lot(); // shuffle lot[] array
        sort_lot(); // sort the first MAXLOT elements in lot[]
        fprintf(fp, "[%d]: ",i+1);
        for (int j=0; j<NORMAL; j++) {
            if (i<n) {
                fprintf(fp, "%02d ", lot[j]);
            } else {
                fprintf(fp, "-- ");
            }
        }
        if (i<n) {
            fprintf(fp, "%02d\n", sp_lot());
        } else {
            fprintf(fp, "--\n");
        }
    }

    fprintf(fp, "========= cise@CGU =========\n");
    #ifndef ONSCREEN
    fclose(fp);
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
        swap_lot(i, k);
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
                swap_lot(i, j);
            }
        }
    }
}

void swap_lot(int i, int j) {
   int tmp = lot[i];
   lot[i] = lot[j];
   lot[j] = tmp;
}

// Random But No Repeat
// Adapted algorithm: pencil-and-paper method (modern approach)
// reference:
//   https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#Modern_method
