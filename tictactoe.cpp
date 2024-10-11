#include <bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3 // Length of the board
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

// Function to show the Tic-Tac-Toe board
void showBoard(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        cout << "\t\t\t ";
        for (int j = 0; j < SIDE; j++) {
            cout << board[i][j];
            if (j < SIDE - 1) cout << " | ";
        }
        cout << "\n";
        if (i < SIDE - 1) cout << "\t\t\t---|---|---\n";
    }
    cout << "\n";
}

// Function to show the instructions for the game
void showInstructions() {
    cout << "\nChoose a cell numbered from 1 to 9 as shown below and play\n\n";
    cout << "\t\t\t 1 | 2 | 3 \n";
    cout << "\t\t\t---|---|---\n";
    cout << "\t\t\t 4 | 5 | 6 \n";
    cout << "\t\t\t---|---|---\n";
    cout << "\t\t\t 7 | 8 | 9 \n\n";
}

// Function to initialize the game board
void initialize(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to declare the winner
void declareWinner(int whoseTurn) {
    if (whoseTurn == COMPUTER)
        cout << "COMPUTER has won!\n";
    else
        cout << "HUMAN has won!\n";
}

// Function to check if any row is crossed
bool rowCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return true;
    }
    return false;
}

// Function to check if any column is crossed
bool columnCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return true;
    }
    return false;
}

// Function to check if any diagonal is crossed
bool diagonalCrossed(char board[][SIDE]) {
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return true;
    return false;
}

// Function to check if the game is over
bool gameOver(char board[][SIDE]) {
    return rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board);
}

// Function to return the best possible move for the computer
int minimax(char board[][SIDE], int depth, bool isAI) {
    if (gameOver(board)) {
        if (isAI)
            return -10 + depth;  // Human wins
        else
            return 10 - depth;  // Computer wins
    }

    if (depth == SIDE * SIDE)
        return 0;  // Draw

    if (isAI) {
        int bestScore = -1000;
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = COMPUTERMOVE;
                    bestScore = max(bestScore, minimax(board, depth + 1, false));
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = HUMANMOVE;
                    bestScore = min(bestScore, minimax(board, depth + 1, true));
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
}

// Function to find the best move for the computer
int bestMove(char board[][SIDE], int moveIndex) {
    int bestVal = -1000;
    int x = -1, y = -1;

    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTERMOVE;
                int moveVal = minimax(board, moveIndex + 1, false);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    x = i;
                    y = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return x * SIDE + y;
}

// Function to play Tic-Tac-Toe
void playTicTacToe(int whoseTurn) {
    char board[SIDE][SIDE];
    int moveIndex = 0, x = 0, y = 0;

    initialize(board);
    showInstructions();

    while (!gameOver(board) && moveIndex != SIDE * SIDE) {
        int n;
        if (whoseTurn == COMPUTER) {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            cout << "COMPUTER has put an " << COMPUTERMOVE << " in cell " << n + 1 << "\n\n";
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        } else if (whoseTurn == HUMAN) {
            cout << "You can insert in the following positions : ";
            for (int i = 0; i < SIDE; i++) {
                for (int j = 0; j < SIDE; j++) {
                    if (board[i][j] == ' ') {
                        cout << (i * SIDE + j) + 1 << " ";
                    }
                }
            }
            cout << "\n\nEnter the position = ";
            cin >> n;
            n--;
            x = n / SIDE;
            y = n % SIDE;

            if (board[x][y] == ' ' && n >= 0 && n < SIDE * SIDE) {
                board[x][y] = HUMANMOVE;
                cout << "\nHUMAN has put an " << HUMANMOVE << " in cell " << n + 1 << "\n\n";
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            } else {
                cout << "Invalid move! Try again.\n\n";
            }
        }
    }

    if (!gameOver(board) && moveIndex == SIDE * SIDE)
        cout << "It's a draw!\n";
    else
        declareWinner(whoseTurn == COMPUTER ? HUMAN : COMPUTER);
}

int main() {
    cout << "\n---------------------------------------------------\n\n";
    cout << "\t\t\t Tic-Tac-Toe\n";
    cout << "\n---------------------------------------------------\n\n";

    char cont = 'y';
    do {
        char choice;
        cout << "Do you want to start first? (y/n): ";
        cin >> choice;

        if (choice == 'n')
            playTicTacToe(COMPUTER);
        else if (choice == 'y')
            playTicTacToe(HUMAN);
        else
            cout << "Invalid choice!\n";

        cout << "Do you want to quit? (y/n): ";
        cin >> cont;
    } while (cont == 'n');

    return 0;
}

