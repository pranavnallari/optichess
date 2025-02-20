// main.c
#include "globals.h"

int main(void) {
    AllInit();
    printf("Finished Initialzing...\n");
    S_BOARD state;
    if (ResetBoard(&state, FEN_7) < 0) {
        printf("Failed to reset board.\n");
        return EXIT_FAILURE;
    }
    PrintBoard(&state);


    S_MOVELIST list[1];
    generate_all_moves(&state, list);
    PrintMoveList(list);

    
    return EXIT_SUCCESS;
}
    