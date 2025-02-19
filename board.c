// board.c
// for setting position and resetting using FEN

#include "globals.h"



/*
6 fields
1. Piece Placement
2. Active Colour
3. Castling Availability
4. En Passant target Square
5. HalfMove clock
6. FullMove clock
*/

int ParseFEN(S_BOARD *state, const char *fen) {
    if (fen == NULL) {
        printf("[Error] :- NULL FEN...!\n");
        return -1;
    }
    if (state == NULL) {
        printf("[Error] :- NULL State...!\n");
        return -2;
    }
    int piece;
    int sq = A8; // Start at A8 in 120-based board index
    int empty_sq;
    int i = 0;

    // 1. Parse piece placement
    printf("Parsing 1. Piece Placement...\n");
    while (fen[i] && fen[i] != ' ') {
        piece = EMPTY;
        empty_sq = -1;
        switch (fen[i]) {
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'q': piece = bQ; break;
            case 'k': piece = bK; break;
            case 'p': piece = bP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'Q': piece = wQ; break;
            case 'K': piece = wK; break;
            case 'P': piece = wP; break;
            case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8':
                empty_sq = fen[i] - '0';
                sq += empty_sq;
                break;
            case '/': 
                sq -= 18;
                break;
            default:
                printf("Invalid character in FEN: %c\n", fen[i]);
                return -1;
        }
        if (piece != EMPTY) {
            state->board[sq++] = piece;
        }
        i++;
    }

    if (fen[i] != ' ') return -1;
    i++;   

    // 2. Active Colour
    printf("Parsing 2. Active Colour...\n");
    if (fen[i] == 'w') {
        state->currSideToPlay = WHITE;
    } else if (fen[i] == 'b') {
        state->currSideToPlay = BLACK;
    } else {
        return -1;
    }
    i++;

    if (fen[i] != ' ') return -1;
    i++;

    // 3. Castling Availability
    printf("Parsing 3. Castling Availability...\n");
    state->castlePerm = 0;
    while (fen[i] != ' ') {
        switch(fen[i]) {
            case 'K': state->castlePerm |= WKCA; break;
            case 'Q': state->castlePerm |= WQCA; break;
            case 'k': state->castlePerm |= BKCA; break;
            case 'q': state->castlePerm |= BQCA; break;
            case '-': break;
            default: return -1;
        }
        i++;
    }
    i++;

    // 4. EnPassant Square
    printf("Parsing 4. EnPassant Square...\n");
    if (fen[i] == '-') {
        state->enPas = NO_SQ;
        i++;
    } else {
        int file = fen[i] - 'a';
        int rank = fen[i + 1] - '1';

        if (file >= 0 && file <= 7 && rank >= 0 && rank <= 7) {
            state->enPas = RCToSQ(file, rank);
            i += 2;
        } else {
            return -1;
        }
    }
    i++;

    // 5. HalfMove Counter
    printf("Parsing 5. HalfMove Counter...\n");
    state->fiftyMoveCounter = 0;
    while (fen[i] != ' ' && fen[i] != '\0') {
        if (fen[i] < '0' || fen[i] > '9') return -1;
        state->fiftyMoveCounter = state->fiftyMoveCounter * 10 + (fen[i] - '0');
        i++;
    }
    i++;

    // 6. Fullmove Number
    printf("Parsing 6. FullMove Counter...\n");
    state->fullmoveNumber = 0;
    while (fen[i] != '\0') {
        if (fen[i] < '0' || fen[i] > '9') return -1;
        state->fullmoveNumber = state->fullmoveNumber * 10 + (fen[i] - '0');
        i++;
    }
    printf("Parsed FEN successfully\n");
    return 1; // Success
}


// we need to reset to starting fen
int ResetBoard(S_BOARD *board, const char* fen) {
    if (board == NULL) {
        return -1;
    }

    memset(board, 0, sizeof(S_BOARD));

    board->currSideToPlay = WHITE;
    board->enPas = NO_SQ;
    board->fiftyMoveCounter = 0;
    board->fullmoveNumber = 1;
    board->ply = 0;
    board->hisPly = 0;
    board->castlePerm = 0;
    memset(board->board, 0, sizeof(board->board));
    printf("Parsing FEN...\n");
    if (ParseFEN(board, fen) < 0) {
        printf("Error initializing board from FEN\n");
        return -1;
    }
    printf("Generating Poskey...\n");
    board->posKey = GeneratePosKey((const S_BOARD *)board);

    for (int i = 0; i < 12; i++) {
        board->piece[i] = 0ULL;
    }
    for (int t = 0; t < 7; t++) {
        for (int c = 0; c < 3; c++) {
            board->pieceNum[t][c] = 0;
        }
    }
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 10; j++) {
            board->pceSqList[i][j] = NO_SQ;
        }
    }

    for (int sq = 0; sq < BOARD_SQ_NUM; sq++) {
        if (OFFBOARD(sq)) continue;
        int piece = board->board[sq];
        if (piece == EMPTY) continue;

        int sq64 = Board120To64[sq];
        if (sq64 == 120) continue;
        
        SetBit(&board->piece[piece-1], sq);

        int pType;
        if (piece >= wP && piece <= wK) {
            pType = piece;
            board->pieceNum[pType][WHITE]++;
        } else if (piece >= bP && piece <= bK) {
            pType = piece - 6;
            board->pieceNum[pType][BLACK]++;
        } else {
            continue;
        }
        board->pieceNum[pType][BOTH]++;
        int idx = 0;
        if (piece >= wP && piece <= wK) {
            idx = board->pieceNum[piece][WHITE] - 1;
        } else {
            idx = board->pieceNum[piece - 6][BLACK] - 1;
        }
        if (idx < 10) {
            board->pceSqList[piece][idx] = sq;
        }
    }
    return 0;
}