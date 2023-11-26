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
#include <list>
#include <array>
#include <cstring>
using namespace std;
int x, y;
int** arr;
int** temp;
void createppm(int row, int col, int max, string output, int** temp) {
    ofstream file;
    file.open(output); //change this when he gives the parameter
    file << "P3\n" << row << " " << col << "\n" << max << "\n";
    cout << endl << "ur in " << row << " " << col;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++) {
            file << temp[i][j] << " ";
            file << temp[i][j] << " ";
            file << temp[i][j] << " ";
        }
        file << std::endl;
    } //this is 600 by 400
    file.close();
}
void bw_converter(int row, int col, int max, string output) {
    temp = new int* [col];
    for (int k = 0; k < col; k++) {
        temp[k] = new int[row]; //600 by 400
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row * 3; j += 3) {
            int temp2 = (int)((arr[i][j] + arr[i][j + 1] + arr[i][j + 2]) / 3);
            arr[i][j] = temp2;
            arr[i][j + 1] = temp2;
            arr[i][j + 2] = temp2;
            int x = j / 3;
            temp[i][x] = temp2;
        }
    } //this array has 1800 by 400
    createppm(row, col, max, output, temp);
}
void sobel_operator(int row, int col, int max, int threshold, string grey) { //this one needs 600 by 400
    bw_converter(row, col, max, grey);
    // int** temp;
     //for (int i = 0; i < col; i++)
     //{
     //    for (int j = 0; j < row*3; j +=3) { //makes a 600 by 400, just keeping r instead of rgb
     //        int x = j / 3;
     //        temp[i][x] = arr[i][j];
     //    }
     //}
    int** AllGx;
    AllGx = new int* [col];
    for (int k = 0; k < col; k++) {
        AllGx[k] = new int[row]; //600 by 400
    }
    int** AllGy;
    AllGy = new int* [col];
    for (int k = 0; k < col; k++) {
        AllGy[k] = new int[row]; //600 by 400
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == 0 || j == 0 || i == col - 1 || j == row - 1) { //outside points 
                temp[i][j] = 0;
            }
            else {
                int Gx = temp[i - 1][j - 1] * 1 + temp[i][j - 1] * 0 + temp[i + 1][j - 1] * -1 + temp[i - 1][j] * 2 + temp[i][j] * 0 + temp[i - 1][j] * -2 +
                    temp[i - 1][j + 1] * 1 + temp[i][j + 1] * 0 + temp[i + 1][j + 1] * -1;
                int Gy = temp[i - 1][j - 1] * 1 + temp[i][j - 1] * 2 + temp[i + 1][j - 1] * 1 + temp[i - 1][j] * 0 + temp[i][j] * 0 + temp[i - 1][j] * 0 +
                    temp[i - 1][j + 1] * -1 + temp[i][j + 1] * -2 + temp[i + 1][j + 1] * -1;
                // int Gx = temp[i][j];
                // int Gy = temp[i][j];
                AllGx[i][j] = Gx;
                AllGy[i][j] = Gy;
            }
        }
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            int magnitude = sqrt(AllGx[i][j] * AllGx[i][j] + AllGy[i][j] * AllGy[i][j]);
            if (magnitude > threshold) {
                temp[i][j] = max;
            }
            else {
                temp[i][j] = 0;
            }
        }
    }
    createppm(row, col, 1, "imagem", temp);
}
//void cannyedge_detect(int thres) {
//    bw_converter();
//    // createppm(true);
//}
void partone(string output) {
    int row, col, max;
    ifstream File;
    File.open("image.ppm");
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
    sobel_operator(row, col, max, 100, output);
}

