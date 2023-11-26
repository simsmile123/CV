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
int x10, y10;
int** arr3;
auto temp = vector<vector<int>>();
auto bresy = vector<vector<int>>();
auto bresy2 = vector<vector<int>>();
auto UnRAllAngle = vector<vector<double>>();
//saves points info
class Point {

public:     // available member methods
    Point()
    {
        x = 800.0;
        y = 800.0;
    }
    Point(double x1, double y1) {
        x = x1;
        y = y1;
    }   // constructor; called when the new is called
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
    //what goes into this?
    Point(const Point& pt) { x = pt.x; y = pt.y; }
    void toString() {
        cout << "(" << x << "," << y << ")";
    }
    ~Point() {

    }  // destructor; called when the delete is called
private:
    double x;
    double y;

};
//saves line info
class Line {
public:     // available member method
    Line() {
        p1 = Point(99.0, 99.0);
        p2 = Point(99.0, 99.0);
        b = 99.0;
        m = 99.0;
        und = false;
    } //what goes into default constructors??
    Line(Point pt1, double m2, double b2) {
        p1 = pt1;
        b = b2;
        p2 = Point(99.0, 99.0);
        und = false;
        m = m2;
    }
    Line(Point pt1, Point pt2, double m2, double b2) {
        p1 = pt1;
        p2 = pt2;
        b = b2;
        und = false;
        m = m2;
    }   // constructor; called when the new is called
    Line(Point pt1, Point pt2) {
        p1 = pt1;
        p2 = pt2;
        b = 99.0;
        m = 99.0;
        und = false;
    }
    Line(const Line& pt) { p1 = pt.p1; p2 = pt.p2; m = pt.m; b = pt.b; und = false; }
    ~Line() {
        // cout << "point delete";
    }  // destructor; called when the delete is called
    double getP1x() {
        return p1.getX();
    }
    double getP2x() {
        return  p2.getX();
    }
    double getP1y() {
        return p1.getY();
    }
    double getP2y() {
        return  p2.getY();
    }
    double getm() {
        return m;
    }
    double getb() {
        return b;
    }
private:
    Point p1;
    //Point* p3;
    Point p2;
    bool und;
    double m;
    double b;

};
//shades in everything
void illuminate(int bx, int by)
{
    // cout << bx << by << "\n";
    if (0 < bx and bx < y10 and 0 < by and by < x10) {
        bresy[bx][by] += 1;
    }

}
//all the bresenhams
void bresenhamxpos(double x1, double y1, double x2, double y2) {
    //cout << "xpos";
    if (x1 > x2) //(5,0) (0,3)
    {
        swap(y1, y2);
        swap(x1, x2);
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    int j = y1;
    int e = dy - dx;
    for (int i = x1; i < x2; i++)
    {
        illuminate(i, j);
        if (e >= 0)
        {
            j += 1;
            e -= dx;
        }
        e += dy;
    }
}
void bresenhamxneg(double x1, double y1, double x2, double y2) {
    //cout << "xneg";
    int dx = x2 - x1;
    int dy = y2 - y1;
    int add = 1; //for case one you go up one x value each time to ensure each has one box filled
    //some cases you need to go down one x value
    //others you need to go down/up for each y value
    if (x1 > x2) //(5,0) (0,3)
    {
        swap(y1, y2);
        dy *= -1;
        swap(x1, x2);
        dx *= -1;
    }
    if (dy < 0) //if it's negative like (0,0) (5,3) this just flips it
    {
        add *= -1;
        dy *= -1;
    }
    int j = y1;
    int e = dy - dx;
    for (int i = x1; i < x2; i++)
    {
        illuminate(i, j);
        if (e >= 0)
        {
            j += add;
            e -= dx;
        }
        e += dy;
    }
}
void bresenhamypos(double x1, double y1, double x2, double y2) {
    //cout << "ypos";
    if (y1 > y2) //(5,0) (0,3)
    {
        swap(y1, y2);
        swap(x1, x2);
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    int j = x1;
    int e = dy - dx;
    for (int i = y1; i < y2; i++)
    {
        illuminate(j, i);
        if (e >= 0)
        {
            j += 1;
            e -= dy;
        }
        e += dx;
    }

}
void bresenhamyneg(double x1, double y1, double x2, double y2) {
    // cout << "yneg";
    int dx = x2 - x1;
    int dy = y2 - y1;
    int add = 1;
    if (y1 > y2)
    {
        swap(y1, y2);
        dy *= -1;
        swap(x1, x2);
        dx *= -1;
    }
    if (dx < 0)
    {
        add *= -1;
        dx *= -1;
    }
    int j = x1;
    int e = dy - dx;
    for (int i = y1; i < y2; i++)
    {
        illuminate(j, i);
        if (e >= 0)
        {
            j += add;
            e -= dy;
        }
        e += dx;
    }
}

void bresenham5(double x1, double y1, double x2, double y2) { // if y1 and y2 = 0
    if (x1 > x2) {
        swap(x1, x2);
    }
    for (int i = x1; i < x2; i++) {
        illuminate(i, y1);
    }
}
void bresenham6(double x1, double y1, double x2, double y2) { //if x1 and x2 = 0
    if (y1 > y2) {
        swap(y1, y2);
    }
    for (int i = y1; i < y2; i++) {
        illuminate(x1, i);
    }
}
//picks the right bresenham
void totalbresenham(Line x) {
    //double x3, y3, x4, y4;
    //x3 = 0;
    //x4 = 799;
    //y3 = x.getb();
    //cout << "totalbres d inter" << x.getb();
    //y4 = x.getb() + x.getm() * x4; x is row y is col
    double x1 = x.getP1x();
    double y1 = x.getP1y();
    double x2 = x.getP2x();
    double y2 = x.getP2y();
    int dy = y2 - y1;
    int dx = x2 - x1;

    double fraction = (double)dy / dx;
    if (abs(dx) > abs(dy))
    {
        if (fraction > 0) {
            bresenhamxpos(x1, y1, x2, y2);
        }
        else if (fraction < 0) {
            bresenhamxneg(x1, y1, x2, y2);
        }
        else if (x1 == x2) {
            bresenham6(x1, y1, x2, y2);
        }
        else if (y1 == y2) {
            bresenham5(x1, y1, x2, y2);
        }

    }
    else {
        if (fraction > 0) {
            bresenhamypos(x1, y1, x2, y2);
        }
        else if (fraction < 0) {
            bresenhamyneg(x1, y1, x2, y2);
        }
        else if (x1 == x2) {
            bresenham6(x1, y1, x2, y2);
        }
        else if (y1 == y2) {
            bresenham5(x1, y1, x2, y2);
        }
    }
}

void createppm(int row, int col, int max, string output, vector<vector<int> > temp3, bool zz) { //y10 is col x10 is row 
    ofstream file;
    file.open(output); //change this when he gives the parameter
    file << "P3\n" << row << " " << col << "\n" << max << "\n";
    cout << endl << "ur in " << row << " " << col;
    if (zz == true) {
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < row; j++) {
                if ((temp3[i][j] != -5) && (temp3[i][j] != -11)) {
                    file << temp3[i][j] << " ";
                    file << temp3[i][j] << " ";
                    file << temp3[i][j] << " ";
                }
                if (temp3[i][j] == -5) {
                    file << max << " ";
                    file << 0 << " ";
                    file << 0 << " ";
                }
                if (temp3[i][j] == -11) {
                    file << arr3[i][j] << " ";
                    file << arr3[i][j + 1] << " ";
                    file << arr3[i][j + 2] << " ";
                }
            }
            file << std::endl;
        } //this is 600 by 400
        file.close();
    }
    else {
        cout << "just disregard this";
    }
}
void bw_converter(int row, int col, int max, string output) {
    for (int g = 0; g < col; g++) {
        temp.push_back(vector<int>(row, 0));
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row * 3; j += 3) {
            int temp2 = (int)((arr3[i][j] + arr3[i][j + 1] + arr3[i][j + 2]) / 3);
            int x = j / 3;
            temp[i][x] = temp2;
        }
    } //this array has 1800 by 400
    createppm(row, col, max, output, temp, true);
}
void sobel_operator(int row, int col, int max, int threshold, string grey) { //this one needs 600 by 400
    bw_converter(row, col, max, grey);
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
    createppm(row, col, 1, "imagem", temp, true);
}

