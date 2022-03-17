#include <iostream>
#include <fstream>
#include <iomanip>
 
static int cX[8] = {1,1,2,2,-1,-1,-2,-2};
static int cY[8] = {2,-2,1,-1,2,-2,1,-1};

bool checkEmptyWarnsdorff(int** board, int size, int x, int y){
    return x >= 0 && y >= 0 && x < size && y < size && board[x][y] == -1;
}
 
int getDegreeWarnsdorff(int** board, int size, int x, int y){
    int count = 0;
    for (int i = 0; i < 8; i++){
        if(checkEmptyWarnsdorff(board, size, x + cX[i], y + cY[i])) count++;
    }
    return count;
}

bool checkNextMoveWarnsdorff(int** board, int size, int* x, int* y){
    int minDegIdx = -1, count, minDeg = size + 1, nextX, nextY;
    for (int i = 0; i < 8; i++){
        nextX = *x + cX[i];
        nextY = *y + cY[i];
        count = getDegreeWarnsdorff(board, size, nextX, nextY);
        if (checkEmptyWarnsdorff(board, size, nextX, nextY) && count < minDeg) {
            minDegIdx = i;
            minDeg = count;
        }
    }
    if (minDegIdx == -1) return false;
    nextX = *x + cX[minDegIdx];
    nextY = *y + cY[minDegIdx];
    board[nextX][nextY] = board[*x][*y] + 1;
    *x = nextX;
    *y = nextY;

    return true;
}

void outputFile(int** board, int size, int x, int y, int total, std::chrono::duration<double> elapsed_seconds){
    std::fstream f("20127370_heuristic.txt", std::fstream::out);
    f << x << " " << y << " " << size << "\n";
    f << total << "\n";
    f << elapsed_seconds.count() << "\n";
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            f << " " << std::setw(2) << board[i][j] << " ";
        }
        f << "\n";
    }
}
 
void findClosedTourWarnsdorff(int argc, char* argv[]){
    int size = std::atoi(argv[6]);
    int ** board = new int*[size];
    for(int i = 0; i < size; i++){
        board[i] = new int[size];
    }
    int x, y, total, startX, startY;
    auto start = std::chrono::system_clock::now();
    while(true){
        x = std::atoi(argv[2]);
        y = std::atoi(argv[4]);
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                board[i][j] = -1;
        total = 1;
        startX = --x;
        startY = --y;
        board[x][y] = 1;
        for (int i = 0; i < size * size-1; i++)
            if (!checkNextMoveWarnsdorff(board, size, &x, &y)) continue;
        break;
    }
    auto end  = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    outputFile(board, size, startX, startY, total, elapsed_seconds);

    for(int i = 0; i < size; i++)
        delete[] board[i];
    delete[] board;
}
 
int main(int argc, char* argv[]){
    findClosedTourWarnsdorff(argc, argv);
    return 0;
}