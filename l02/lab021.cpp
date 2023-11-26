// lab02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
const int p = 50;
const int b = 50;
int arr[p][b];
#include <iomanip>      // std::setprecision


void createppm() {
    ofstream file;
    file.open("l02.ppm");
    file << "P3\n" << p << " " << b << "\n1\n";
    for (int i = 0; i < p; ++i)
    {
        for (int j = 0; j < b; ++j)
        {
            file << arr[i][j] << " ";
            file << arr[i][j] << " ";
            file << arr[i][j] << " ";
        }
        file << std::endl;
    }
    file.close();
}
double area(double x, double y, double x1, double y1, double x2, double y2) {
    double a = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
    double b = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    double c = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
    double s = (a + b + c) * 0.5;
    double area = sqrt((s - a) * (s - b) * (s - c) * s);
    return area;
}
void partone() {
    srand(time(NULL));
    double x = (double)rand() / (RAND_MAX);
    double y = (double)rand() / (RAND_MAX);
    double x1 = (double)rand() / (RAND_MAX);
    double y1 = (double)rand() / (RAND_MAX);
    double x2 = (double)rand() / (RAND_MAX);
    double y2 = (double)rand() / (RAND_MAX);
    double x3, y3;
    bool check = true;
    // cout << area(300.0, 300.0, 300.0, 700.0, 600.0, 300.0);

    ofstream file, file2;
    file.open("log.txt");
    while (check) {
        x3 = (double)rand() / (RAND_MAX);
        y3 = (double)rand() / (RAND_MAX);
        double bigtri3 = area(x, y, x2, y2, x3, y3); //case 3
        double bigtri2 = area(x1, y1, x2, y2, x3, y3); //case 2
        double bigtri1 = area(x, y, x1, y1, x3, y3); //case 4
        double bigtri = area(x, y, x1, y1, x2, y2); //case 1
        double smalltri = area(x, y, x1, y1, x3, y3); //0 1 3
        double smalltri1 = area(x, y, x2, y2, x3, y3); //0 2 3
        double smalltri2 = area(x1, y1, x2, y2, x3, y3); //1 2 3
        double smalltri3 = area(x, y, x1, y1, x2, y2); // 0 1 2
        cout << std::setprecision(19) << "testing point (" << x3 << ", " << y3 << ")" << endl;
        file << std::setprecision(19) << "testing point (" << x3 << ", " << y3 << ")" << endl;
        // cout << "this is the big one " <<bigtri << "this is the three" << smalltri << " " << smalltri2 << " " << smalltri3;
        if (abs((smalltri + smalltri1 + smalltri2) - bigtri) >= 0.01 && abs((smalltri + smalltri1 + smalltri3) - bigtri2) >= 0.01 && abs((smalltri + smalltri2 + smalltri3) - bigtri3) >= 0.01
            && abs((smalltri3 + smalltri2 + smalltri1) - bigtri1) >= 0.01) { //0 1 2   
            check = false;
        }
    }
    //array<double, 8> sim{} = { x, y, x1, y1, x2, y2, x3, y3 };
    file2.open("points.txt");
    file2 << std::setprecision(19) << "(" << x << "," << y << ") , (" << x1 << "," << y1 << ") , (" << x2 << "," << y2 << "), (" << x3 << "," << y3 << ")";
    std::cout << std::setprecision(19) << "(" << x << "," << y << ") , (" << x1 << "," << y1 << ") , (" << x2 << "," << y2 << "), (" << x3 << "," << y3 << ")";
    file2.close();
    file.close();
}
int main()
{
    partone();

    //Line a = Line(); 
    //a.totalbresenham(x, y, x1, y1);
    //Line f = Line();
    //f.totalbresenham(x1, y1, x2, y2);
    //Line c = Line();
    //c.totalbresenham(x2, y2, x, y);
    return 0;
}