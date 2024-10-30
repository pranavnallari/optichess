// main.c
#include "globals.h"

int main(void) {
    AllInit();
    printf("Finished Initialzing...\n");
    S_BOARD state;
    if (ResetBoard(&state, START_FEN) < 0) {
        printf("Failed to reset board.\n");
        return EXIT_FAILURE;
    }

    PrintBoard(&state);
    return EXIT_SUCCESS;
}
    