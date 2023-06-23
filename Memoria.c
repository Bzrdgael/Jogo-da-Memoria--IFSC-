#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BOARD_SIZE 6
#define NUM_PAIRS 18
#define VIEW_TIME 15

void createBoard(char board[][BOARD_SIZE]);
void printBoard(const char board[][BOARD_SIZE], const bool revealed[][BOARD_SIZE]);
void printLetters(const char board[][BOARD_SIZE]);
bool isBoardFull(const bool revealed[][BOARD_SIZE]);
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

void printBoard(const char board[][BOARD_SIZE], const bool revealed[][BOARD_SIZE]) {
    printf("   ");
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("%2d ", col + 1);
    }
    printf("\n");
    printf("  +");
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("---");
    }
    printf("\n");
    for (int row = 0; row < BOARD_SIZE; row++) {
        printf("%2d|", row + 1);
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (revealed[row][col]) {
                printf(" %c ", board[row][col]);
            } else {
                printf("[*]");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void printLetters(const char board[][BOARD_SIZE]) {
    printf("   ");
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("%2d ", col + 1);
    }
    printf("\n");
    printf("  +");
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("---");
    }
    printf("\n");
    for (int row = 0; row < BOARD_SIZE; row++) {
        printf("%2d|", row + 1);
        for (int col = 0; col < BOARD_SIZE; col++) {
            printf(" %c ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
    printf("Memorize as letras e suas posições por %d segundos.\n", VIEW_TIME);
    sleep(VIEW_TIME);
    system("clear"); // Limpa a tela (apenas para sistemas Unix/Linux)
}

bool isBoardFull(const bool revealed[][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!revealed[i][j]) {
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
    bool revealed[BOARD_SIZE][BOARD_SIZE];
    memset(revealed, false, sizeof(revealed));

    createBoard(board);

    int numPairs = NUM_PAIRS;
    int numAttempts = 0;

    printLetters(board);

    while (numPairs > 0 && !isBoardFull(revealed)) {
        system("clear"); // Limpa a tela (apenas para sistemas Unix/Linux)
        printf("Tabuleiro:\n\n");
        printBoard(board, revealed);
        printf("\n");

        int row1, col1, row2, col2;

        do {
            printf("Escolha a primeira posição (linha coluna): ");
            scanf("%d %d", &row1, &col1);
            printf("\n");
        } while (!isValidPosition(row1 - 1, col1 - 1) || revealed[row1 - 1][col1 - 1]);

        revealed[row1 - 1][col1 - 1] = true;

        system("clear"); // Limpa a tela (apenas para sistemas Unix/Linux)
        printf("Tabuleiro:\n\n");
        printBoard(board, revealed);
        printf("\n");

        do {
            printf("Escolha a segunda posição (linha coluna): ");
            scanf("%d %d", &row2, &col2);
            printf("\n");
        } while (!isValidPosition(row2 - 1, col2 - 1) || revealed[row2 - 1][col2 - 1] || (row1 == row2 && col1 == col2));

        revealed[row2 - 1][col2 - 1] = true;

        system("clear"); // Limpa a tela (apenas para sistemas Unix/Linux)

        numAttempts++;

        if (board[row1 - 1][col1 - 1] == board[row2 - 1][col2 - 1]) {
            printf("Par encontrado!\n\n");
            board[row1 - 1][col1 - 1] = '#';
            board[row2 - 1][col2 - 1] = '#';
            revealed[row1 - 1][col1 - 1] = true;
            revealed[row2 - 1][col2 - 1] = true;
            numPairs--;
        } else {
            printf("Par não encontrado. Tente novamente.\n\n");
            revealed[row1 - 1][col1 - 1] = false;
            revealed[row2 - 1][col2 - 1] = false;
        }
    }

    system("clear"); // Limpa a tela (apenas para sistemas Unix/Linux)
    printf("Tabuleiro:\n\n");
    printBoard(board, revealed);
    printf("\n");

    if (numPairs == 0) {
        printf("Parabéns! Você completou o jogo em %d tentativas.\n", numAttempts);
    } else {
        printf("Você não conseguiu encontrar todos os pares. Tente novamente!\n");
    }
}

int main() {
    playGame();

    return 0;
}