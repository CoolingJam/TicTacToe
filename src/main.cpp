#include <iostream>

#define USER 0
#define COMPUTER 1
#define USERMOVE 'X'
#define COMPUTERMOVE 'O'
#define EMPTYMOVE ' '

struct Move {
    int row, col;
};

int evaluate(char board[3][3]) {
    // Result of this function is who won
    // X win is -1
    // O win is 1
    // check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == USERMOVE) return -1;
            if (board[i][0] == COMPUTERMOVE) return 1;
        }
    }
    // check cols
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == USERMOVE) return -1;
            if (board[0][i] == COMPUTERMOVE) return 1;
        }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0]== USERMOVE) return -1;
        if (board[0][0]== COMPUTERMOVE) return 1;
    }
 
    if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        if (board[0][2]== USERMOVE) return -1;
        if (board[0][2]== COMPUTERMOVE) return 1;
    }
    }
    // Nobody won so return 0
    return 0;
}

int legalMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTYMOVE) return true;
        }
    }
    return false;
}

void display(char board[3][3]) {
    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << " " << board[i][j] << " ";
            if (j != 2) std::cout << "|";
        }
        std::cout << std::endl;
        if (i != 2) std::cout << "-----------" << std::endl;
    }
    std::cout << std::endl;
}

int minimax(char board[3][3], int depth, bool isMax, int alpha, int beta) {
    int score = evaluate(board);
    if (score == 1) return score;
    if (score == -1) return score;
    if (!legalMovesLeft(board)) return 0;
    if (isMax) { // max turn
        int best = -2;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTYMOVE) {
                        board[i][j] = COMPUTERMOVE;
                        best = std::max(best, minimax(board, depth+1, !isMax, alpha, beta));
                        alpha = std::max(alpha, best);
                        board[i][j] = EMPTYMOVE;
                        if (beta <= alpha) break; // alpha beta pruning
                }
            }
        }
        return best;
    } else { // min turn
        int best = 2;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTYMOVE) {
                    board[i][j] = USERMOVE;
                    best = std::min(best, minimax(board, depth+1, !isMax, alpha, beta));
                    beta = std::min(beta, best);
                    board[i][j] = EMPTYMOVE;
                    if (beta <= alpha) break; // alpha beta pruning
                }
            }
        }
        return best;
    } 
}

void initBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = EMPTYMOVE;
        }
    }
}

Move getBestMove(char board[3][3]) {
    int bestV = -2;
    Move bestM;
    bestM.row = -1;
    bestM.col = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTYMOVE) {
            board[i][j] = COMPUTERMOVE;
            int moveV = minimax(board, 0, false, -2, 2);
            board[i][j] = EMPTYMOVE;
            if (moveV > bestV) {
                bestM.row = i;
                bestM.col = j;
                bestV = moveV;
            }
            }
        }
    }
    return bestM;
}

int isLegal(Move move, char board[3][3]) {
    if (move.row >= 0 && move.col <=2 && move.row >= 0 && move.col <= 2) {
        if (board[move.row][move.col] == EMPTYMOVE) return true;
    }
    return false;
}


void play(int turn) {
    char board[3][3];
    initBoard(board);
    while (legalMovesLeft(board) && evaluate(board) == 0) {
        if (turn == USER) {
            std::cout << "Your turn, enter the row and col: ";
            int row, col;
            std::cin >> row >> col;
            row -= 1;
            col -= 1; // minus 1 since its zero based
            Move userMove;
            userMove.row = row;
            userMove.col = col;
            if (!isLegal(userMove, board)) {
                std::cout << "Invalid move, try again" << std::endl;
                continue;
            }
            board[userMove.row][userMove.col] = USERMOVE;
            turn = COMPUTER;
        } else if (turn == COMPUTER) {
            Move bestMove = getBestMove(board);
            board[bestMove.row][bestMove.col] = COMPUTERMOVE;
            std::cout << "AI plays this:" << std::endl;
            display(board);
            turn = USER;
        }
    }
    if (evaluate(board) == 1) std::cout << "Computer won";
    if (evaluate(board) == -1) std::cout << "User won";
    if (evaluate(board) == 0) std::cout << "Draw";
    std::cout << std::endl;
}

int main() {
    std::cout << "TicTacToe AI by Cooling" << std::endl;
    std::cout << "You are playing as " << USERMOVE << ", AI is playing as " << COMPUTERMOVE << std::endl;
    play(USER);
}