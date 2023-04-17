#include <stdio.h>

#define SYSMEM 10   // managed system memory size
//#define DEBUG     // for generating debug messages

int* my_calloc(int n, int size);
void mem_status(void);
void my_free(int* p);
typedef struct my_mm {  // unlike function, there's no prototype for strcut
    char m[SYSMEM];  // memory space status: 0: free, 1: allocated
    int* p[SYSMEM];  // pointer to the allocated memory
    int i[SYSMEM];   // index of the allocated memory
    int n[SYSMEM];   // number of elements allocated
} my_mm_t;
int g_mem[SYSMEM];   // managed system memory space
my_mm_t mms;

int main() {
    int* np1 = my_calloc(1, 1);
    int* np2 = my_calloc(1, 2);
    int* np3 = my_calloc(1, 3);
    int* np4 = my_calloc(1, 4);
    my_free(np1);
    my_free(np4);
    int* np5 = my_calloc(1, 5);
    int* np6 = my_calloc(1, 1);
    #ifdef DEBUG
        int* np7 = my_calloc(1, 3); // this should succeed
        int* np8 = my_calloc(1, 5); // this should fail
        my_free(np1); // this should succeed because np1 has the same address as np7
        my_free(np1); // this should fail because np1 has been freed
    #endif
    return 0;
}

int* my_calloc(int n, int size) {
    int cnt = 0, start = 0;
    for (int i=0; i<SYSMEM; i++) { // find the first free block of n*size
        if (mms.m[i] == 0) {
            if (cnt == 0) {
                start = i; // record the start index of the free block
            }
            cnt++; // commulative count of free blocks
            if (cnt == n*size) { // if the size of free block meets the requirement
                for (int i=start; i<start+n*size; i++) {
                    mms.m[i] = 1; // mark the block as allocated
                }
                for (int i=0; i<SYSMEM; i++) {    // find the first empty slot in p[]
                    if (mms.p[i] == NULL) {
                        mms.p[i] = &g_mem[start]; // record the pointer to the allocated memory
                        mms.i[i] = start;         // record the index of the allocated memory
                        mms.n[i] = n*size;        // record the number of elements allocated
                        break;  // this break is critical, otherwise, the following mms.p[] will be overwritten
                    }
                }
                for (int i=0; i<n*size; i++) {    // my_calloc() shall initialize as calloc() does
                    g_mem[start+i] = 0; // initialize the allocated memory to 0
                }
                mem_status(); // print the memory status
                #ifdef DEBUG
                    printf(" address = %p, allocated %d bytes", &g_mem[start], n*size);
                #endif
                printf("\n");
                return &g_mem[start];
            }
        } else { // if allocation succeed, reseting cnt shall not be executed
            cnt = 0;
        }
    }
    mem_status(); // print the memory status
    printf(" <- Out of space\n");
    return NULL;
}

void mem_status(void) {
    for (int i=0; i<SYSMEM; i++) {
        printf("%d", mms.m[i]);
    }
}

void my_free(int *p) {
    for (int i=0; i<SYSMEM; i++) {
        #ifdef DEBUG
            printf("i = %d, p = %p, mms.p[i] = %p\n", i, p, mms.p[i]);
        #endif
        if (mms.p[i] == p) {
            mms.p[i] = NULL; // clear the record of pointer to the allocated memory
            #ifdef DEBUG
                printf("i = %d, mms.p[i] = %p matched, and is cleared to %p\n", i, p, mms.p[i]);
            #endif
            for (int j=0; j<mms.n[i]; j++) {
                mms.m[mms.i[i]+j] = 0; // reset the memory status
            }
            mem_status(); // print the memory status
            #ifdef DEBUG
                printf(" address = %p, freed %d bytes", p, mms.n[i]);
            #endif
            mms.n[i] = 0; // clear the record of number of elements allocated
            mms.i[i] = 0; // clear the record of index of the allocated memory
            printf("\n");
            return;
        }
    }
    mem_status(); // print the memory status
    printf(" %p Invalid pointer\n", p);
}
