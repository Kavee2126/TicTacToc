#include <stdio.h>

#define MAX_SIZE 10

// Function to initialize the board
void initializeBoard(char board[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = ' ';
}

// Function to display the board
void displayBoard(char board[MAX_SIZE][MAX_SIZE], int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        // Print row
        for (int j = 0; j < n; j++) {
            printf(" %c ", board[i][j]);
            if (j < n - 1) printf("|");
        }
        printf("\n");

        // Print separator
        if (i < n - 1) {
            for (int k = 0; k < n; k++) {
                printf("---");
                if (k < n - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

// Function to validate move
int isValidMove(char board[MAX_SIZE][MAX_SIZE], int row, int col, int n) {
    return row >= 0 && row < n && col >= 0 && col < n && board[row][col] == ' ';
}

// Function to place symbol
void placeSymbol(char board[MAX_SIZE][MAX_SIZE], int row, int col, char symbol) {
    board[row][col] = symbol;
}

// Function to accept user input
void getUserMove(int* row, int* col, int player, char symbol, int n) {
    printf("Player %d (%c), enter row and column (0 to %d): ", player, symbol, n - 1);
    scanf("%d %d", row, col);
}

// Function to check for win
int checkWin(char board[MAX_SIZE][MAX_SIZE], int n, char symbol) {
    int win;

    // Check rows and columns
    for (int i = 0; i < n; i++) {
        win = 1;
        for (int j = 0; j < n; j++)
            if (board[i][j] != symbol) win = 0;
        if (win) return 1;

        win = 1;
        for (int j = 0; j < n; j++)
            if (board[j][i] != symbol) win = 0;
        if (win) return 1;
    }

    // Check diagonals
    win = 1;
    for (int i = 0; i < n; i++)
        if (board[i][i] != symbol) win = 0;
    if (win) return 1;

    win = 1;
    for (int i = 0; i < n; i++)
        if (board[i][n - i - 1] != symbol) win = 0;
    if (win) return 1;

    return 0;
}

// Function to check for draw
int isDraw(char board[MAX_SIZE][MAX_SIZE], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

// Main function
int main() {
    int n;
    char board[MAX_SIZE][MAX_SIZE];
    int row, col, turn = 0;
    char symbols[2] = {'X', 'O'};

    printf("Enter board size (3–10): ");
    scanf("%d", &n);

    if (n < 3 || n > 10) {
        printf("Invalid size. Please enter a number between 3 and 10.\n");
        return 1;
    }

    initializeBoard(board, n);

    while (1) {
        displayBoard(board, n);

        // Accept and validate move
        while (1) {
            getUserMove(&row, &col, turn + 1, symbols[turn], n);
            if (isValidMove(board, row, col, n)) break;
            printf("Invalid move. Try again.\n");
        }

        placeSymbol(board, row, col, symbols[turn]);

        // Check win
        if (checkWin(board, n, symbols[turn])) {
            displayBoard(board, n);
            printf("Player %d (%c) wins!\n", turn + 1, symbols[turn]);
            break;
        }

        // Check draw
        if (isDraw(board, n)) {
            displayBoard(board, n);
            printf("It's a draw!\n");
            break;
        }

        turn = 1 - turn; // Switch player
    }

    return 0;
}

