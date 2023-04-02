#include <stdio.h>  // printf, fprintf, fseek, ftell, NULL
#include <stdlib.h> // rand, srand, exit
#include <time.h>   // time, ctime
#include <string.h> // strcpy, strlen
#include <limits.h> // INT_MAX

// Settings
#define RECORD "record.bin"
#define TXT "lotto[%05d].txt"

#define LOT_PRICE 100     // price of one set of lotto numbers
                          // min possible lot number is 1
#define MAXLOT 69         // max possible lot number in a set
#define SPLOT 10          // max possible special lot number in a set
#define NORMAL 6          // # of normal lot numbers in a set
#define MAX_GEN 5         // # of sets of lot numbers
#define LOTTO_M 100       // max array size to store RECORD
                          // end users have to buy PRO version for bigger size
#define MAX_WIN 3         // max # of winning numbers for checking
#define MAX_INST 100      // max # of instructions in rw_f()

// Pre-defined Acronyms
#define ASK_LOT_SETS 1    // prompt user: how many sets of numbers?
#define CHK_RECORD 2      // check the existence of RECORD
#define NEW_TICKET 3      // generate a new lotto ticket with TXT and RECORD
#define FILE_SIZE 4       // calculate the file size of RECORD
#define FILE_SIZE_GET 5   // .. retrieve the file size
#define IS_RECORD_VALID 6 // check if RECORD is not corrupted
#define LOAD_RECORD 7     // load RECORD into memory
#define LAST_RECORD 8     // get the last record ID

#define OK 0              // command successfully executed
#define FILE_NOT_EXIST -1 // file does not exist
#define FILE_ERROR -2     // file error
#define TXT_ERROR -3      // TXT error
#define RECORD_ERROR -4   // RECORD error
#define NA -5             // instruction not available
#define FILE_BIG 1        // file size is too big for int

// struct
typedef struct {
    int receipt_id;                     // lotto ticket ID, begins from 1
    int receipt_price;                  // lotto ticket price, 100 per set
    char receipt_time[32];              // lotto ticket purchase time
    int lotto_set[MAX_GEN][NORMAL+1];   // lotto ticket numbers
} lotto_record_t;
static int lotto_record_size = sizeof(lotto_record_t);

// macros
// DUALFORIF: double for loop with if condition, i & j with increment of 1
#define DUALFORIF(IS, IE, JS, JE, CONDITION, CMD)    \
    for (int i = IS; i < IE; i++) {                  \
        for (int j = JS; j < JE; j++) {              \
            if (CONDITION) {                         \
                CMD;                                 \
            }                                        \
        }                                            \
    }                                                \

// FORIF: single for loop with if condition, i with increment of 1
#define FORIF(IS, IE, CONDITION, CMD)                \
    for (int i = IS; i < IE; i++) {                  \
        if (CONDITION) {                             \
            CMD;                                     \
        }                                            \
    }                                                \

// function prototypes
int query(int instruction);             // query info from user
int procf(int instruction);             // file operation
int rw_f(int instruction, lotto_record_t lots[]);   // read/write file data
void format_time(char* str);            // format time string
void swap(int* a, int* b);              // swap two integers
void lot_gen(int* lot);                 // generate a set of lot numbers
int inlist(int* list, int* win);        // check if lot number is in the win list

