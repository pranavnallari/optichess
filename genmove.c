// genmove.c

#include "globals.h"


void add_normal_move(const S_BOARD *pos, int move, S_MOVELIST *list) {
    list->moves[list->move_count].move = move;
    list->moves[list->move_count].score = 0;
    list->move_count++;
}

void add_capture_move(const S_BOARD *pos, int move, S_MOVELIST *list) {
    list->moves[list->move_count].move = move;
    list->moves[list->move_count].score = 0;
    list->move_count++;
}

void add_enpassant_move(const S_BOARD *pos, int move, S_MOVELIST *list) {
    list->moves[list->move_count].move = move;
    list->moves[list->move_count].score = 0;
    list->move_count++;
}

void add_pawn_normal_move(const S_BOARD *pos, const int from, const int to, S_MOVELIST *list, int side) {
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


void add_pawn_capture_move(const S_BOARD *pos, const int from, const int to, const int cap, S_MOVELIST *list, int side) {
    int row = (from / 10) - 2;
    if (side == WHITE) {
        if (row == ROW_7) {
            add_normal_move(pos, SET_MOVE(from, to, cap, wQ, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, cap, wR, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, cap, wB, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, cap, wN, 0), list);
        } else {
            add_normal_move(pos, SET_MOVE(from, to, EMPTY, EMPTY, 0), list);
        }
    } else if (side == BLACK) {
        if (row == ROW_2) {
            add_normal_move(pos, SET_MOVE(from, to, cap, bQ, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, cap, bR, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, cap, bB, 0), list);
            add_normal_move(pos, SET_MOVE(from, to, cap, bN, 0), list);
        } else {
            add_normal_move(pos, SET_MOVE(from, to, cap, EMPTY, 0), list);
        }
    }
}



void generate_all_moves(S_BOARD *pos, S_MOVELIST *mvlist) {
    mvlist->move_count = 0;
    int side = pos->currSideToPlay;
    int sq;
    for (int i = 0; i < pos->pieceNum[Pawn][WHITE]; ++i) {
        sq = pos->pceSqList[wP][i];
        
    }
}