// init.c
#include "globals.h"

int Board120To64[BOARD_SQ_NUM];
int Board64To120[64];

/*

  120  120  120  120  120  120  120  120  120  120
  120  120  120  120  120  120  120  120  120  120
  120    0    1    2    3    4    5    6    7  120
  120    8    9   10   11   12   13   14   15  120
  120   16   17   18   19   20   21   22   23  120
  120   24   25   26   27   28   29   30   31  120
  120   32   33   34   35   36   37   38   39  120
  120   40   41   42   43   44   45   46   47  120
  120   48   49   50   51   52   53   54   55  120
  120   56   57   58   59   60   61   62   63  120
  120  120  120  120  120  120  120  120  120  120
  120  120  120  120  120  120  120  120  120  120


   21   22   23   24   25   26   27   28
   31   32   33   34   35   36   37   38
   41   42   43   44   45   46   47   48
   51   52   53   54   55   56   57   58
   61   62   63   64   65   66   67   68
   71   72   73   74   75   76   77   78
   81   82   83   84   85   86   87   88
   91   92   93   94   95   96   97   98
*/

void InitBoard() {
    for (int i = 0; i < BOARD_SQ_NUM; ++i) Board120To64[i] = 120;
    for (int i = 0; i < 64; ++i) Board64To120[i] = 69;

    int sq120, sq64 = 0;

    for (int col = COL_1; col <= COL_8; ++col) {
        for (int row = ROW_A; row <= ROW_H; ++row) {
            sq120 = RCToSQ(row, col); // getting the 120 indexed square from row and column
            Board120To64[sq120] = sq64;
            Board64To120[sq64] = sq120;
            ++sq64;
        }
    } 
}

void AllInit() {
    InitBoard();
}