#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME "Optichess 1.0"
#define BOARD_SQ_NUM 120

#define MAXMOVES 2048

typedef unsigned long long U64;

enum PIECES {ALL, Pawn, Knight, Bishop, Rook, Queen, King};
enum ROWS{ROW_A, ROW_B, ROW_C, ROW_D, ROW_E, ROW_F, ROW_G, ROW_H, ROW_NONE};
enum COLS{COL_1 , COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8, COL_NONE};
enum COLOUR {WHITE, BLACK, BOTH};
enum CASTLE {WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8}; // 4 bit number -> BQCA BKCA WQCA WKCA
enum SQUARES {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,    
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
};

/*
    piece[ALL....King][WHITE...BOTH];
*/

typedef struct {
    int move; // move like NF3, QC2, etc.... I might just store the fen to make it easier. Will see
    int castlePerm;
    int enPas;
    int fiftyMoveCounter;
    U64 posKey;
} S_UNDO;

typedef struct {
    int board[BOARD_SQ_NUM]; // 120 sq board;
    U64 piece[7][3];        // holds position of every piece in a 64 bit integer
    int pieceNum[7][3]; // holds number of pieces
    int currSideToPlay;
    int enPas;
    int fiftyMoveCounter;
    int ply;
    int hisPly;
    U64 posKey;
    int castlePerm;
    S_UNDO history[MAXMOVES];

} S_BOARD;

#define RCToSQ(Row, Col) ((21 + Row) + (Col * 10)) // Given Row and Col to 120 indexed board

extern int Board120To64[BOARD_SQ_NUM];
extern int Board64To120[64];


// init.c
extern void AllInit();
extern void InitBoard();


#endif

