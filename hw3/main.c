#include <stdio.h>  // printf, fprintf, fseek, ftell
#include <stdlib.h> // 
#include <time.h>   // time, ctime
#include <string.h> // strcpy

// macro
#define RECORD "record.bin"

#define MAXLOT 69   // max possible lot number in a set
#define SPLOT 10    // max possible special lot number in a set
#define NORMAL 6    // # of normal lot numbers in a set
#define MAX_GEN 5   // # of sets of lot numbers

#define ASK_LOT_SETS 1

// struct
typedef struct {
    int receipt_id;
    int receipt_price;
    char receipt_time[32];
    int lotto_set[5][7];
} lotto_record_t;

// function prototypes
int query(int instruction);             // query info from user
int procf(FILE* fp, int instruction,    // read/write file data
          int lotto_record_size,
          lotto_record_t lottos[]);


int main() {
    srand((unsigned) time(NULL));  // random seed

    time_t ct;                  // current time
    char ct_str[80];            // current time: formatted string
    int n = 1;                  // # of sets (1-5)
    lotto_record_t lottos[100]; // # of tickets (max 5 sets per ticket)
    FILE* fp_txt;               // file pointer to lotto[*].txt
    FILE* fp_bin;               // file pointer to record.bin

    fprintf(stdout, "歡迎光臨長庚樂透彩購買機台\n");
    if (n = query(ASK_LOT_SETS)) {
        if () {
            
            fclose(fp_bin); 
        } else {
            if (!(fp_bin = fopen(RECORD, "wb"))) {
                fprintf(stderr, "無法建立檔案 %s\n", RECORD);
                exit(1);
            }
            fseek(fp, 0, SEEK_END);
            int size = ftell(fp);
            if (size % sizeof(lotto_record_t) != 0) {
                fprintf(stderr, RECORD" 檔案損毀，重建已購買資料庫。\n");
            }
        }
    }
    time(&curtime);
    ctime(&curtime);
}

int query(int instruction) {
    switch (instruction) {
    case 1:
        int n;
        fprintf(stdout, "請問您要買幾組樂透彩：");
        while (1) {
            signed char flag = scanf("%d", &n);
            if (flag < 0 || n < 0 || n > 5) {
                fprintf(stderr, "請輸入數字 1 到 5 以決定要購買的彩券組數\n");
                continue;
            }
            if (flag == 0) {
                fprintf(stderr, "您沒有輸入數字，預設為您購買 1 組樂透彩。\n");
                n = 1;
                break;
            }
            if (n >= 0 && n <= 5) {
                break;
            }
        }
        return n;
        break;
    default:
        return 0;
        break;
    }
}

int promptf(FILE* fp, int instruction,
            int lotto_record_size,
            lotto_record_t lottos[]) {
    switch (instruction) {
    case 1:
        if (fp = fopen())
    }
}
