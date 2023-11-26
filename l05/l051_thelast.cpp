//Simrith Ranjan, Period 5, 12/14/2022
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>      // std::setprecision
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <string>
#include <stack>
using namespace std;
int** arr;
void createppm(bool name, int row, int col) {
    ofstream file;
    if (name == true) {
        file.open("imageg.ppm");
    }
    else {
        file.open("imagem.ppm");
    }
    file << "P3\n" << row << " " << col << "\n1\n";
    cout << endl << "ur in " << row << " " << col;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j += 3) {
            file << arr[i][j] << " ";
            file << arr[i][j] << " ";
            file << arr[i][j] << " ";
        }
        file << std::endl;
    }
    file.close();
}
void bw_converter() {
    int row, col, max;
    ifstream File;
    File.open("test.ppm");
    char* temp = new char[2];
    File.read(temp, 2); //p3
    File >> row; //800 by 200 or whatever 
    File >> col;
    File >> max;
    cout << row << " " << col << endl;
    arr = new int* [col];
    for (int i = 0; i < col; i++) {
        arr[i] = new int[row * 3];
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row * 3; j++) {
            arr[i][j] = 1;
        }
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row * 3; j++) {
            File >> arr[i][j];
        }
    }

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < (row * 3) - 3; j += 3) {
            int temp = (int)((arr[i][j] + arr[i][j + 1] + arr[i][j + 2]) / 3);
            arr[i][j] = temp;
            arr[i][j + 1] = temp;
            arr[i][j + 2] = temp;
        }
    }
    createppm(true, row, col);
}

//void cannyedge_detect(int thres) {
//    bw_converter();
//    // createppm(true);
//}
void partone() {
    bw_converter();
}

int main()
{
    partone();
}