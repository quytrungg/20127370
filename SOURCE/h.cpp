#include <iostream>
 
static int cX[8] = {1,1,2,2,-1,-1,-2,-2};
static int cY[8] = {2,-2,1,-1,2,-2,1,-1};

bool checkLimitsWarnsdorff(int x, int y, int size){
    return x >= 0 && y >= 0 && x < size && y < size;
}

bool checkEmptyWarnsdorff(int* a, int size, int x, int y){
    return checkLimitsWarnsdorff(x, y, size) && a[y*size+x] < 0;
}
 
/* So luong square con lai */
int getDegreeWarnsdorff(int* &a, int size, int x, int y){
    int count = 0;
    for (int i = 0; i < size; i++){
        if(checkEmptyWarnsdorff(a, size, x + cX[i], y + cY[i])) count++;
    }
    return count;
}
 
// Picks next point using Warnsdorff's heuristic.
// Returns false if it is not possible to pick next point.
bool checkNextMoveWarnsdorff(int* &a, int size, int *x, int *y){
    int minDegIdx = -1, c, minDeg = size + 1, nX, nY;
 
    // Try all N adjacent of (*x, *y) starting from a random adjacent. Find the adjacent with minimum degree.
    int start = rand() % size;
    for (int count = 0; count < size; count++){
        int i = (start + count) % size;
        nX = *x + cX[i];
        nY = *y + cY[i];
        c = getDegreeWarnsdorff(a, size, nX, nY);
        if (checkEmptyWarnsdorff(a, size, nX, nY) && c < minDeg) {
            minDegIdx = i;
            minDeg = c;
        }
    }

    if (minDegIdx == -1) return false;
    // Store coordinates of next point
    nX = *x + cX[minDegIdx];
    nY = *y + cY[minDegIdx];
    // Mark next move
    a[nY * size + nX] = a[*y * size + *x] + 1;
    // Update next point
    *x = nX;
    *y = nY;
    return true;
}
 
/* displays the chessboard with all the legal knight's moves */
void printSolutionWarnsdorff(int* a, int size){
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j)
            std::cout << a[j*size+i] << "\t";
        std::cout << "\n";
    }
}
 
/* checks its neighbouring squares */
/* If the knight ends on a square that is one knight's move from the beginning square,
   then tour is closed */
bool checkNeighbour(int size, int x, int y, int xx, int yy){
    for (int i = 0; i < size; i++)
        if (x+cX[i] == xx && y + cY[i] == yy) return true;
    return false;
}
 
/* Generates the legal moves using warnsdorff's heuristics. Returns false if not possible */
bool findClosedTourWarnsdorff(){
    int size;
    std::cout << "Size: ";
    std::cin >> size;
    int* a = new int[size*size];
    for (int i = 0; i< size * size; i++)
        a[i] = -1;
    
    int sX = rand() % size;
    int sY = rand() % size;
    // Current points are same as initial points
    int x = sX, y = sY;
    a[y * size + x] = 1;
 
    // Keep picking next points using Warnsdorff's heuristic
    for (int i = 0; i < size * size-1; ++i){
        if (checkNextMoveWarnsdorff(a, size, &x, &y) == 0) return false;
    }
 
    if (!checkNeighbour(size, x, y, sX, sY)) return false;
    printSolutionWarnsdorff(a, size);
    delete[] a;
    return true;
}
 
// Driver code
int main(int argc, char* argv[]){
    srand(time(NULL));
    while (!findClosedTourWarnsdorff()){;}
    return 0;
}