#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// program parameters
#define MAXLOT 69    // max lottery number
#define SPLOT 10     // max special lottery number
                     // lottery number must begin with 1
#define NORMAL 6     // how many normal lot number
                     // only 1 special lot number allowed
#define MAX_GEN 5    // max lot number tuples to be generated
#define LOTTO_M 100

// global variables
int lot[MAXLOT];     // lottery tickets

// function prototypes
void init_lot(void); // initialize lot[]
void shuf_lot(void); // shuffle the lot[]
void sort_lot(void); // sort the first NORMAL lot numbers
void swap_lot(int i, int j); // swap the i and j elements of lot[]
int sp_lot(void);    // find the special number

// struct
typedef struct {
    int receipt_id;
    int receipt_price;
    char receipt_time[32];
    int lotto_set[5][7];
} lotto_record_t;

// main()
int main(int argc, char* argv[]) {
    srand((unsigned) time(NULL)); // random seed

    time_t curtime;
    char time_str[80];  // string buffer to store current time
    int n;              // how many tuples of lot to buy?
    FILE* fp;
    FILE* ftxt;
    int last_rec = -1;
    int ticket_no = 0;
    char TXT[80];
    lotto_record_t lottos[LOTTO_M];
    
    printf("歡迎光臨長庚樂透彩購買機台\n");
    fp = fopen("record.bin", "rb");
    if (fp) {
        for (int i=0; i<LOTTO_M; i++) {
            int c = fread(&lottos[i], sizeof(lotto_record_t), 1, fp);
            if (!c) {
                last_rec = i - 1;
                break;
            }
        }
        fclose(fp);
        ticket_no = lottos[last_rec].receipt_id;
        fp = fopen("record.bin", "ab");
    } else {
        fp = fopen("record.bin", "wb");
    }
    ticket_no++;
    sprintf(TXT, "lotto[%05d].txt", ticket_no);
    
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &n);
    lottos[last_rec+1].receipt_id = ticket_no;
    lottos[last_rec+1].receipt_price = n * 100;
    printf("已為您購買的 %d 組樂透組合輸出至 lotto[%05d].txt\n", n, ticket_no);

    ftxt = fopen(TXT, "w");
    fprintf(ftxt, "========= lotto649 =========\n");

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
    fprintf(ftxt, "========+ No.%05d +========\n", ticket_no);
    fprintf(ftxt, "= %s =\r\n", time_str);
    strcpy(lottos[last_rec+1].receipt_time, time_str);

    init_lot();  // initialize the lot[] array

    for (int i=0; i<MAX_GEN; i++) {
        shuf_lot(); // shuffle lot[] array
        sort_lot(); // sort the first MAXLOT elements in lot[]
        fprintf(ftxt, "[%1d]: ",i+1);
        for (int j=0; j<NORMAL; j++) {
            if (i<n) {
                fprintf(ftxt, "%02d ", lot[j]);
                lottos[last_rec+1].lotto_set[i][j] = lot[j];
            } else {
                fprintf(ftxt, "-- ");
                lottos[last_rec+1].lotto_set[i][j] = 0;
            }
        }
        if (i<n) {
            int splot = sp_lot();
            fprintf(ftxt, "%02d\n", splot);
            lottos[last_rec+1].lotto_set[i][NORMAL] = splot;
        } else {
            fprintf(ftxt, "--\n");
        }
    }
    fwrite(&lottos[last_rec+1], sizeof(lottos[0]), 1, fp);
    fclose(fp);

    fprintf(ftxt, "========= cise@CGU =========\n");
    fclose(ftxt);
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
