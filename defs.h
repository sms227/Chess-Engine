#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if (!(n)) { \
printf("%s - Failed ", #n); \
printf("On %s ", __DATE__); \
printf("At %s ", __TIME__); \
printf("In File %s ", __FILE__); \
printf("At Line %s\n", __LINE__); \
exit(1);}
#endif

typedef unsigned long long U64;

#define NAME "Engine"
#define BRD_SQ_NUM 120

#define MAXGAMEMOVES 2048

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

// Board structure 
enum {EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};

enum {WHITE, BLACK, BOTH};

// 120 square board (to check if move is legal)
enum{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

enum {FALSE, TRUE};

// Castling Permisions:
enum {WKC = 1, WQC = 2, BKC = 4, BQC = 8};

// Undo move structure
typedef struct {
    int move;
    int castlePerm;
    int enPas;
    int fiftyMove;
    U64 posKey; //(or hash key) unique number representing position

} S_UNDO;

//Board structure
typedef struct{
    int pieces[BRD_SQ_NUM];
    U64 pawns[3];

    int KingSq[2];

    int side;
    int enPas; 
    int fiftyMove; 

    int ply; // number of half-moves
    int hisPly;

    U64 posKey; 

    int castlePerm;

    int pceNum[13]; 
    int bigPce[2]; // all pieces (no pawns) 
    int majPce[2]; // major pieces: rooks and queens
    int minPce[2]; // minor pieces: knights and bishops
    int material[2];

    S_UNDO history[MAXGAMEMOVES];

    // piece list (no pawns)
    int PieceList[13][10]; 

} S_BOARD;

/* MACROS */
#define FR2SQ(f, r) ((21 + (f)) + ((r) * 10)) // convert file and rank to 120 square coordinates
#define SQ64(sq120) (Sq120ToSq64[(sq120)]) // convert 120 based index to 64
#define SQ120(sq64) (Sq64ToSq120[(sq64)])
#define POP(b) PopBit(b) // takes the first bit, returns the index of bit, and sets bit to 0.
#define CNT(b) CountBits(b)
#define CLRBIT(bb, sq) ((bb) &= ClearMask[(sq)])
#define SETBIT(bb, sq) ((bb) |= SetMask[(sq)])

/* GLOBALS */
extern int Sq120ToSq64[BRD_SQ_NUM]; // Converts 120 square board to 64 square board
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CastleKeys[16]; // uses 4 bits to represent castling rights
extern char PceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

extern int PieceBig[13];
extern int PieceMaj[13];
extern int PieceMin[13];
extern int PieceVal[13]; // piece value
extern int PieceCol[13]; // piece color

extern int FilesBrd[BRD_SQ_NUM];
extern int RanksBrd[BRD_SQ_NUM];


/* FUNCTIONS */

// init.c 
extern void AllInit();

// bitboards.c
extern void PrintBitBoard(U64 bb); 
extern int PopBit(U64 *bb); // takes the first bit, returns the index of bit, and sets bit to 0.
extern int CountBits(U64 b); // counts number of bits

// hashkeys.c
extern U64 GeneratePosKey(const S_BOARD *pos);

// board.c
extern void ResetBoard(S_BOARD *pos);
extern int ParseFen(char *fen, S_BOARD *pos);
extern void PrintBoard(const S_BOARD *pos);
extern void UpdateListMaterial(S_BOARD *pos);
extern int CheckBoard(const S_BOARD *pos);

#endif