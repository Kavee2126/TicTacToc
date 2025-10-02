#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 3
#define MAX_SIZE 10

char board[MAX_SIZE][MAX_SIZE];
int N;
FILE *logFile;

// Function to initialize the board
void initializeBoard() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = ' ';
}

// Function to display the board
void displayBoard() {
    printf("\n");
    for (int i = 0; i < N; i++) {
    
         // Print row
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
            if (j < N - 1) printf("|");
        }
        
        // Print separator
        if (i < N - 1) {
            printf("\n");
            for (int k = 0; k < N; k++) {
                printf("---");
                if (k < N - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

// Function to validate move
int isValidMove(int row, int col) {
    return row >= 0 && row < N && col >= 0 && col < N && board[row][col] == ' ';
}


void logMove(const char *player, int row, int col) {
    fprintf(logFile, "%s moved to (%d, %d)\n", player, row, col);
}

// Function to accept user input
void getUserMove() {
    int row, col;
    do {
        printf("Enter your move (row and column: 0 to %d): ", N - 1);
        scanf("%d %d", &row, &col);
    } while (!isValidMove(row, col));
    board[row][col] = 'X';
    logMove("User", row, col);
}
// Function to generate computer input
void generateComputerMove(int *row, int *col) {
    do {
        *row = rand() % N;
        *col = rand() % N;
    } while (!isValidMove(*row, *col));
}

// Function to play by computer
void playComputerTurn() {
    int row, col;
    generateComputerMove(&row, &col);
    board[row][col] = 'O';
    printf("Computer played at (%d, %d)\n", row, col);
    logMove("Computer", row, col);
}

char checkWinner() {
    // Check rows and columns
    for (int i = 0; i < N; i++) {
        int rowMatch = 1, colMatch = 1;
        for (int j = 1; j < N; j++) {
            if (board[i][j] != board[i][0] || board[i][j] == ' ') rowMatch = 0;
            if (board[j][i] != board[0][i] || board[j][i] == ' ') colMatch = 0;
        }
        if (rowMatch) return board[i][0];
        if (colMatch) return board[0][i];
    }

    // Check diagonals
    int diag1 = 1, diag2 = 1;
    for (int i = 1; i < N; i++) {
        if (board[i][i] != board[0][0] || board[i][i] == ' ') diag1 = 0;
        if (board[i][N - i - 1] != board[0][N - 1] || board[i][N - i - 1] == ' ') diag2 = 0;
    }
    if (diag1) return board[0][0];
    if (diag2) return board[0][N - 1];

    return ' ';
}

int isDraw() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

int main() {
    srand(time(NULL));
    logFile = fopen("game_log.txt", "w");
    if (!logFile) {
        printf("Error opening log file.\n");
        return 1;
    }

    printf("Enter board size (3 to 10): ");
    scanf("%d", &N);
    if (N < MIN_SIZE || N > MAX_SIZE) {
        printf("Invalid size. Please restart.\n");
        return 1;
    }

    initializeBoard();
    char winner = ' ';
    while (1) {
        displayBoard();
        getUserMove();
        winner = checkWinner();
        if (winner != ' ' || isDraw()) break;

        playComputerTurn();
        winner = checkWinner();
        if (winner != ' ' || isDraw()) break;
    }

    displayBoard();
    if (winner == 'X') printf("You win!\n");
    else if (winner == 'O') printf("Computer wins!\n");
    else printf("It's a draw!\n");

    fclose(logFile);
    return 0;
}