// main
int main() {
    time_t ct;                       // current time
    char ct_str[80];                 // current time: formatted string
    int n = 1;                       // # of sets (1-MAX_GEN), 0 = manage mode
    lotto_record_t lots[LOTTO_M];    // # of tickets loaded into memory
    
    srand((unsigned) time(NULL));     // random seed

    fprintf(stdout, "歡迎光臨長庚樂透彩購買機台\n");
    if (procf(CHK_RECORD) == OK) {                // if RECORD exists
        switch (procf(IS_RECORD_VALID)) {         // if RECORD is valid
            case OK:
                rw_f(LOAD_RECORD, lots);          // load it into memory
                break;
            case RECORD_ERROR:
                fprintf(stderr, "檔案 "RECORD" 已損毀，請聯絡系統管理員。\n");
                exit(1);  // exit program because no solution available
            case FILE_BIG:
                fprintf(stderr, "檔案 "RECORD" 過大，超出設計，請聯絡系統管理員。\n");
                exit(2);  // exit program because no solution available
            default:
                fprintf(stderr, "未知錯誤，請聯絡系統管理員。\n");
                exit(3);  // exit program because no solution available
        }
    }
    if (n = query(ASK_LOT_SETS)) {   // n is regulated (0 <= n <= 5)
        switch (rw_f(NEW_TICKET + n*MAX_INST, lots)) { // generate new ticket
            case OK:
                int ticket_no = rw_f(LAST_RECORD, lots)+1;
                printf("已為您購買的 %d 組樂透組合輸出至 "TXT"\n", n, ticket_no);
                break;
            case RECORD_ERROR:
                fprintf(stderr, "無法正確建立檔案 " RECORD "\n");
                exit(4); // exit program because no solution available
            case TXT_ERROR:
                fprintf(stderr, "無法正確建立檔案 " TXT "\n", ticket_no);
                exit(5); // exit program because no solution available
            default:
                fprintf(stderr, "未知錯誤，請聯絡系統管理員。\n");
                exit(6); // exit program because no solution available
        }
    } else if (n == 0) { // manage mode
        int ticket_no = rw_f(LAST_RECORD, lots) + 1;
        if (ticket_no == 1) {
            fprintf(stdout, "目前尚無任何購買紀錄。\n");
            return 0;
        }
        fprintf(stdout, "請輸入中獎號碼 (最多三個)：");
        int win[MAX_WIN+1] = {0};
        for (int i = 0; i < MAX_WIN; i++) {
            scanf("%d", &win[i]);
            char c = getchar();
            if (c == '\n') {
                win[MAX_WIN] = i+1; // # of winning numbers
                break;
            }
        }
        fprintf(stdout, "輸入中獎號碼為：");
        for (int i = 0; i < MAX_WIN; i++) {
            if (win[i] != 0) {
                fprintf(stdout, "%02d ", win[i]);
            } else {
                break;
            }
        }
        fprintf(stdout, "\n");
        fprintf(stdout, "以下為中獎彩券：\n");
        for (int i = 0; i < ticket_no; i++) {
            int lastwinticket = -1;
            for (int j = 0; j < MAX_GEN; j++) {
                if (inlist(lots[i].lotto_set[j], win)) {
                    if (lastwinticket != i) {
                        lastwinticket = i;
                        fprintf(stdout, "彩券 No. %d\n", lots[i].receipt_id);
                        fprintf(stdout, "售出時間：%s\n", lots[i].receipt_time);
                    }
                    for (int k = 0; k < NORMAL+1; k++) {
                        fprintf(stdout, "%02d ", lots[i].lotto_set[j][k]);
                    }
                    fprintf(stdout, "\n");
                }
            }
        }
    }
    return 0;
}

int query(int instruction) { // query info from user
    switch (instruction) {
    case ASK_LOT_SETS: // prompt user: how many sets of numbers?
        int n = 0;
        fprintf(stdout, "請問您要買幾組樂透彩：");
        scanf("%d", &n);
        return n;
    default:
        return NA; // no instruction matched, simply do nothing
    }
}

int procf(int instruction) { // file operation (read metadata)
    static FILE* fp;
    static long size = 0; // for FILE_SIZE_GET
    switch (instruction) {
        case CHK_RECORD: // check if RECORD exists
            fp = fopen(RECORD, "rb");
            return (fp ? fclose(fp), OK : FILE_NOT_EXIST);
        case IS_RECORD_VALID: // check if RECORD is valid by file size
        case FILE_SIZE: // calculate file size, and store it in 'size'
            fp = fopen(RECORD, "rb");
            fseek(fp, 0, SEEK_END);
            size = ftell(fp);
            fclose(fp);
            if (instruction == FILE_SIZE) {
                return OK;
            } else {    // file size must be multiple of lotto_record_size
                if (size % lotto_record_size) {
                    return RECORD_ERROR;
                } else {
                    return (size < INT_MAX ? OK : FILE_BIG);
                }
            }
            break;
        case FILE_SIZE_GET: // return file size in type int
            return (int) size;
        default:
            return NA; // unknown instruction
    }
}

