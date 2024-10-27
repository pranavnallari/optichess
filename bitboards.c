// bitboards.c

#include "globals.h"

typedef U64 BB; // local reference to one BitBoard

/*
    H8 G8 F8 E8 D8 C8 B8 A8 H7 .. ..... .... H1 G1 F1 E1 D1 C1 B1 A1
    63 62                                                    2  1  0
    MSB                                                           LSB
*/
// example SetBit(board, A4) where A4 = 51
void SetBit(BB *bitboard, unsigned int sq) {
    // set the square in that board
    if (sq >= 120) return; // invalid index
    int shift = Board120To64[sq];
    if (shift == 120) return; // Off board square
    *bitboard |= SQUARE_MASK(shift);
}


void ClearBit(BB *bitboard, unsigned int sq) {
    // clear the square in that board
    if (sq >= 120) return;
    int shift = Board120To64[sq];
    if (shift == 120) return;
    *bitboard &= ~SQUARE_MASK(shift);
}