#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

#define FEN1 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FEN2 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
int main()
{
    AllInit();

    S_BOARD board[1];
    ParseFen(FEN2, board);
    PrintBoard(board);
    
    ASSERT(CheckBoard(board));

    board -> posKey ^= SideKey;
    ASSERT(CheckBoard(board));

    return 0;
}
