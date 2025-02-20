#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "FEN_TEST.h"

#define NAME "Optichess 1.0"
#define BOARD_SQ_NUM 120

#define TRUE 1
#define FALSE 0

#define MAXMOVES 2048
#define MAXPOSITIONALMOVES 256  // Max no. of moves at a given position.


typedef unsigned long long U64;

enum PIECELIST {EMPTY = 0, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};
enum ROWS{ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8, ROW_NONE};
enum COLS{COL_A, COL_B, COL_C, COL_D, COL_E, COL_F, COL_G, COL_H, COL_NONE};
enum COLOUR {WHITE, BLACK, BOTH, NONE};
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
    int move;
    int score;
} S_MOVE;


/*
    Move Representation (24bits)
    CastleFlag  PromotedPiece PawnStart EnPassantFlag  CapturedPiece  To          From
    (1bit)      (4bits)       (1bit)    (1bit)         (4bits)       (7bits)     (7bits)
                0000 0000 0000 0000 0000 0000 
    For reference
    0-6 -> From
    7-13 -> To
    14->17-> Captured Piece
    18 -> EnPassantFlag
    19 -> Pawn Start Flag
    20-23 -> Promoted Piece
    24 ->Castle Flag
*/

typedef struct {
    S_MOVE moves[MAXPOSITIONALMOVES];
    int move_count;
} S_MOVELIST;

typedef struct {
    int move;
    int castlePerm;
    int enPas;
    int fiftyMoveCounter;
    U64 posKey;
} S_UNDO;

typedef struct {
    int board[BOARD_SQ_NUM]; // 120 sq board;
    U64 piece[13];        // holds position of every piece in a 64 bit integer
    int pieceNum[13]; // holds number of pieces at any given time
    int pceSqList[13][10];  // holds the square of every piece on the board
    int currSideToPlay;
    int enPas;
    int fiftyMoveCounter;
    int fullmoveNumber;
    int ply;
    int hisPly;
    U64 posKey; // UID hashkey for each move in the game, useful for detecting repetition. 
    int castlePerm;
    // S_UNDO history[MAXMOVES];

} S_BOARD;

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define RCToSQ(Row, Col) ((21 + Row) + (Col * 10)) // Given Row and Col to 120 indexed board
#define SQUARE_MASK(sq) (1ULL << (sq))
#define RAND_64 ((U64)rand() | (U64)rand() << 15 | (U64)rand() << 30 | (U64)rand() << 45 | ((U64)rand() &0xf) << 60)
#define OFFBOARD(sq) ((Board120To64[sq] == 120) ? TRUE : FALSE)

/* Move Order MACROS */

#define MOVE_FROM_SQ(m)                     (m & 0x7F)                // From Square (bits 0-6)
#define MOVE_TO_SQ(m)                       ((m >> 7) & 0x7F)         // To Square (bits 7-13)
#define MOVE_CAPTURED_PIECE(m)              ((m >> 14) & 0xF)         // Captured Piece (bits 14-17)
#define MOVE_FLAG_ENPASSANT(m)              (m & 0x40000)             // En Passant Flag (bit 18)
#define MOVE_FLAG_PAWN_START(m)             (m & 0x80000)             // Pawn Start Flag (bit 19)
#define MOVE_PROMOTED_PIECE(m)              ((m >> 20) & 0xF)         // Promoted Piece (bits 20-23)
#define MOVE_FLAG_CASTLE(m)                 (m & 0x1000000)           // Castle Flag (bit 24)


#define SET_MOVE_FLAG_ENPASSANT                 (0x40000)
#define SET_MOVE_FLAG_PAWN_START                (0x80000)
#define SET_MOVE_FLAG_CASTLE                    (0x1000000)


#define SET_MOVE(f, t, ca, pr, fl)          ((f) | ((t) << 7) | ((ca) << 14) | ((pr) << 20) | (fl))

// variables
extern int Board120To64[BOARD_SQ_NUM];
extern int Board64To120[64];
extern const char pieceChar[14];
extern U64 PieceKeys[13][64];
extern U64 SideKey;
extern U64 CastleKeys[16];
extern U64 EnPassant[8];

//debug.c
extern void PrintBoard120To64();
extern void PrintBoard64To120();
extern void PrintHashKeys();
extern void PrintBoard(S_BOARD *brd);
extern void PrintMoveList(const S_MOVELIST *list);
extern const char *PrintSquare(const int sq);
extern void DebugPrintBoard(const S_BOARD *board);

// init.c
extern void AllInit();
extern void InitBoard();
extern void InitHashKeys();

//data.c
extern int PieceToColour[13];

//bitboards.c
extern void SetBit(U64 *bitboard, unsigned int sq);
extern void ClearBit(U64 *bitboard, unsigned int sq);

//poskey.c
extern U64 GeneratePosKey(const S_BOARD *pos);

// board.c
extern int ParseFEN(S_BOARD *state, const char *fen);
extern int ResetBoard(S_BOARD *board, const char *fen);

// attack.c
extern int is_square_attacked(const int sq120, const int colour, const S_BOARD *pos);

//genmove.c
extern void generate_all_moves(S_BOARD *pos, S_MOVELIST *mvlist);
#endif