int rw_f(int instruction, lotto_record_t lots[]) {
    static FILE* fp;
    static int lastrec = 0;       // last record ID, for LOAD_RECORD
    static int lot[MAXLOT] = {0}; // one set of lot numbers
    static int run_once = 1;      // only run once indicator, for NEW_TICKET
    int n = instruction / MAX_INST;   // for hybrid instruction
    switch (instruction % MAX_INST) {
        case LAST_RECORD:
            return lastrec;
        case NEW_TICKET:
            char str[80];
            int j;
            lots[lastrec].receipt_id = lastrec+1;
            lots[lastrec].receipt_price = n * LOT_PRICE;
            sprintf(str, "lotto[%05d].txt", lastrec+1);
            if ((fp = fopen(str, "w")) == NULL) {
                return TXT_ERROR;
            }
            fprintf(fp, "========= lotto649 =========\n");
            fprintf(fp, "========+ No.%05d +========\n", lastrec+1);
            format_time(str);
            strcpy(lots[lastrec].receipt_time, str);
            fprintf(fp, "= %s =\n", str);
            if (run_once) {
                run_once = 0;
                for (int i = 0; i < MAXLOT; i++) { // initialize lot[]
                    lot[i] = i + 1;
                }
            }
            for (int i = 0; i < MAX_GEN; i++) { // print lot[] and store it
                lot_gen(lot); // generate lot[]
                fprintf(fp, "[%1d]: ", i+1);
                if (i < n) {
                    for (int j = 0; j < NORMAL; j++) {
                        fprintf(fp, "%02d ", lot[j]);
                        lots[lastrec].lotto_set[i][j] = lot[j];
                    }
                    fprintf(fp, "%02d\n", lot[NORMAL]);
                    lots[lastrec].lotto_set[i][NORMAL] = lot[NORMAL];
                } else {
                    for (int j = 0; j < NORMAL; j++) {
                        fprintf(fp, "-- ");
                    }
                    fprintf(fp, "--\n");
                }
            }
            fprintf(fp, "========= csie@CGU =========\n");
            fclose(fp);
            fp = fopen(RECORD, "ab");
            fwrite(&lots[lastrec], lotto_record_size, 1, fp);
            fclose(fp);
            return OK;
        case LOAD_RECORD:
            fp = fopen(RECORD, "rb");
            for (int i = 0; i < LOTTO_M; i++) {
                if (fread(&lots[i], lotto_record_size, 1, fp) == 0) {
                    lastrec = i;
                    break;
                }
            }
            fclose(fp);
            return OK;
        default:
            return NA; // unknown instruction
    }
}

void format_time(char* str) { // format time string
    time_t ct; // current time
    time(&ct);
    strcpy(str, ctime(&ct));
    str[strlen(str)-1] = '\0'; // remove '\n' at the end
}

void swap(int* a, int* b) { // swap two integers
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void lot_gen(int* lot) { // generate lot[]
    for (int i = MAXLOT-1; i>0; i--) { // shuffle lot[]
        swap(&lot[i], &lot[rand() % (i+1)]);
    }
    DUALFORIF(0, NORMAL, i+1, NORMAL, lot[i] > lot[j], swap(&lot[i], &lot[j]));
    FORIF(NORMAL, MAXLOT, lot[i] <= SPLOT, swap(&lot[i], &lot[NORMAL]));
}

int inlist(int* list, int* win) { // check if list[] is in win[]
    DUALFORIF(0, NORMAL+1, 0, win[MAX_WIN], list[i] == win[j], return 1);
    return 0;
}
