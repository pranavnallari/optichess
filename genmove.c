// genmove.c

#include "globals.h"

const int PceDir[13][8] = {
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ 0, 0, 0, 0, 0, 0, 0 },
	{ -8, -19,	-21, -12, 8, 19, 21, 12 },
	{ -9, -11, 11, 9, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, 0, 0, 0, 0 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 },
	{ -1, -10,	1, 10, -9, -11, 11, 9 }
};

const int NumDir[13] = {
    0, 0, 8, 4, 4, 8, 8, 0, 8, 4, 4, 8, 8
   };

static void add_normal_move(const S_BOARD *pos, int move, S_MOVELIST *list) {
    list->moves[list->move_count].move = move;
    list->moves[list->move_count].score = 0;
    list->move_count++;
}

static void add_capture_move(const S_BOARD *pos, int move, S_MOVELIST *list) {
    list->moves[list->move_count].move = move;
    list->moves[list->move_count].score = 0;
    list->move_count++;
}

static void add_enpassant_move(const S_BOARD *pos, int move, S_MOVELIST *list) {
    list->moves[list->move_count].move = move;
    list->moves[list->move_count].score = 0;
    list->move_count++;
}

static void add_pawn_normal_move(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list, int side) {
    int row = (from / 10) - 2;
    if (side == WHITE) {
        if (row == ROW_7) {
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, wQ, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, wR, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, wB, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, wN, 0), list);
        } else {
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, EMPTY, 0), list);
        }
    } else if (side == BLACK) {
        if (row == ROW_2) {
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, bQ, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, bR, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, bB, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, bN, 0), list);
        } else {
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, EMPTY, 0), list);
        }
    }
}


static void add_pawn_capture_move(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list, int side) {
    int row = (from / 10) - 2;
    if (side == WHITE) {
        if (row == ROW_7) {
            add_capture_move(pos, SET_MOVE(from, to, cap, wR, 0), list);
            add_capture_move(pos, SET_MOVE(from, to, cap, wB, 0), list);
            add_capture_move(pos, SET_MOVE(from, to, cap, wN, 0), list);
            add_capture_move(pos, SET_MOVE(from, to, cap, wQ, 0), list);
        } else {
            add_capture_move(pos, SET_MOVE(from, to, cap, EMPTY, 0), list);
        }
    } else if (side == BLACK) {
        if (row == ROW_2) {
            add_capture_move(pos, SET_MOVE(from, to, cap, bQ, 0), list);
            add_capture_move(pos, SET_MOVE(from, to, cap, bR, 0), list);
            add_capture_move(pos, SET_MOVE(from, to, cap, bB, 0), list);
            add_capture_move(pos, SET_MOVE(from, to, cap, bN, 0), list);
        } else {
            add_capture_move(pos, SET_MOVE(from, to, cap, EMPTY, 0), list);
        }
    }
}

int LoopSlidePce[8] = {wB, wR, wQ, 0, bB, bR, bQ, 0};
int LoopNonSlidePce[6] = {wN, wK, 0, bN, bK, 0};

int LoopSlideColInd[2] = {0, 4};
int LoopNonSlideColInd[2] = {0, 3};


