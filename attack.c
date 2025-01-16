// attack.c

#include "globals.h"
// all directions of pieces
const int KnDir[8] = {-8, -19, -21, -12, 8, 19, 21, 12};
const int RkDir[4] = {-1, -10, 1, 10};
const int BiDir[4] = {-9, -11, 11, 9};
const int KiDir[8] = {-1, -10, 1, 10, -9, -11, 11, 9};

int is_square_attacked(const int sq120, const int colour, const S_BOARD *pos) {
    // Pawns
    if (colour == WHITE) {
        if (pos->board[sq120 - 11] == wP || pos->board[sq120 - 9] == wP) {
            return TRUE;
        }
    } else {
        if (pos->board[sq120 + 11] == bP || pos->board[sq120 + 9] == bP) {
            return TRUE;
        }
    }

    // Knights
    for (int i = 0; i < 8; ++i) {
        if (pos->board[sq120 + KnDir[i]] == wN && colour == WHITE) return TRUE;
        else if (pos->board[sq120 + KnDir[i]] == bN && colour == BLACK) return TRUE;
    }

    // Bishop/Queen
    for (int i = 0; i < 4; ++i) {
        int dir = BiDir[i];
        int curr_sq = sq120;
        int piece = EMPTY;
        while (!OFFBOARD(curr_sq)) {
            if (colour == WHITE && (piece == wB || piece == wQ)) return TRUE;
            else if (colour == BLACK && (piece == bB || piece == bQ)) return TRUE;
            if (piece != EMPTY) break;
            curr_sq += dir;
            piece = pos->board[curr_sq];
        }
    }


    // Rook/Queen
    for (int i = 0; i < 4; ++i) {
        int dir = RkDir[i];
        int curr_sq = sq120;
        int piece = EMPTY;
        while (!OFFBOARD(curr_sq)) {
            if (colour == WHITE && (piece == wR || piece == wQ)) return TRUE;
            else if (colour == BLACK && (piece == bR || piece == bQ)) return TRUE;
            if (piece != EMPTY) break;
            curr_sq += dir;
            piece = pos->board[curr_sq];
        }
    }

    // King
    for (int i = 0; i < 8; ++i) {
        if (pos->board[sq120 + KiDir[i]] == wK && colour == WHITE) return TRUE;
        else if (pos->board[sq120 + KiDir[i]] == bK && colour == BLACK) return TRUE;
    }
    
    return FALSE;


}