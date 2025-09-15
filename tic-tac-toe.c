#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY ' '

//All functions
void Board(char board[10][10], int n);
void disboard(char board[10][10], int n);
int checkwin(char board[10][10], int n, char symbol);
int checkdraw(char board[10][10], int n);
void playermove(char board[10][10], int n, char symbol);
void computermove(char board[10][10], int n, char symbol);

//the board
void Board(char board[10][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = EMPTY;
}

//Display the board  
void disboard(char board[10][10], int n) {
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
int checkwin(char board[10][10], int n, char s) {
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
int checkdraw(char board[10][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (board[i][j] == EMPTY) return 0;
    return 1;
}
//Player Move
void playermove(char board[10][10], int n, char symbol) {
    int row, column;
    while (1) {
        printf("Player %c - enter row and column (0-%d): ", symbol, n - 1);
        scanf("%d %d", &row, &column);
        if (row >= 0 && row < n && column >= 0 && column < n && board[row][column] == EMPTY) {
            board[row][column] = symbol;
            break;
        } else {
            printf("Invalid move,Try again.\n");
        }
    }
}

//Random move for pc
void computermove(char board[10][10], int n, char symbol) {
    int row, column;
    do {
        row = rand() % n;
        column = rand() % n;
    } while (board[row][column] != EMPTY);

    board[row][column] = symbol;
    printf("Computer played at (%d, %d)\n", row, column);
}

//Main Game 
int main() {
    srand(time(NULL));
    int n, mode;
    char board[10][10];

    printf("Enter board size (3-10): ");
    scanf("%d", &n);
    if (n < 3 || n > 10) {
        printf("Invalid size\n");
        return 0;
    }
    printf("Select Mode:\n");
    printf("1 - User vs User\n");
    printf("2 - User vs Computer\n");
    scanf("%d", &mode);
    Board(board, n);
    char player = 'X';
    while (1) {
        disboard(board, n);

        if (mode == 1 || (mode == 2 && player == 'X')) {
            playermove(board, n, player);
        } else {
            computermove(board, n, player);
        }

        if (checkwin(board, n, player)) {
            disboard(board, n);
            if (mode == 2 && player == 'O')
                printf("Computer wins\n");
            else
                printf("Player %c wins\n", player);
            break;
        }

        if (checkdraw(board, n)) {
            disboard(board, n);
            printf("Game is a draw!\n");
            break;
        }

        //Switch turn
        player = (player == 'X') ? 'O' : 'X';
    }

    return 0;
}