void recuring(int col, int row) { //col is x, row is y
    //if (temp[col][row] == 0 || temp[col][row] == 1 || temp[col][row] == 3) {
    //   
    //}
    if (temp[col][row] == 2) {
        temp[col][row] = 3;
        //cout << "can it get here";
        int neigha[8][2] = { {-1, 0},{-1, 1},{-1, -1},{0, 1},{0, -1},{1, 0},{1, 1},{1, -1} };
        for (int i = 0; i < 8; i++) { //do it 8 times
            int row1 = row + neigha[i][0];
            int col1 = col + neigha[i][1];
            if (temp[col1][row1] == 1) {
                temp[col1][row1] = 2;
            }
            else if (temp[col1][row1] == 2 || temp[col1][row1] == 3) {
                continue;
            }
            recuring(col1, row1);
        }
    }
}
void algo(int row, int col, int high, int low, string output, string both, string hys) {
    auto AllGx = vector<vector<int>>();
    for (int g = 0; g < col; g++) {
        AllGx.push_back(vector<int>(row, 0));
    }
    auto AllGy = vector<vector<int>>();
    for (int g = 0; g < col; g++) {
        AllGy.push_back(vector<int>(row, 0));
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == 0 || j == 0 || i == col - 1 || j == row - 1) { //outside points 
                AllGx[i][j] = 0;
                AllGy[i][j] = 0;
            }
            else {
                int Gx = temp[i - 1][j - 1] * 1 +
                    temp[i][j - 1] * 0 +
                    temp[i + 1][j - 1] * -1 +
                    temp[i - 1][j] * 2 +
                    temp[i][j] * 0 +
                    temp[i + 1][j] * -2 +
                    temp[i - 1][j + 1] * 1 +
                    temp[i][j + 1] * 0 +
                    temp[i + 1][j + 1] * -1;
                int Gy = temp[i - 1][j - 1] * -1
                    + temp[i][j - 1] * -2
                    + temp[i + 1][j - 1] * -1
                    + temp[i - 1][j] * 0
                    + temp[i][j] * 0
                    + temp[i + 1][j] * 0
                    + temp[i - 1][j + 1] * 1
                    + temp[i][j + 1] * 2
                    + temp[i + 1][j + 1] * 1;
                // int Gx = temp[i][j];
                // int Gy = temp[i][j];
                AllGx[i][j] = Gx;
                AllGy[i][j] = Gy;
            }
        }
    }
    //auto AllAngle = vector<vector<int>>();
    for (int g = 0; g < col; g++) {
        UnRAllAngle.push_back(vector<double>(row, 0));
    }
    auto AllMagn = vector<vector<int>>();
    for (int g = 0; g < col; g++) {
        AllMagn.push_back(vector<int>(row, 0));
    }
    auto AllAngle = vector<vector<int>>();
    for (int g = 0; g < col; g++) {
        AllAngle.push_back(vector<int>(row, 0));
    }
    double comparingAngle;
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == 0 || j == 0 || i == col - 1 || j == row - 1) { //outside points 
                temp[i][j] = 0;
            }
            int magnitude = sqrt(AllGx[i][j] * AllGx[i][j] + AllGy[i][j] * AllGy[i][j]);
            if (magnitude > high) {
                temp[i][j] = 2;
            }
            else if (magnitude > low) {
                temp[i][j] = 1;
            }
            else {
                temp[i][j] = 0;
            }
            AllMagn[i][j] = magnitude;
            comparingAngle = atan2(AllGy[i][j], AllGx[i][j]) * 180 / 3.1415; //216
            UnRAllAngle[i][j] = atan2(AllGy[i][j], AllGx[i][j]);
            AllAngle[i][j] = floor((comparingAngle / 45)) * 45;
        }
    }
    // createppm(row, col, 2, "temp.ppm", temp);
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (col == 0 || row == 0 || col == x10 - 1 || row == y10 - 1) { //outside points 
                temp[col][row] = 0;
            }
            else {
                recuring(i, j);
            }
        }
        //cout << "did it get here tho??";
    }
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
    createppm(row, col, 1, hys, temp, true);
    cout << endl << "can you get here";
    //int** temp2;
    //temp2 = new int* [col];
    //for (int k = 0; k < col; k++) {
    //    temp2[k] = new int[row]; //600 by 400
    //}
    auto temp2 = vector<vector<int>>();
    for (int g = 0; g < col; g++) {
        temp2.push_back(vector<int>(row, 0));
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            if (i == col - 1 || j == row - 1 || i == 0 || j == 0) {
                temp2[i][j] = 0;
                continue;
            }
            int temps;
            temps = abs(AllAngle[i][j]);
            int magnrn = AllMagn[i][j];
            if (temps == 0 || temps == 180)
            {
                if ((magnrn >= AllMagn[i][j - 1]) && (magnrn >= AllMagn[i][j + 1])) {
                    magnrn = 1;
                }
                else {
                    magnrn = 0;
                }
            }
            else if (temps == 45)
            {
                if ((magnrn >= AllMagn[i - 1][j + 1]) && (magnrn >= AllMagn[i + 1][j - 1])) {
                    magnrn = 1;
                }
                else {
                    magnrn = 0;
                }
            }
            else if (temps == 90)
            {
                if ((magnrn >= AllMagn[i - 1][j]) && (magnrn >= AllMagn[i + 1][j])) {
                    magnrn = 1;
                }
                else {
                    magnrn = 0;
                }
            }
            else
            {
                if ((magnrn >= AllMagn[i - 1][j - 1]) && (magnrn >= AllMagn[i + 1][j + 1])) {
                    magnrn = 1;
                }
                else {
                    magnrn = 0;
                }
            }
            temp2[i][j] = magnrn;
        }
    }
    createppm(row, col, 1, output, temp2, true);
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
    createppm(row, col, 1, both, temp, true);
}
void partthree(int high, int low, string filename, string output, string gre, string both, string hys) {
    ifstream File;
    int row, col, max;
    File.open(filename); //change this for all .ppm files
    char* temp3 = new char[2];
    File.read(temp3, 2); //p3
    File >> row; //800 by 200 or whatever 
    File >> col;
    File >> max;
    cout << row << " " << col << endl; //800 600
    arr3 = new int* [col];
    for (int i = 0; i < col; i++) {
        arr3[i] = new int[row * 3];
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row * 3; j++) {
            arr3[i][j] = 1;
        }
    }
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row * 3; j++) {
            File >> arr3[i][j];
        }
    }
    x10 = row; //800
    y10 = col; //600
    bw_converter(row, col, max, gre);
    algo(x10, y10, high, low, output, both, hys); //change these to include all 
}
void testcolor(int row, int col, int max, string output, vector<vector<int>> temp3) { //y10 is col x10 is row 
    ofstream file;
    file.open(output); //change this when he gives the parameter
    file << "P3\n" << row << " " << col << "\n" << max << "\n";
    cout << endl << "ur in " << row << " " << col;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++) {
            if (temp3[i][j] == -11) {
                file << arr3[i][j * 3] << " ";
                file << arr3[i][j * 3 + 1] << " ";
                file << arr3[i][j * 3 + 2] << " ";
            }
            if (temp3[i][j] == -5) {
                file << max << " ";
                file << 0 << " ";
                file << 0 << " ";
            }
        }
        file << std::endl;
    } //this is 600 by 400
    file.close();
}
void illuminateRed(int bx, int by) {
    if (0 < bx and bx < y10 and 0 < by and by < x10) {
        bresy[bx][by] = -5;
    }
}
void circle(double r, Point p) {
    //double cy1 = p.getY();
    //double cx1 = p.getX();
    double cy = p.getY();
    double cx = p.getX();
    int x, y, xmax, y2, y2_new, ty;
    xmax = (int)(r * 0.70710678); // maximum x at radius/sqrt(2)
    y = r;
    y2 = y * y;
    ty = (2 * y) - 1;
    y2_new = y2;
    for (x = 0; x <= xmax; x++) {
        if ((y2 - y2_new) >= ty) {
            y2 -= ty;
            y -= 1;
            ty -= 2;
        }
        illuminateRed(x + cx, y + cy);
        illuminateRed(x + cx, -y + cy);
        illuminateRed(-x + cx, y + cy);
        illuminateRed(-x + cx, -y + cy);
        illuminateRed(y + cx, x + cy);
        illuminateRed(y + cx, -x + cy);
        illuminateRed(-y + cx, x + cy);
        illuminateRed(-y + cx, -x + cy);
        y2_new -= (2 * x) + 3;
    }
}
//void 
void parttwo(int TC, int highthres, int lowerthres, string filename, string nms, string grey, string fin, string outfile, string www, string imageC) { // only call after doing nms and cannyedge, use temp AFTER algo() called
    //add a bunch of bresenhams at the edges so for like every 5th 1, add line
    partthree(highthres, lowerthres, filename, nms, grey, fin, outfile); //imagef contains what we should use, imagef info is in int ** temp

    for (int g = 0; g < y10; g++) { //col
        bresy.push_back(vector<int>(x10, 0)); //row
    }
    //int lm = 0;
    for (int i = 0; i < y10; i++) { //col
        for (int j = 0; j < x10; j++) { //row
            if (temp[i][j] == 1) {
                //lm += 1;
                //if (lm <= 20) {
 /*                   cout << "this is your angle" << UnRAllAngle[i][j];
                    cout << "this is your point" << i << " " << j;*/
                int x8 = (int)(j + (x10 * cos(UnRAllAngle[i][j])));
                int y8 = (int)(i + (y10 * sin(UnRAllAngle[i][j])));
                int x80 = (int)(j - (x10 * cos(UnRAllAngle[i][j])));
                int y80 = (int)(i - (y10 * sin(UnRAllAngle[i][j])));
                totalbresenham(Line(Point(y80, x80), Point(y8, x8)));
                //}
            }
        }
    }
    //totalbresenham(Line(Point(200, 300), Point(400, 500)));
    //cout << " " << lm << endl;
    int max = 0;
    for (int i = 0; i < y10; i++) {
        for (int j = 0; j < x10; j++) {
            if (bresy[i][j] > max) {
                //cout << bresy[i][j] << " "; //how is max still 0 if im changin bresy via totalbresenham
                max = bresy[i][j];
            }
        }
    }
    cout << endl << "THis is the highest illum : " << max << endl;
    createppm(x10, y10, max, www, bresy, true);

    //what do i do after this? how do i get the red circles on top of the og pic 
    //first get red circles and only the red waitttt

    for (int i = 0; i < y10; i++) {
        for (int j = 0; j < x10; j++) {
            if (bresy[i][j] > TC) {
                //  circle(1, Point(i, j)); // fix this to show red and circles  
                circle(2, Point(i, j));
                circle(3, Point(i, j));
                // circle(4, Point(i, j));
                 //bresy[i][j] = 0;
            }
            bresy[i][j] = -11;
        }
    }
    // circle(2, Point(400, 400));
    testcolor(x10, y10, 255, imageC, bresy);
    //createppm(x10, y10, 255, "imagetest", bresy, true);
    //auto count_rr = vector<vector<int>>();
    //for (int g = 0; g < y10; g++) { //col
    //    count_rr.push_back(vector<int>(x10, 0)); //row
    //}
    //int min = 10;
    //int max = 100;
    //auto vector_holdrr = vector<vector<int>>();
    //for (int i = 0; i < y10; i++)
    //{
    //    for (int j = 0; j < x10; j++) {
    //        if (bresy[i][j] == -5) {
    //            //array with radius range, add all the edges
    //            auto vector_count = vector<int>();
    //            for (int x = min; x < max; x++){
    //                //temp
    //                //i, j
    //                radius_out(i, j, x);
    //            }
    //        }
    //    }
    //}
}
int main(int argc, char** argv)
{
    //high, low, input, output
    int lowerthres, highthres, TC;
    string outfile, filename, grey, nms, fin, www, imageC;
    TC = 30;
    lowerthres = 200;
    highthres = 400;
    outfile = "image1.ppm";
    nms = "image2.ppm";
    grey = "imageg.ppm";
    filename = "onecircle.ppm";
    fin = "imagef.ppm";
    www = "imagev.ppm";
    imageC = "imageCC.ppm";
    // -f1 myimage1.ppm -f2 myimage2.ppm -ff myimagef.ppm -TC 300 -fv myimagev.ppm -fcc myimageCC.ppm
    for (int i = 0; i < argc; ++i) {
        //cout << argv[i] << "\n";
        if (strcmp(argv[i], "-f") == 0) {
            filename = argv[i + 1];
            cout << filename;
        }
        if (strcmp(argv[i], "-fv") == 0) {
            www = argv[i + 1];
            cout << www;
        }
        if (strcmp(argv[i], "-fcc") == 0) {
            imageC = argv[i + 1];
            cout << imageC;
        }
        if (strcmp(argv[i], "-TC") == 0) {
            TC = stoi(argv[i + 1]);
            cout << TC;
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
        if (strcmp(argv[i], "-f1") == 0) {
            outfile = argv[i + 1];
            cout << outfile;
        }
    }
    parttwo(TC, highthres, lowerthres, filename, nms, grey, fin, outfile, www, imageC);
}