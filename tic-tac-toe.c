#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tic-tac-toe.h"

//create dynamic board
char** createboard(int n) {
    char **board = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++)
        board[i] = (char*)malloc(n * sizeof(char));
    return board;
}

// Free dynamic board
void freeboard(char** board, int n) {
    for (int i = 0; i < n; i++)
        free(board[i]);
    free(board);
}

//the board
void Board(char** board, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = EMPTY;
}

//Display the board  
void disboard(char** board, int n) {
    printf("\n   ");
    for (int j = 0; j < n; j++) {
        printf(" %d  ", j);
    }
    printf("\n");
    printf("   ");
    for (int j = 0; j < n; j++) {
        printf("----");
    }
    printf("-\n");
    for (int i = 0; i < n; i++) {
        printf("%d |", i); 
        for (int j = 0; j < n; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n");
        printf("   ");
        for (int j = 0; j < n; j++) {
            printf("----");
        }
        printf("-\n");
    }
    printf("\n");
}

//Check win
int checkwin(char** board, int n, char s) {
    for (int i = 0; i < n; i++) {
        int row = 1, column = 1;
        for (int j = 0; j < n; j++) {
            if (board[i][j] != s) row = 0;
            if (board[j][i] != s) column = 0;
        }
        if (row || column) return 1;
    }
    int d1 = 1, d2 = 1;
    for (int i = 0; i < n; i++) {
        if (board[i][i] != s) d1 = 0;
        if (board[i][n - 1 - i] != s) d2 = 0;
    }
    return (d1 || d2);
}

//Check draw 
int checkdraw(char** board, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (board[i][j] == EMPTY) return 0;
    return 1;
}
//Player Move
void playermove(char** board, int n, char symbol) {
    int row, column;
    while (1) {
        printf("Player %c - enter row and column (0-%d): ", symbol, n - 1);
        scanf("%d %d", &row, &column);
        if (row >= 0 && row < n && column >= 0 && column < n && board[row][column] == EMPTY) {
            board[row][column] = symbol;
          
	    FILE *fp = fopen("results.txt", "a");
            if (fp) {
                fprintf(fp, "Player %c -> (%d,%d)\n", symbol, row, column);
                fclose(fp);
            }
	  
	    break;
        } else {
            printf("Invalid move,Try again.\n");
        }
    }
}

//Random move for pc
void computermove(char** board, int n, char symbol) {
    int row, column;
    do {
        row = rand() % n;
        column = rand() % n;
    } while (board[row][column] != EMPTY);

    board[row][column] = symbol;
    printf("Computer played at (%d, %d)\n", row, column);
 
    FILE *fp = fopen("results.txt", "a");
    if (fp) {
        fprintf(fp, "Computer -> (%d,%d)\n", row, column);
        fclose(fp);
    }
}
//save file
void savegameresult(const char* filename, const char* result) {
    FILE *fp = fopen(filename, "a");
    if (fp) {
        fprintf(fp, "%s\n", result);
        fclose(fp);
    }
}

//Main Game 
int main() {
    srand(time(NULL));
    int n, mode;

    printf("Enter board size (3-10): ");
    scanf("%d", &n);
    if (n < 3 || n > 10)
        return 0;
   
    printf("Select Mode:\n");
    printf("1 - User vs User\n");
    printf("2 - User vs Computer\n");
    printf("3 - Three Player\n");
    scanf("%d", &mode);

    FILE *fp = fopen("results.txt", "a");
    if (fp) {
       fprintf(fp, "\n      New Game (Mode %d)     \n", mode);
       fclose(fp);
    }

    char **board = createboard(n);
    Board(board,n);

    char players[3] = {'X' , 'O' , 'Z'};
    int turn = 0;

    while (1) {
        disboard(board, n);
        
	char player = (mode == 3) ? players[turn % 3] : players[turn % 2];
        if(mode == 2 && player == 'O')
            computermove(board, n, player);
         else
            playermove(board, n, player);
        
        if (checkwin(board, n, player)) {
            disboard(board, n);
            if (mode == 2 && player == 'O'){
                printf("Computer wins\n");
	        savegameresult("results.txt", "Computer wins!");
	}  else{
                printf("Player %c wins!\n", player);
                char res[50]; sprintf(res, "Player %c wins!", player);
                savegameresult("results.txt", res);
            }
            break;
	}

        if (checkdraw(board, n)) {
            disboard(board, n);
            printf("Game is a draw!\n");
	    savegameresult("results.txt", "Draw!");
            break;
        }

        //Next player turn
        turn++;
    }
    freeboard(board, n);
    return 0;
}
