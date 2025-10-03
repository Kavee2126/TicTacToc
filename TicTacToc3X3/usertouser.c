#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10

char board[MAX_SIZE][MAX_SIZE];
int size;

// Initialize the board
void initBoard(int n) {
    size = n;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = ' ';
}

// Display the board
void displayBoard() {
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]);
            if (j < size - 1) printf("|");
        }
        printf("\n");
        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                printf("---");
                if (j < size - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

// Check if move is valid
int isValidMove(int row, int col) {
    return row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ';
}

// Check for win condition
int checkWin(char symbol) {
    // Check rows and columns
    for (int i = 0; i < size; i++) {
        int rowCount = 0, colCount = 0;
        for (int j = 0; j < size; j++) {
            if (board[i][j] == symbol) rowCount++;
            if (board[j][i] == symbol) colCount++;
        }
        if (rowCount == size || colCount == size) return 1;
    }

    // Check diagonals
    int diag1 = 0, diag2 = 0;
    for (int i = 0; i < size; i++) {
        if (board[i][i] == symbol) diag1++;
        if (board[i][size - i - 1] == symbol) diag2++;
    }
    return diag1 == size || diag2 == size;
}

// Check for draw
int isDraw() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

// Player move
void playerMove(char symbol) {
    int row, col;
    do {
        printf("Player %c, enter row and column (0-%d): ", symbol, size - 1);
        scanf("%d %d", &row, &col);
    } while (!isValidMove(row, col));
    board[row][col] = symbol;
}

// Computer move
void computerMove(char symbol) {
    int row, col;
    do {
        row = rand() % size;
        col = rand() % size;
    } while (!isValidMove(row, col));
    printf("Computer %c plays at (%d, %d)\n", symbol, row, col);
    board[row][col] = symbol;
}

// Main game loop
void playGame(int mode) {
    char player1 = 'X'; // Human
    char player2 = 'O'; // Computer 1 or Player 2
    char player3 = 'Z'; // Computer 2 (only in mode 3)
    int turn = 0;

    while (1) {
        displayBoard();
        char current;

        if (mode == 3) {
            // 3-player mode: 1 human, 2 computers
            if (turn % 3 == 0) {
                current = player1;
                playerMove(current);
            } else if (turn % 3 == 1) {
                current = player2;
                computerMove(current);
            } else {
                current = player3;
                computerMove(current);
            }

            if (checkWin(current)) {
                displayBoard();
                if (current == player1)
                    printf("Human player %c wins!\n", current);
                else
                    printf("Computer player %c wins!\n", current);
                break;
            }
        } else if (mode == 1) {
            // User vs User
            current = (turn % 2 == 0) ? player1 : player2;
            playerMove(current);
            if (checkWin(current)) {
                displayBoard();
                printf("Player %c wins!\n", current);
                break;
            }
        } else if (mode == 2) {
            // User vs Computer
            if (turn % 2 == 0) {
                playerMove(player1);
                if (checkWin(player1)) {
                    displayBoard();
                    printf("You win!\n");
                    break;
                }
            } else {
                computerMove(player2);
                if (checkWin(player2)) {
                    displayBoard();
                    printf("Computer wins!\n");
                    break;
                }
            }
        }

        if (isDraw()) {
            displayBoard();
            printf("It's a draw!\n");
            break;
        }

        turn++;
    }
}

// Entry point
int main() {
    srand(time(NULL));
    int n, mode;

    printf("Welcome to TicTacToe!\n");
    do {
        printf("Enter board size (3 to 10): ");
        scanf("%d", &n);
    } while (n < 3 || n > 10);

    initBoard(n);

    printf("Choose Game Mode:\n");
    printf("1. User vs User\n");
    printf("2. User vs Computer\n");
    printf("3. Multiplayer (1 human + 2 computers)\n");
    scanf("%d", &mode);

    playGame(mode);

    return 0;
}