void generate_all_moves(S_BOARD *pos, S_MOVELIST *mvlist) {
    mvlist->move_count = 0;
    int side = pos->currSideToPlay;
    int sq = 0;
    if (side == WHITE) {
        for (int i = 0; i < pos->pieceNum[wP]; ++i) {
            sq = pos->pceSqList[wP][i];
            if (pos->board[sq + 10] == EMPTY) {
                add_pawn_normal_move(pos, sq, sq + 10, mvlist, WHITE);
                if (((sq / 10) - 2) == ROW_2 && pos->board[sq+20] == EMPTY) {
                    add_normal_move(pos, SET_MOVE(sq, (sq+20), EMPTY, EMPTY, SET_MOVE_FLAG_PAWN_START), mvlist);
                }
            }
            if (!OFFBOARD(sq + 9) && PieceToColour[pos->board[sq+9]] == BLACK) {
                add_pawn_capture_move(pos, sq, sq + 9, pos->board[sq+9], mvlist, WHITE);
            }
            if (!OFFBOARD(sq + 11) && PieceToColour[pos->board[sq+11]] == BLACK) {
                add_pawn_capture_move(pos, sq, sq + 11, pos->board[sq+11], mvlist, WHITE);
            }
            if (pos->enPas != NO_SQ) {
                if (sq + 9 == pos->enPas) {
                    add_enpassant_move(pos, SET_MOVE(sq, sq + 9, EMPTY, EMPTY, SET_MOVE_FLAG_ENPASSANT), mvlist);
                }
                if (sq + 11 == pos->enPas) {
                    add_enpassant_move(pos, SET_MOVE(sq, sq + 11, EMPTY, EMPTY, SET_MOVE_FLAG_ENPASSANT), mvlist);
                }
            }
        }
    } else {
        for (int i = 0; i < pos->pieceNum[bP]; ++i) {
            sq = pos->pceSqList[bP][i];
            
            if (pos->board[sq - 10] == EMPTY) {
                add_pawn_normal_move(pos, sq, sq - 10, mvlist, BLACK);
                if (((sq / 10) - 2) == ROW_7 && pos->board[sq-20] == EMPTY) {
                    add_normal_move(pos, SET_MOVE(sq, (sq-20), EMPTY, EMPTY, SET_MOVE_FLAG_PAWN_START), mvlist);
                }
            }

            if (!OFFBOARD(sq - 9) && PieceToColour[pos->board[sq-9]] == WHITE) {
                add_pawn_capture_move(pos, sq, sq - 9, pos->board[sq-9], mvlist, BLACK);
            }
            if (!OFFBOARD(sq - 11) && PieceToColour[pos->board[sq-11]] == WHITE) {
                add_pawn_capture_move(pos, sq, sq - 11, pos->board[sq-11], mvlist, BLACK);
            }

            if (pos->enPas != NO_SQ) {
                if (sq - 9 == pos->enPas) {
                    add_enpassant_move(pos, SET_MOVE(sq, sq - 9, EMPTY, EMPTY, SET_MOVE_FLAG_ENPASSANT), mvlist);
                }
                if (sq - 11 == pos->enPas) {
                    add_enpassant_move(pos, SET_MOVE(sq, sq - 11, EMPTY, EMPTY, SET_MOVE_FLAG_ENPASSANT), mvlist);
                }
            }
        }
    }

    // loop all sliding pieces
    int pceInd = LoopSlideColInd[side];
    int piece = LoopSlidePce[pceInd++];
    int dir = 0;
    int to_sq = NO_SQ;
    while (piece != 0) {
        for (int i = 0; i < pos->pieceNum[piece]; ++i) {
            sq = pos->pceSqList[piece][i];
            for (int ind = 0; ind < NumDir[piece]; ++ind) {
                dir = PceDir[piece][ind];
                to_sq = sq + dir;

                while (!OFFBOARD(to_sq)) {
                    if (pos->board[to_sq] != EMPTY) {
                        if (PieceToColour[pos->board[to_sq]] == (side ^ 1)) {
                            add_capture_move(pos, SET_MOVE(sq, to_sq, pos->board[to_sq], EMPTY, 0), mvlist);
                        }
                        break;
                    }
                    add_normal_move(pos, SET_MOVE(sq, to_sq, EMPTY, EMPTY, 0), mvlist);
                    to_sq += dir;
                }
            }
        }

        piece = LoopSlidePce[pceInd++];
    }
    // loop all non sliding pieces
    pceInd = LoopNonSlideColInd[side];
    piece = LoopNonSlidePce[pceInd++];
    while (piece != 0) {    
        for (int i = 0; i < pos->pieceNum[piece]; ++i) {
            sq = pos->pceSqList[piece][i];
            for (int ind = 0; ind < NumDir[piece]; ++ind) {
                dir = PceDir[piece][ind];
                to_sq = sq + dir;

                if (OFFBOARD(to_sq)) continue;

                if (pos->board[to_sq] != EMPTY) {
                    if (PieceToColour[pos->board[to_sq]] == (side ^ 1)) {
                        add_capture_move(pos, SET_MOVE(sq, to_sq, pos->board[to_sq], EMPTY, 0), mvlist);
                    }
                    continue;
                }
                add_normal_move(pos, SET_MOVE(sq, to_sq, EMPTY, EMPTY, 0), mvlist);
            }
        }
        piece = LoopNonSlidePce[pceInd++];
    }

    // special moves (castling)
    if (pos->castlePerm & WKCA) {
        if (pos->board[F1] == EMPTY && pos->board[G1] == EMPTY) {
            if (!is_square_attacked(E1, BLACK, pos) && !is_square_attacked(F1, BLACK, pos)) {
                add_normal_move(pos, SET_MOVE(E1, G1, EMPTY, EMPTY, SET_MOVE_FLAG_CASTLE), mvlist);
            }
        }
    }

    if (pos->castlePerm & WQCA) {
        if (pos->board[D1] == EMPTY && pos->board[C1] == EMPTY && pos->board[B1] == EMPTY) {
            if (!is_square_attacked(E1, BLACK, pos) && !is_square_attacked(D1, BLACK, pos)) {
                add_normal_move(pos, SET_MOVE(E1, C1, EMPTY, EMPTY, SET_MOVE_FLAG_CASTLE), mvlist);
            }
        }
    }

    if (pos->castlePerm & BKCA) {
        if (pos->board[F8] == EMPTY && pos->board[G8] == EMPTY) {
            if (!is_square_attacked(E8, WHITE, pos) && !is_square_attacked(F8, WHITE, pos)) {
                add_normal_move(pos, SET_MOVE(E8, G8, EMPTY, EMPTY, SET_MOVE_FLAG_CASTLE), mvlist);
            }
        }
    }

    if (pos->castlePerm & BQCA) {
        if (pos->board[D8] == EMPTY && pos->board[C8] == EMPTY && pos->board[B8] == EMPTY) {
            if (!is_square_attacked(E8, WHITE, pos) && !is_square_attacked(D8, WHITE, pos)) {
                add_normal_move(pos, SET_MOVE(E8, C8, EMPTY, EMPTY, SET_MOVE_FLAG_CASTLE), mvlist);
            }
        }
    }
}



