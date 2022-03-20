#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

std::string mssv = "20127370", algo1 = "_backtrack", algo2 = "_heuristic";

static int moveX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
static int moveY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isValidBacktracking(int x, int y, int** board, int size){
    return x >= 0 && x < size && y >= 0 && y < size && board[x][y] == -1;
}

bool recursionKTBacktracking(int x, int y, int move, unsigned long long &total, int** &board, int size, int xMove[], int yMove[]){
    int nextX, nextY;
    if (move > size * size) return true;
    for (int i = 0; i < 8; i++) {
        nextX = x + xMove[i];
        nextY = y + yMove[i];
        if (isValidBacktracking(nextX, nextY, board, size)) {
            board[nextX][nextY] = move;
            total++;
            //if(total % 100000000 == 0) std::cout << total << "\n";
            if (recursionKTBacktracking(nextX, nextY, move + 1, total, board, size, xMove, yMove)) return true;
            else board[nextX][nextY] = -1;
        }
    }
    return false;
}

void outputFileBacktracking(int** board, int size, int x, int y, unsigned long long total, std::chrono::duration<double> elapsed_seconds){
    std::fstream f(mssv + algo1 + ".txt", std::fstream::out);
    f << x << " " << y << " " << size << "\n";
    f << total << "\n";
    f << elapsed_seconds.count() << "\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            f << " " << std::setw(2) << board[i][j] << " ";
        f << "\n";
    }
    f.close();
}
 
void backtrackingKT(int argc, char* argv[]){
    int size = std::atoi(argv[6]), x = std::atoi(argv[2]), y = std::atoi(argv[4]);
    int** board = new int*[size];
    for(int i = 0; i < size; i++){
        board[i] = new int[size];
        for(int j = 0; j < size; j++)
            board[i][j] = -1;
    }

    unsigned long long total = 1;
    board[--y][--x] = 1;
    auto start = std::chrono::system_clock::now();
    bool checkKT = recursionKTBacktracking(y, x, 2, total, board, size, moveY, moveX);
    auto end  = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    if (!checkKT) std::cout << "Solution does not exist!";
    else outputFileBacktracking(board, size, x+1, y+1, total, elapsed_seconds);

    for(int i = 0; i < size; i++)
        delete[] board[i];
    delete[] board;
}

static int cX[8] = {1,1,2,2,-1,-1,-2,-2};
static int cY[8] = {2,-2,1,-1,2,-2,1,-1};

bool checkEmptyWarnsdorff(int** board, int size, int x, int y){
    return x >= 0 && y >= 0 && x < size && y < size && board[x][y] == -1;
}
 
int getValidMoveWarnsdorff(int** board, int size, int x, int y){
    int count = 0;
    for (int i = 0; i < 8; i++){
        if(checkEmptyWarnsdorff(board, size, x + cX[i], y + cY[i])) count++;
    }
    return count;
}

bool checkNextMoveWarnsdorff(int** board, int size, int &x, int &y, unsigned long long &total){
    int minIdx = -1, count, min = size + 1, nextX, nextY;
    for (int i = 0; i < 8; i++){
        nextX = x + cX[i];
        nextY = y + cY[i];
        count = getValidMoveWarnsdorff(board, size, nextX, nextY);
        if (checkEmptyWarnsdorff(board, size, nextX, nextY) && count < min) {
            minIdx = i;
            min = count;
        }
    }
    if (minIdx == -1) return false;
    nextX = x + cX[minIdx];
    nextY = y + cY[minIdx];
    if(nextX != x && nextY != y){
        board[nextX][nextY] = board[x][y] + 1;
        total++;
        x = nextX;
        y = nextY;
    }
    return true;
}

void outputFileWarnsdorff(int** board, int size, int x, int y, unsigned long long total, std::chrono::duration<double> elapsed_seconds){
    std::fstream f(mssv + algo2 + ".txt", std::fstream::out);
    f << x << " " << y << " " << size << "\n";
    f << total << "\n";
    f << elapsed_seconds.count() << "\n";
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            f << " " << std::setw(2) << board[i][j] << " ";
        }
        f << "\n";
    }
    f.close();
}
 
void warnsdorffKT(int argc, char* argv[]){
    int size = std::atoi(argv[6]);
    int ** board = new int*[size];
    for(int i = 0; i < size; i++)
        board[i] = new int[size];

    int x, y, startX, startY;
    unsigned long long total = 1;
    auto start = std::chrono::system_clock::now();
    while(true){
        x = std::atoi(argv[2]);
        y = std::atoi(argv[4]);
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                board[i][j] = -1;
        startX = x--;
        startY = y--;
        board[y][x] = 1;
        for (int i = 0; i < size * size-1; i++)
            if (!checkNextMoveWarnsdorff(board, size, y, x, total)) continue;
        break;
    }
    auto end  = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    outputFileWarnsdorff(board, size, startX, startY, total, elapsed_seconds);

    for(int i = 0; i < size; i++)
        delete[] board[i];
    delete[] board;
}
 
int main(int argc, char* argv[]){
    if(argc == 7){
        backtrackingKT(argc, argv);
        warnsdorffKT(argc, argv);
        std::cout << "Solved!";
    }
    return 0;
}