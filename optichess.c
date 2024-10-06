// main.c
#include "globals.h"

int main(void) {
    AllInit();
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (i % 10 == 0) printf("\n");
        printf("%5d",  Board120To64[i]);
    }
    printf("\n\n");
    for (int i = 0; i < 64; ++i) {
        if (i % 8 == 0)  printf("\n");
        printf("%5d", Board64To120[i]);
    }
    printf("\n");
    return 0;
}
    