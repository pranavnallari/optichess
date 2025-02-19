// debug.c
#include "globals.h"

void PrintBoard120To64() {
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (i % 10 == 0) printf("\n");
            printf("%5d",  Board120To64[i]);
    }
    printf("\n\n");
}

void PrintBoard64To120() {
    for (int i = 0; i < 64; ++i) {
        if (i % 8 == 0)  printf("\n");
        printf("%5d", Board64To120[i]);
    }
}

void PrintHashKeys() {
    printf("SideKey: %llu\n", SideKey);
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 64; ++j) {
            printf("PieceKey[%d][%d]: %llu\n", i, j, PieceKeys[i][j]);
        }
    }
    for (int i = 0; i < 16; ++i) {
        printf("CastleKey[%d]: %llu\n", i, CastleKeys[i]);
    }
    for (int i = 0; i < 8; ++i) {
        printf("EnPassant[%d]: %llu\n", i, EnPassant[i]);
    }
}

void PrintBoard(S_BOARD *brd) {
    const char pieceChar[] = ".PNBRQKpnbrqk";
    printf("\nBoard:\n\n");
    for (int col = 7; col >= 0; col--) {
        printf("%d  ", col+1);
        for (int row = 0; row <= 7; row++) {
            int sq = RCToSQ(row, col);
            int piece = brd->board[sq];
            printf("%c ", pieceChar[piece]);
        }
        printf("\n");
    }
    
    printf("\n   ");
    for (char file = 'a'; file <= 'h'; file++) {
        printf("%c ", file);
    }
    printf("\n\n");

    printf("Side to play: %s\n", brd->currSideToPlay == WHITE ? "White" : "Black");

    printf("Castling availability: ");
    if (brd->castlePerm & WKCA) printf("K");
    if (brd->castlePerm & WQCA) printf("Q");
    if (brd->castlePerm & BKCA) printf("k");
    if (brd->castlePerm & BQCA) printf("q");
    if (brd->castlePerm == 0) printf("-");
    printf("\n");

    if (brd->enPas == NO_SQ) {
        printf("En passant square: -\n");
    } else {
        int enpas_rank = (brd->enPas / 10) - 2;
        int enpas_file = (brd->enPas % 10) - 1;
        printf("En passant square: %c%d\n", 'a' + enpas_file, enpas_rank + 1);
    }

    printf("Fifty-move counter: %d\n", brd->fiftyMoveCounter);
    printf("Fullmove number: %d\n", brd->fullmoveNumber);

    printf("Position key: %llu\n\n", brd->posKey);
}

const char *PrintSquare(const int sq) {
    static char PrSqr[3];

    int col = (sq % 10) - 1;
    int row = (sq / 10) - 2;

    PrSqr[0] = (char)('A' + col);
    PrSqr[1] = (char)('1' + row);
    PrSqr[2] = '\0';

    return PrSqr;
}

char *PrintMove(const int move) {
    static char MoveStr[6];

    int from_col = (MOVE_FROM_SQ(move) % 10) - 1;
    int from_row = (MOVE_FROM_SQ(move) / 10) - 2;

    int to_col = (MOVE_TO_SQ(move) % 10) - 1;
    int to_row = (MOVE_TO_SQ(move) / 10) - 2;

    int promoted = MOVE_PROMOTED_PIECE(move);

    if (promoted) {
        char pc = 'Q';
        if (promoted == wN || promoted == bN) {
            pc = 'N';
        } else if (promoted ==  bR || promoted == wR) {
            pc = 'R';
        } else if (promoted == bB || promoted == wB) {
            pc = 'B';
        }

        sprintf(MoveStr, "%c%c%c%c%c", ('A'+from_col), ('1'+from_row),('A'+to_col), ('1'+to_row), pc);
    } else {
        sprintf(MoveStr, "%c%c%c%c", ('A'+from_col), ('1'+from_row),('A'+to_col), ('1'+to_row));
    }
    return MoveStr;
}


void PrintMoveList(const S_MOVELIST *list) {
    printf("MoveList\n\n");
    for (int i = 0; i < list->move_count; ++i) {
        int move = list->moves[i].move;
        int score = list->moves[i].score;

        printf("Move : %d > %s  (score : %d)\n", i+1, PrintMove(move), score);
    }
}

#include <stdio.h>
#include "globals.h"

void DebugPrintBoard(const S_BOARD *board) {
    // Print a header
    printf("=== S_BOARD Debug Info ===\n");

    // Print the 120-square board array
    printf("Board Array (120-sq):\n");
    for (int i = 0; i < BOARD_SQ_NUM; i++) {
        // Print 10 values per line for readability
        if (i % 10 == 0)
            printf("\n");
        printf("%4d", board->board[i]);
    }
    printf("\n\n");

    // Print bitboards for each piece type
    printf("Bitboards (piece[12]):\n");
    for (int i = 0; i < 12; i++) {
        printf("Piece %2d: 0x%llx\n", i+1, board->piece[i]);
    }
    printf("\n");

    // Print piece numbers (pieceNum[7][3])
    printf("Piece Numbers (pieceNum[7][3]):\n");
    for (int type = 0; type < 7; type++) {
        for (int col = 0; col < 3; col++) {
            printf("%4d ", board->pieceNum[type][col]);
        }
        printf("\n");
    }
    printf("\n");

    // Print piece square list (pceSqList[13][10])
    printf("Piece Square List (pceSqList[13][10]):\n");
    for (int p = 0; p < 13; p++) {
        printf("Piece index %2d: ", p);
        for (int j = 0; j < 10; j++) {
            printf("%4d ", board->pceSqList[p][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Print other board metadata
    printf("Current Side To Play: %s\n", board->currSideToPlay == WHITE ? "WHITE" : "BLACK");
    printf("En Passant Square: %d\n", board->enPas);
    printf("Fifty Move Counter: %d\n", board->fiftyMoveCounter);
    printf("Fullmove Number: %d\n", board->fullmoveNumber);
    printf("Ply: %d, History Ply: %d\n", board->ply, board->hisPly);
    printf("Position Key: 0x%llx\n", board->posKey);
    printf("Castle Permissions: %d\n", board->castlePerm);

    printf("=== End of Board Debug Info ===\n");
}
