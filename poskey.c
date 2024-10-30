// poskeys.c
#include "globals.h"


U64 GeneratePosKey(const S_BOARD *pos) {
	U64 key = 0;
	for (int piece = 0; piece <  12; piece++) {
		U64 bitboard = pos->piece[piece];
		while (bitboard) {
			int sq = __builtin_ffsll(bitboard) - 1;
			key ^= PieceKeys[piece][sq];
			bitboard &= bitboard - 1;
		}
	}

	key ^= CastleKeys[pos->castlePerm];

	if (pos->enPas != -1) {
		int enPasFile = pos->enPas % 8;
		key ^= EnPassant[enPasFile];
	}

	if (pos->currSideToPlay == BLACK) {
		key ^= SideKey;
	}
	return key;
} 
