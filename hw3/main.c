#include <stdio.h>  // printf
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    int receipt_id;
    int receipt_price;
    char receipt_time[32];
    int lotto_set[5][7];
} lotto_record_t;


int main() {
    srand((unsigned) time(NULL));  // random seed

    time_t ct;       // current time
    char ct_str[80]; // current time: formatted string
    int n;           // # of tickets
    FILE* fp_txt;    // file pointer to lotto[*].txt
    FILE* fp_bin;    // file pointer to record.bin

    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &n);

    if (n) {
        
    }
    time(&curtime);
    ctime(&curtime);
}
