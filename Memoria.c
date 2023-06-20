#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARD_SIZE 6
#define NUM_PAIRS 18

void createBoard(char board[][BOARD_SIZE]);
void printBoard(const char board[][BOARD_SIZE]);
bool isBoardFull(const char board[][BOARD_SIZE]);
bool isValidPosition(int row, int col);
void playGame();

void createBoard(char board[][BOARD_SIZE]) {
    char symbols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int pairs[NUM_PAIRS * 2];
    srand(time(NULL));

    // Criar pares de símbolos
    for (int i = 0; i < NUM_PAIRS * 2; i++) {
        pairs[i] = symbols[i / 2];
    }

    // Embaralhar os pares
    for (int i = 0; i < NUM_PAIRS * 2; i++) {
        int j = rand() % (NUM_PAIRS * 2);
        int temp = pairs[i];
        pairs[i] = pairs[j];
        pairs[j] = temp;
    }

    // Preencher o tabuleiro com os pares
    int index = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = pairs[index++];
        }
    }
}

void printBoard(const char board[][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

bool isBoardFull(const char board[][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] != ' ') {
                return false;
            }
        }
    }
    return true;
}

bool isValidPosition(int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE);
}

void playGame() {
    char board[BOARD_SIZE][BOARD_SIZE];
    createBoard(board);

    int numPairs = NUM_PAIRS;
    int numAttempts = 0;
    time_t startTime, endTime;
    double elapsedTime;

    time(&startTime);

    while (numPairs > 0) {
        printf("Tabuleiro:\n\n");
        printBoard(board);
        printf("\n");

        int row1, col1, row2, col2;

        do {
            printf("Escolha a primeira posicao (linha coluna): ");
            scanf("%d %d", &row1, &col1);
        } while (!isValidPosition(row1 - 1, col1 - 1) || board[row1 - 1][col1 - 1] == ' ');

        do {
            printf("Escolha a segunda posicao (linha coluna): ");
            scanf("%d %d", &row2, &col2);
            printf("\n");
        } while (!isValidPosition(row2 - 1, col2 - 1) || board[row2 - 1][col2 - 1] == ' ' || (row1 == row2 && col1 == col2));

        numAttempts++;

        if (board[row1 - 1][col1 - 1] == board[row2 - 1][col2 - 1]) {
            printf("Par encontrado!\n\n");
            board[row1 - 1][col1 - 1] = ' ';
            board[row2 - 1][col2 - 1] = ' ';
            numPairs--;
        } else {
            printf("Par nao encontrado. Tente novamente.\n\n");
        }
    }

    time(&endTime);
    elapsedTime = difftime(endTime, startTime);

    printf("Parabens! Voce completou o jogo em %.1f segundos com %d tentativas.\n", elapsedTime, numAttempts);
}

int main() {
    playGame();

    return 0;
}
