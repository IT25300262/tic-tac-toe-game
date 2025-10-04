#ifndef TICTACTOE_H
#define TICTACTOE_H

#define EMPTY ' '

// Function prototypes
char** createboard(int n);
void freeboard(char** board, int n);
void Board(char** board, int n);
void disBoard(char** board, int n);
int checkWin(char** board, int n, char symbol);
int checkDraw(char** board, int n);
void playerMove(char** board, int n, char symbol);
void computerMove(char** board, int n, char symbol);
void savegameresult(const char* filename, const char* result);

#endif
