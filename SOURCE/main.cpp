#include <iostream>
#include <iomanip>

 
bool isSafeBacktracking(int x, int y, int** board, int size){
    return x >= 0 && x < size && y >= 0 && y < size && board[x][y] == -1;
}

bool solveKTBacktracking(int x, int y, int move, int** &board, int size, int xMove[8], int yMove[8]){
    int nextX, nextY;
    if (move == size * size) return true;
    for (int i = 0; i < size; i++) {
        nextX = x + xMove[i];
        nextY = y + yMove[i];
        if (isSafeBacktracking(nextX, nextY, board, size)) {
            board[nextX][nextY] = move;
            if (solveKTBacktracking(nextX, nextY, move + 1, board, size, xMove, yMove)) 
                return true;
            else board[nextX][nextY] = -1;
        }
    }
    return false;
}

void printSolution(int** sol, int size){
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++)
            std::cout << " " << std::setw(2) << sol[x][y] << " ";
        std::cout << "\n";
    }
}
 
void backtrackKT(){
    int size, x, y;
    std::cout << "Size: ";
    std::cin >> size;
    int** board = new int*[size];
    for(int i = 0; i < size; i++){
        board[i] = new int[size];
        for(int j = 0; j < size; j++){
            board[i][j] = -1;
        }
    }
    std::cin >> x >> y;

    int moveX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int moveY[8] = {1, 2, 2, 1, -1, -2, -2, -1};
 
    board[x][y] = 0;
 
    if (!solveKTBacktracking(x, y, 1, board, size, moveX, moveY)) {
        std::cout << "Solution does not exist";
    }
    else printSolution(board, size);
    for(int i = 0; i < size; i++){
        delete[] board[i];
    }
    delete[] board;
}
 
int main(int argc, char* argv[]){
    backtrackKT();
    return 0;
}