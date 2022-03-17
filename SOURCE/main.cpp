#include <iostream>
#include <iomanip>
#include <fstream>

bool isSafeBacktracking(int x, int y, int** board, int size){
    return x >= 0 && x < size && y >= 0 && y < size && board[x][y] == -1;
}

bool solveKTBacktracking(int x, int y, int move, int &total, int** &board, int size, int xMove[8], int yMove[8]){
    int nextX, nextY;
    if (move > size * size) return true;
    for (int i = 0; i < 8; i++) {
        nextX = x + xMove[i];
        nextY = y + yMove[i];
        if (isSafeBacktracking(nextX, nextY, board, size)) {
            board[nextX][nextY] = move;
            total++;
            if (solveKTBacktracking(nextX, nextY, move + 1, total, board, size, xMove, yMove)) return true;
            else board[nextX][nextY] = -1;
        }
    }
    return false;
}

void outputFile(int** board, int size, int x, int y, int total, std::chrono::duration<double> elapsed_seconds){
    std::fstream f("20127370_backtrack.txt", std::fstream::out);
    f << x << " " << y << " " << size << "\n";
    f << total << "\n";
    f << elapsed_seconds.count() << "\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            f << " " << std::setw(2) << board[i][j] << " ";
        f << "\n";
    }
}
 
void backtrackKT(int argc, char* argv[]){
    int size = std::atoi(argv[6]);
    int x = std::atoi(argv[2]), y = std::atoi(argv[4]);
    int** board = new int*[size];
    for(int i = 0; i < size; i++){
        board[i] = new int[size];
        for(int j = 0; j < size; j++){
            board[i][j] = -1;
        }
    }

    int total = 1;
    int moveX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int moveY[8] = {1, 2, 2, 1, -1, -2, -2, -1};
 
    board[x-1][y-1] = 1;
    auto start = std::chrono::system_clock::now();
    bool checkKT = solveKTBacktracking(y-1, x-1, 2, total, board, size, moveX, moveY);
    auto end  = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Time: " << elapsed_seconds.count() << "\n";
    if (!checkKT) std::cout << "Solution does not exist";
    else outputFile(board, size, x, y, total, elapsed_seconds);

    for(int i = 0; i < size; i++){
        delete[] board[i];
    }
    delete[] board;
}
 
int main(int argc, char* argv[]){
    backtrackKT(argc, argv);
    return 0;
}