void recuring(int col, int row) { //col is x, row is y
    if (temp[col][row] == 0 || temp[col][row] == 1 || temp[col][row] == 3) {
        return;
    }
    if (col == 0 || row == 0 || col == x - 1 || row == y - 1) { //outside points 
        temp[col][row] = 0;
    }
    if (temp[col][row] == 2) {
        temp[col][row] = 3;
        //cout << "can it get here";
        int neigha[8][2] = { { -1, 0},{-1, 1},{-1, -1},{0, 1},{0, -1},{1, 0},{1, 1},{1, -1} };
        //= [[-1, 0], [-1, 1], [-1, -1], [0, 1], [0, -1], [1, 0], [1, 1], [1, -1]];//{{-1, 0}, {-1, -1}, {-1, 1}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {1,0}};
        for (int i = 0; i < 8; i++) { //do it 8 times
            int row1 = row + neigha[i][0];
            int col1 = col + neigha[i][1];
            if (temp[col1][row1] == 1) {
                temp[col1][row1] = 2;
            }
            if (temp[col1][row1] == 3 || temp[col1][row1] == 2) {
                return;
            }
            recuring(col1, row1);
        }
    }
}
void Hysteresis(int row, int col, int threshold1, int threshold2) {
    int** AllGx;
    AllGx = new int* [col];
    for (int k = 0; k < col; k++) {
        AllGx[k] = new int[row]; //600 by 400
    }
    int** AllGy;
    AllGy = new int* [col];
    for (int k = 0; k < col; k++) {
        AllGy[k] = new int[row]; //600 by 400
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == 0 || j == 0 || i == col - 1 || j == row - 1) { //outside points 
                temp[i][j] = 0;
            }
            else {
                int Gx = temp[i - 1][j - 1] * 1 + temp[i][j - 1] * 0 + temp[i + 1][j - 1] * -1 + temp[i - 1][j] * 2 + temp[i][j] * 0 + temp[i - 1][j] * -2 + temp[i - 1][j + 1] * 1 + temp[i][j + 1] * 0 + temp[i + 1][j + 1] * -1;
                int Gy = temp[i - 1][j - 1] * 1 + temp[i][j - 1] * 2 + temp[i + 1][j - 1] * 1 + temp[i - 1][j] * 0 + temp[i][j] * 0 + temp[i - 1][j] * 0 + temp[i - 1][j + 1] * -1 + temp[i][j + 1] * -2 + temp[i + 1][j + 1] * -1;
                // int Gx = temp[i][j];
                // int Gy = temp[i][j];
                AllGx[i][j] = Gx;
                AllGy[i][j] = Gy;
            }
        }
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            int magnitude = sqrt(AllGx[i][j] * AllGx[i][j] + AllGy[i][j] * AllGy[i][j]);
            if (magnitude > threshold1) {
                temp[i][j] = 2;
            }
            else if (magnitude > threshold2) {
                temp[i][j] = 1;
            }
            else {
                temp[i][j] = 0;
            }
        }
    }
    //now look thro again change connecteds 1s into 2, change 2s to 3s, starting at 3 look for connected ones
    //forloop
    //cout << "last check" << row << " " << col;
    //x = col;
    //y = row;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == 0 || j == 0 || i == col - 1 || j == row - 1) { //outside points 
                temp[i][j] = 0;
            }
            else {
                recuring(i, j);
            }
        }
        //cout << "did it get here tho??";
    }
    // cout << "does it get hereeee";
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (temp[i][j] == 1) {
                temp[i][j] = 0;
            }
            if (temp[i][j] == 3 || temp[i][j] == 2) {
                temp[i][j] = 1;
            }
        }
    }

}
void parttwo(int low, int high, string filename, string output, string gre) {
    int row, col, max;
    ifstream File;
    File.open(filename); //change this for all .ppm files
    char* temp2 = new char[2];
    File.read(temp2, 2); //p3
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
    x = col;
    y = row;
    bw_converter(row, col, max, gre);
    Hysteresis(row, col, high, low); //change these to include all 
    createppm(row, col, 1, output, temp);
}
void algo(int row, int col, int threshold1, int threshold2, string output, string both, string hys) {
    auto AllGx = vector<vector<int>>();
    for (int g = 0; g < col; g++) {
        AllGx.push_back(vector<int>(row, 0));
    }
    auto AllGy = vector<vector<int>>();
    for (int g = 0; g < col; g++) {
        AllGy.push_back(vector<int>(row, 0));
    }
    /*   for (int i = 0; i < col; i++) {
           for (int j = 0; j < row; j++) {
               AllGy[i][j] = 1;
               AllGx[i][j] = 1;
           }
       }*/
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == 0 || j == 0 || i == col - 1 || j == row - 1) { //outside points 
                temp[i][j] = 0;
            }
            else {
                int Gx = temp[i - 1][j - 1] * 1 + temp[i][j - 1] * 0 + temp[i + 1][j - 1] * -1 + temp[i - 1][j] * 2 + temp[i][j] * 0 + temp[i - 1][j] * -2 + temp[i - 1][j + 1] * 1 + temp[i][j + 1] * 0 + temp[i + 1][j + 1] * -1;
                int Gy = temp[i - 1][j - 1] * 1 + temp[i][j - 1] * 2 + temp[i + 1][j - 1] * 1 + temp[i - 1][j] * 0 + temp[i][j] * 0 + temp[i - 1][j] * 0 + temp[i - 1][j + 1] * -1 + temp[i][j + 1] * -2 + temp[i + 1][j + 1] * -1;
                // int Gx = temp[i][j];
                // int Gy = temp[i][j];
                AllGx[i][j] = Gx;
                AllGy[i][j] = Gy;
            }
        }
    }
    auto AllAngle = vector<vector<int>>();
    for (int g = 0; g < col; g++) {
        AllAngle.push_back(vector<int>(row, 0));
    }
    auto AllMagn = vector<vector<int>>();
    for (int g = 0; g < col; g++) {
        AllMagn.push_back(vector<int>(row, 0));
    }
    double comparingAngle;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == 0 || j == 0 || i == col - 1 || j == row - 1) { //outside points 
                temp[i][j] = 0;
            }
            int magnitude = sqrt(AllGx[i][j] * AllGx[i][j] + AllGy[i][j] * AllGy[i][j]);
            if (magnitude > threshold1) {
                temp[i][j] = 2;
            }
            else if (magnitude > threshold2) {
                temp[i][j] = 1;
            }
            else {
                temp[i][j] = 0;
            }
            AllMagn[i][j] = magnitude;
            comparingAngle = atan2(AllGx[i][j], AllGy[i][j]) * 180 / 3.1415; //216
            if (int(comparingAngle) % 45 >= 22.5) //more than half the distance between the two
            {
                AllAngle[i][j] = ceil((comparingAngle / 45)) * 45; //go to top one
            }
            else
            {
                AllAngle[i][j] = floor((comparingAngle / 45)) * 45;
            }
        }
    }
    //delete this part if it meses code
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == 0 || j == 0 || i == col - 1 || j == row - 1) { //outside points 
                temp[i][j] = 0;
            }
            else {
                recuring(i, j);
            }
        }
        //cout << "did it get here tho??";
    }
    // cout << "does it get hereeee";
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (temp[i][j] == 1) {
                temp[i][j] = 0;
            }
            if (temp[i][j] == 3 || temp[i][j] == 2) {
                temp[i][j] = 1;
            }
        }
    }
    createppm(row, col, 1, hys, temp);
    cout << "can you get here";
    int** temp2;
    temp2 = new int* [col];
    for (int k = 0; k < col; k++) {
        temp2[k] = new int[row]; //600 by 400
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == col - 1 || j == row - 1 || i == 0 || j == 0) {
                temp[i][j] = 0;
            }
            int temps;
            temps = abs(AllAngle[i][j]);
            int magnrn = AllMagn[i][j];
            if (temps == 0 || temps == 180)
            {
                if ((magnrn > AllMagn[i][j - 1]) && (magnrn > AllMagn[i][j + 1])) {
                    magnrn = 1;
                }
                else {
                    magnrn = 0;
                }
            }
            else if (temps == 45)
            {
                if ((magnrn > AllMagn[i - 1][j + 1]) && (magnrn > AllMagn[i + 1][j - 1])) {
                    magnrn = 1;
                }
                else {
                    magnrn = 0;
                }
            }
            else if (temps == 90)
            {
                if ((magnrn > AllMagn[i - 1][j]) && (magnrn > AllMagn[i + 1][j])) {
                    magnrn = 1;
                }
                else {
                    magnrn = 0;
                }
            }
            else
            {
                if ((magnrn > AllMagn[i - 1][j - 1]) && (magnrn > AllMagn[i + 1][j + 1])) {
                    magnrn = 1;
                }
                else {
                    magnrn = 0;
                }
            }
            temp2[i][j] = magnrn;
        }
    }
    createppm(row, col, 1, output, temp2);
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (temp2[i][j] == 1 && temp[i][j] == 1) {
                temp[i][j] = 1;
            }
            else {
                temp[i][j] = 0;
            }
        }
    }
    createppm(row, col, 1, both, temp);
}
void partthree(int low, int high, string filename, string output, string gre, string both, string hys) {
    ifstream File;
    int row, col, max;
    File.open(filename); //change this for all .ppm files
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
    x = col;
    y = row;
    bw_converter(row, col, max, gre);
    algo(row, col, high, low, output, both, hys); //change these to include all 
    //createppm(row, col, 1, output);
    //createppm(row, col, 1, both);
}
int main(int argc, char** argv)
{
    // partone();
    //high, low, input, output
    int lowerthres, highthres;
    string outfile, filename, grey, nms, fin;
    lowerthres = 175;
    highthres = 250;
    outfile = "image1.ppm";
    nms = "image2.ppm";
    grey = "imageg.ppm";
    filename = "image.ppm";
    fin = "imagef.ppm";
    for (int i = 0; i < argc; ++i) {
        //cout << argv[i] << "\n";
        if (strcmp(argv[i], "-f") == 0) {
            filename = argv[i + 1];
            cout << filename;
        }
        if (strcmp(argv[i], "-lt") == 0) {
            lowerthres = stoi(argv[i + 1]);
            cout << lowerthres;
        }
        if (strcmp(argv[i], "-fg") == 0) {
            grey = argv[i + 1];
            cout << grey;
        }
        if (strcmp(argv[i], "-ht") == 0) {
            highthres = stoi(argv[i + 1]);
            cout << highthres;
        }
        if (strcmp(argv[i], "-f2") == 0) {
            nms = argv[i + 1];
            cout << nms;
        }
        if (strcmp(argv[i], "-ff") == 0) {
            fin = argv[i + 1];
            cout << fin;
        }
        if (strcmp(argv[i], "-of") == 0) {
            outfile = argv[i + 1];
            cout << outfile;
        }
    }
    // parttwo(lowerthres, highthres, filename, outfile, grey);
    partthree(lowerthres, highthres, filename, nms, grey, fin, outfile);
}