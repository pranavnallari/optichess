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

void PrintBoard(const S_BOARD *brd) {
    const char pieceChar[] = ".PNBRQKpnbrqk";
    printf("\nBoard:\n\n");
    
    for (int rank = 8; rank >= 1; rank--) {
        printf("%d  ", rank);
        for (int file = 1; file <= 8; file++) {
            int sq = RCToSQ(rank - 1, file - 1);
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

    printf("Position key: %llx\n\n", brd->posKey);
}
