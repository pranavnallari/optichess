// init.c
#include "globals.h"

int Board120To64[BOARD_SQ_NUM];
int Board64To120[64];

// hashing keys
U64 PieceKeys[12][64];
U64 SideKey;
U64 EnPassant[8];
U64 CastleKeys[16];

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

   A    B    C    D    E    F    G    H
   21   22   23   24   25   26   27   28    1
   31   32   33   34   35   36   37   38    2
   41   42   43   44   45   46   47   48    3
   51   52   53   54   55   56   57   58    4
   61   62   63   64   65   66   67   68    5
   71   72   73   74   75   76   77   78    6
   81   82   83   84   85   86   87   88    7
   91   92   93   94   95   96   97   98    8 
*/

void InitBoard() {
    for (int i = 0; i < BOARD_SQ_NUM; ++i) Board120To64[i] = 120;
    for (int i = 0; i < 64; ++i) Board64To120[i] = 69;

    int sq120, sq64 = 0;

    for (int col = COL_A; col <= COL_H; ++col) {
        for (int row = ROW_1; row <= ROW_8; ++row) {
            sq120 = RCToSQ(row, col); // getting the 120 indexed square from row and column
            Board120To64[sq120] = sq64;
            Board64To120[sq64] = sq120;
            ++sq64;
        }
    } 
}

void InitHashKeys() {
	for (int piece = 0; piece < 12; ++piece) {
        for (int sq = 0; sq < 64; ++sq) {
            PieceKeys[piece][sq] = RAND_64;
        }
    }
    for (int i = 0; i < 16; ++i) {
        CastleKeys[i] = RAND_64;
    }

    for (int col = COL_A; col <= COL_H; ++col) {
        EnPassant[col] = RAND_64;
    }

    SideKey = RAND_64;
}

void AllInit() {
    InitBoard();
    InitHashKeys();
}