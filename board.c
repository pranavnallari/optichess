// board.c
// for setting position and resetting using FEN

#include "globals.h"

const char* startfen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

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
    int piece;
    int sq = A8; // Start at A8 in 120-based board index
    int empty_sq;
    int i = 0;
    
    // 1. Parse piece placement
    memset(state->board, EMPTY, sizeof(state->board));
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
            case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8':
                empty_sq = fen[i] - '0'; break;
            case '/': 
                sq -= 16;
                continue;
            default:
                return -1; // Invalid FEN character
        }
        if (piece != EMPTY) {
            state->board[sq++] = piece;
        } else if (empty_sq > -1) {
            for (int j = 0; j < empty_sq; j++) {
                state->board[sq++] = EMPTY;
            }
        }
        i++;
    }
    if (fen[i] != ' ') return -1;
    i++;

    // 2. Active Colour
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
    if (fen[i] == '-') {
        state->enPas = NO_SQ;
        i++;
    } else {
        int file = fen[i] - 'a';
        int rank = fen[i + 1] - '1';

        if (file >= 0 && file <= 7 && rank >= 0 && rank <= 7) {
            state->enPas = RCToSQ(rank, file);
            i += 2;
        } else {
            return -1;
        }
    }
    i++;

    // 5. HalfMove Counter
    state->fiftyMoveCounter = 0;
    while (fen[i] != ' ' && fen[i] != '\0') {
        if (fen[i] < '0' || fen[i] > '9') return -1;
        state->fiftyMoveCounter = state->fiftyMoveCounter * 10 + (fen[i] - '0');
        i++;
    }
    i++;

    // 6. Fullmove Number
    state->fullmoveNumber = 0;
    while (fen[i] != '\0') {
        if (fen[i] < '0' || fen[i] > '9') return -1;
        state->fullmoveNumber = state->fullmoveNumber * 10 + (fen[i] - '0');
        i++;
    }

    return 1; // Success
}
