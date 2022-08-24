#include <iostream>
#include <vector>
using namespace std;


void printSudoku(int arr[9][9]) {
	cout << "-------------------------" << endl;
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++)
			cout << arr[y][x] << " ";
		cout << endl;
	}
	cout << "-------------------------" << endl;

}
bool canplace (int arr[9][9],int row ,int col, int n){
    if (arr[row][col] != 0) return false;
    bool status = true;
    int gredx = (col/3) *3;
    int gredy = (row/3) *3;
    for (int i =0;i<9;i++){
        if (arr[row][i]==n){ status=false; break;}
        if (arr[i][col]==n){ status=false;break;}
        if (arr[gredy + i / 3][gredx + i % 3] == n){ status=false;break;}
    }
    return status;
}

void findNext(int arr[9][9],int row,int col,int &rowNext,int &colNext){
    int allIndexes = 82;
    for(int i = row * 9 + col + 1 ;i<9*9 ;i++){
        if(arr[i/9][i%9]==0){
            allIndexes=i;
            break;
        }
    }
    rowNext = allIndexes /9;
    colNext = allIndexes %9;

}

void copyArray(int arr[9][9], int arrCpy[9][9]) {
	for (int y = 0; y < 9; y++)
		for (int x = 0; x < 9; x++)
			arrCpy[y][x] = arr[y][x];
}

std::vector<int> findPlaceables(int arr[9][9], int row, int col) {
	vector<int> placebles = {};
	for (int n = 1; n <= 9; n++)
		if (canplace(arr, row, col, n)) placebles.push_back(n);
	return placebles;
}

bool solveSudoku(int arr[9][9], int row, int col)
{

	if (row > 8) return true;
	if (arr[row][col] != 0) {
		int rowNext, colNext;
		findNext(arr, row, col, rowNext, colNext);
		return solveSudoku(arr, rowNext, colNext);
	}

	std::vector<int> placebles = findPlaceables(arr, row, col);

	if (placebles.size() == 0) {

		return false;

	};

	bool status = false;
	for (int i = 0; i < placebles.size(); i++) {
		int n = placebles[i];
		int arrCpy[9][9];
		copyArray(arr, arrCpy);
		arrCpy[row][col] = n;
		int rowNext = row;
		int colNext = col;
		findNext(arrCpy, row, col, rowNext, colNext);
		if (solveSudoku(arrCpy, rowNext, colNext)) {
			copyArray(arrCpy, arr);
			status = true;
			break;
		}
	}
	return status;
}




int main()
{

	int sodoku[9][9] = {
		{5,3,0,0,7,0,0,0,0},
		{6,0,0,1,9,5,0,0,0},
		{0,9,8,0,0,0,0,6,0},
		{8,0,0,0,6,0,0,0,3},
		{4,0,0,8,0,3,0,0,1},
		{7,0,0,0,2,0,0,0,6},
		{0,6,0,0,0,0,2,8,0},
		{0,0,0,4,1,9,0,0,5},
		{0,0,0,0,8,0,0,7,9}
	};

	if (solveSudoku(sodoku, 0, 0)) cout << "successfully solved board!" << std::endl;
	printSudoku(sodoku);

	return 0;
}

