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

double PI = 3.14159265358979323846;

auto temp = vector<vector<int> >();

auto bresy = vector<vector<int> >();

auto bresy2 = vector<vector<int> >();

auto bresy6 = vector<vector<int> >();

auto UnRAllAngle = vector<vector<double> >();

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

    if (0 < bx and bx < x10 and 0 < by and by < y10) {

        bresy[by][bx] += 1;

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

    //y4 = x.getb() + x.getm() * x4; x is width y is height

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

 

void createppm(int width, int height, int max, string output, vector<vector<int> > temp3, bool zz) { //y10 is height x10 is width

    ofstream file;

    file.open(output); //change this when he gives the parameter

    file << "P3\n" << width << " " << height << "\n" << max << "\n";

    cout << endl << "ur in " << width << " " << height;

    if (zz == true) {

        for (int i = 0; i < height; i++)

        {

            for (int j = 0; j < width; j++) {

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

void bw_converter(int width, int height, int max, string output) {

    for (int g = 0; g < height; g++) {

        temp.push_back(vector<int>(width, 0));

    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width * 3; j += 3) {

            int temp2 = (int)((arr3[i][j] + arr3[i][j + 1] + arr3[i][j + 2]) / 3);

            int x = j / 3;

            temp[i][x] = temp2;

        }

    } //this array has 1800 by 400

    createppm(width, height, max, output, temp, true);

}

void sobel_operator(int width, int height, int max, int threshold, string grey) { //this one needs 600 by 400

    bw_converter(width, height, max, grey);

    int** AllGx;

    AllGx = new int* [height];

    for (int k = 0; k < height; k++) {

        AllGx[k] = new int[width]; //600 by 400

    }

    int** AllGy;

    AllGy = new int* [height];

    for (int k = 0; k < height; k++) {

        AllGy[k] = new int[width]; //600 by 400

    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) { //outside points

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

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            int magnitude = sqrt(AllGx[i][j] * AllGx[i][j] + AllGy[i][j] * AllGy[i][j]);

            if (magnitude > threshold) {

                temp[i][j] = max;

            }

            else {

                temp[i][j] = 0;

            }

        }

    }

    createppm(width, height, 1, "imagem", temp, true);

}

 

void recuring(int height, int width) { //height is x, width is y

    //if (temp[height][width] == 0 || temp[height][width] == 1 || temp[height][width] == 3) {

    //  

    //}

    if (temp[height][width] == 2) {

        temp[height][width] = 3;

        //cout << "can it get here";

        int neigha[8][2] = { {-1, 0},{-1, 1},{-1, -1},{0, 1},{0, -1},{1, 0},{1, 1},{1, -1} };

        for (int i = 0; i < 8; i++) { //do it 8 times

            int width1 = width + neigha[i][0];

            int height1 = height + neigha[i][1];

            if (temp[height1][width1] == 1) {

                temp[height1][width1] = 2;

            }

            else if (temp[height1][width1] == 2 || temp[height1][width1] == 3) {

                continue;

            }

            recuring(height1, width1);

        }

    }

}

void algo(int width, int height, int high, int low, string output, string both, string hys) {

    auto AllGx = vector<vector<int> >();

    for (int g = 0; g < height; g++) {

        AllGx.push_back(vector<int>(width, 0));

    }

    auto AllGy = vector<vector<int> >();

    for (int g = 0; g < height; g++) {

        AllGy.push_back(vector<int>(width, 0));

    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) { //outside points

                AllGx[i][j] = 0;

                AllGy[i][j] = 0;

            }

            else {

                //ejurj gx and gy are switched so I changed them here
                double Gx = (temp[i - 1][j - 1] * -1 + temp[i][j - 1] * -2 + temp[i + 1][j - 1] * -1 + temp[i - 1][j + 1] + temp[i][j + 1] * 2 + temp[i + 1][j + 1]);
                double Gy = (temp[i - 1][j - 1] * -1 + temp[i - 1][j] * -2 + temp[i - 1][j + 1] * -1 + temp[i + 1][j - 1] + temp[i + 1][j] * 2 + temp[i + 1][j + 1]);

                // int Gx = temp[i - 1][j - 1] * 1 +

                //     temp[i][j - 1] * 0 +

                //     temp[i + 1][j - 1] * -1 +

                //     temp[i - 1][j] * 2 +

                //     temp[i][j] * 0 +

                //     temp[i + 1][j] * -2 +

                //     temp[i - 1][j + 1] * 1 +

                //     temp[i][j + 1] * 0 +

                //     temp[i + 1][j + 1] * -1;

                // int Gy = temp[i - 1][j - 1] * -1

                //     + temp[i][j - 1] * -2

                //     + temp[i + 1][j - 1] * -1

                //     + temp[i - 1][j] * 0

                //     + temp[i][j] * 0

                //     + temp[i + 1][j] * 0

                //     + temp[i - 1][j + 1] * 1

                //     + temp[i][j + 1] * 2

                //     + temp[i + 1][j + 1] * 1;

                // int Gx = temp[i][j];

                // int Gy = temp[i][j];

                AllGx[i][j] = Gx;

                AllGy[i][j] = Gy;

            }

        }

    }

    //auto AllAngle = vector<vector<int>>();

    for (int g = 0; g < height; g++) {

        UnRAllAngle.push_back(vector<double>(width, 0));

    }

    auto AllMagn = vector<vector<int> >();

    for (int g = 0; g < height; g++) {

        AllMagn.push_back(vector<int>(width, 0));

    }

    auto AllAngle = vector<vector<int> >();

    for (int g = 0; g < height; g++) {

        AllAngle.push_back(vector<int>(width, 0));

    }

    double comparingAngle;

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if (i == 0 || j == 0 || i == height - 1 || j == width - 1) { //outside points

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

            //ejurj fixed the angle

            //comparingAngle = atan2(AllGx[i][j], AllGy[i][j]) * 180 / 3.1415; //216

            //comparingAngle = atan2(AllGy[i][j], AllGx[i][j]) * 180 / 3.1415; //216 //looks tangent

            comparingAngle = atan2(AllGy[i][j], AllGx[i][j]) * 180 / PI; //216

            UnRAllAngle[i][j] = atan2(AllGy[i][j], AllGx[i][j]);

            AllAngle[i][j] = floor((comparingAngle / 45)) * 45;

        }

    }

    // createppm(width, height, 2, "temp.ppm", temp);

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if (height == 0 || width == 0 || height == x10 - 1 || width == y10 - 1) { //outside points

                temp[height][width] = 0;

            }

            else {

                recuring(i, j);

            }

        }

        //cout << "did it get here tho??";

    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if (temp[i][j] == 1) {

                temp[i][j] = 0;

            }

            if (temp[i][j] == 3 || temp[i][j] == 2) {

                temp[i][j] = 1;

            }

        }

    }

    createppm(width, height, 1, hys, temp, true);

    cout << endl << "can you get here";

    //int** temp2;

    //temp2 = new int* [height];

    //for (int k = 0; k < height; k++) {

    //    temp2[k] = new int[width]; //600 by 400

    //}

    auto temp2 = vector<vector<int> >();

    for (int g = 0; g < height; g++) {

        temp2.push_back(vector<int>(width, 0));

    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            if (i == height - 1 || j == width - 1 || i == 0 || j == 0) {

                temp2[i][j] = 0;

                continue;

            }

            int temps;

            temps = AllAngle[i][j];

            int magnrn = AllMagn[i][j];

            if (temps == 0 || temps == 180 || temps == -180)

            {

                if ((magnrn >= AllMagn[i][j - 1]) && (magnrn >= AllMagn[i][j + 1])) {

                    magnrn = 1;

                }

                else {

                    magnrn = 0;

                }

            }

            //ejurj temps is absolute value of angle and you say 45 and -45 are the same? that is wrong

            //for 45 this seems correct but for -45 is not correct

            //you need to check for all angles if positive and negative are the same and also if the direction is correct

            else if (temps == 45 || temps == -135)

            {

                if ((magnrn >= AllMagn[i -1][j + 1]) && (magnrn >= AllMagn[i + 1][j - 1])) {

                    magnrn = 1;

                }

                else {

                    magnrn = 0;

                }

            }
            else if (temps == -45 || temps == 135)
            {

                if ((magnrn >= AllMagn[i -1][j - 1]) && (magnrn >= AllMagn[i +1][j +1])) {

                    magnrn = 1;

                }

                else {

                    magnrn = 0;

                }

            }

            else if (temps == 90|| temps ==-90)

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
    createppm(width, height, 1, output, temp2, true);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (temp2[i][j] == 1 && temp[i][j] == 1) {

                temp[i][j] = 1;
            }
            else {
                temp[i][j] = 0;
            }
        }
    }
    createppm(width, height, 1, both, temp, true);
}

void partthree(int high, int low, string filename, string output, string gre, string both, string hys) {

    ifstream File;

    int width, height, max;

    File.open(filename); //change this for all .ppm files

    char* temp3 = new char[2];

    File.read(temp3, 2); //p3

    //ejurj I think these 2 are mixed so I will replace them with height and width which is more approprite from the ppm

    File >> width; //800 by 200 or whatever

    File >> height;
   
    File >> max;

    cout << width << " " << height << endl; //800 600

    arr3 = new int* [height];

    for (int i = 0; i < height; i++) {

        arr3[i] = new int[width * 3];

    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width * 3; j++) {

            arr3[i][j] = 1;

        }

    }

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width * 3; j++) {
            File >> arr3[i][j];

        }
    }

    x10 = width; //800

    y10 = height; //600
    for (int g = 0; g < y10; g++) { //height
        bresy6.push_back(vector<int>(x10, 0)); //width
    }
    for (int g = 0; g < y10; g++) { //height
        for(int l =0; l< x10; l++){
            bresy6[g][l] = arr3[g][l];
        }    
    }

    bw_converter(width, height, max, gre);

    algo(width, height, high, low, output, both, hys); //change these to include all

}

void testheightor(int width, int height, int max, string output, vector<vector<int> > temp3, int r =0, int g = 0, int b=0) { //y10 is height x10 is width

    ofstream file;

    file.open(output); //change this when he gives the parameter

    file << "P3\n" << width << " " << height << "\n" << max << "\n";

    cout << endl << "ur in " << width << " " << height;

    for (int i = 0; i < height; i++)

    {

        for (int j = 0; j < width; j++) {

            if (temp3[i][j] == -11) {

                file << arr3[i][j * 3] << " ";

                file << arr3[i][j * 3 + 1] << " ";

                file << arr3[i][j * 3 + 2] << " ";

            }

            if (temp3[i][j] == -5) { //red

                file << max << " ";

                file << 0 << " ";

                file << 0 << " ";

            }
            if(temp3[i][j] == -4) { //green
                file << 0 << " ";
                file << max << " ";
                file << 0 << " ";
            }
            if(temp3[i][j] == -3) { //blue
                file << 0 << " ";
                file << 0 << " ";
                file << max << " ";
            }
            if(temp3[i][j] == -2) { //yellow
                file << max << " ";
                file << max << " ";
                file << 0 << " ";
            }
            if(temp3[i][j] == -1) { //purple
                file << max << " ";
                file << 0 << " ";
                file << max << " ";
            }

        }

        file << std::endl;

    } //this is 600 by 400

    file.close();

}

void illuminateRed(int bx, int by, int c, bool b = true) {

    if (0 < bx and bx < x10 and 0 < by and by < y10) {
        if (b){
            bresy[by][bx] = c;
        } else{
            bresy6[by][bx] = c;
        }
    }

}

int illuminateT(int bx, int by) {
    if (0 < bx and bx < x10 and 0 < by and by < y10) {
        return temp[by][bx];
    }
    return 0;
}

void circle(double r, Point p, int c = -5, bool b = true) {

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
        if(b) {
            illuminateRed(x + cx, y + cy, c);
            illuminateRed(x + cx, -y + cy, c);
            illuminateRed(-x + cx, y + cy, c);
            illuminateRed(-x + cx, -y + cy, c);
            illuminateRed(y + cx, x + cy, c);
            illuminateRed(y + cx, -x + cy, c);
            illuminateRed(-y + cx, x + cy, c);
            illuminateRed(-y + cx, -x + cy, c);
        } else {
            illuminateRed(x + cx, y + cy, c, false );
            illuminateRed(x + cx, -y + cy, c, false);
            illuminateRed(-x + cx, y + cy, c, false);
            illuminateRed(-x + cx, -y + cy, c, false);
            illuminateRed(y + cx, x + cy, c, false);
            illuminateRed(y + cx, -x + cy, c, false);
            illuminateRed(-y + cx, x + cy, c, false);
            illuminateRed(-y + cx, -x + cy, c, false);
        }

        y2_new -= (2 * x) + 3;

    }

}

//void
int Testcircle(double r, Point p) {

    //double cy1 = p.getY();

    //double cx1 = p.getX();
    int counter = 0;
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
        //this is an edge/noise
        counter += illuminateT(x + cx, y + cy);
        counter += illuminateT(x + cx, -y + cy);
        counter += illuminateT(-x + cx, y + cy);
        counter += illuminateT(-x + cx, -y + cy);
        counter += illuminateT(y + cx, x + cy);
        counter += illuminateT(y + cx, -x + cy);
        counter += illuminateT(-y + cx, x + cy);
        counter += illuminateT(-y + cx, -x + cy);

        y2_new -= (2 * x) + 3;

    }
    return counter;
}

void parttwo(int gap, string FCo, string FCi, double TCircle, int TC, int highthres, int lowerthres, string filename, string nms, string grey, string fin, string outfile, string www, string imageC, int kernel,int bb) { // only call after doing nms and cannyedge, use temp AFTER algo() called

    //add a bunch of bresenhams at the edges so for like every 5th 1, add line

    partthree(highthres, lowerthres, filename, nms, grey, fin, outfile); //imagef contains what we should use, imagef info is in int ** temp
    for (int g = 0; g < y10; g++) { //height
    
        bresy.push_back(vector<int>(x10, 0)); //width
        
    }


    //int lm = 0;
    //y10 is height
    //x10 is width
    for (int y = 0; y < y10; y++) { //height

        for (int x = 0; x < x10; x++) { //width

            if (temp[y][x] == 1) {

                //lm += 1;

                //if (lm <= 20) {

/*                   cout << "this is your angle" << UnRAllAngle[i][j];

                    cout << "this is your point" << i << " " << j;*/
                // int k= 0;
                // if(UnRAllAngle[i][j] != 0){
                //    cout << UnRAllAngle[i][j]*180/PI<< endl;
                //    if(k==0){
                //     cout<< i << " j" << j << endl;
                //     //k+=1;
                //    }
                // }
                

                int x8 = (int)(x + (x10* cos(UnRAllAngle[y][x])));

                int y8 = (int)(y + (x10* sin(UnRAllAngle[y][x])));

                int x80 = (int)(x - (x10 * cos(UnRAllAngle[y][x])));

                int y80 = (int)(y - (x10* sin(UnRAllAngle[y][x])));

                // double slope = tan(UnRAllAngle[i][j]);//y=mx+b and x = (y-b)/m
                
                // int b8 = j - (slope)*i;

                // int x8 = i + 200;

                // int y8 = x8*slope + b8;

                // int x80 = i -200;
                // int y80 = x80*slope +b8;
                //ejurj replaced next line

                //totalbresenham(Line(Point(y80, x80), Point(y8, x8)));

                totalbresenham(Line(Point(x80, y80), Point(x8, y8)));

                //}

            }

        }

    }

    //totalbresenham(Line(Point(200, 300), Point(400, 500)));

    //cout << " " << lm << endl;

    int max = 0;

    for (int y = 0; y < y10; y++) {

        for (int x= 0; x< x10; x++) {

            if (bresy[y][x] > max) {

                //cout << bresy[i][j] << " "; //how is max still 0 if im changin bresy via totalbresenham
                max = bresy[y][x];

            }

        }

    }

    cout << endl << "THis is the highest illum : " << max << endl;

    createppm(x10, y10, max, www, bresy, true); //votes
    for(int y = kernel; y< y10-kernel; y++) {//y10 height x10 width
        for(int x = kernel; x < x10 -kernel; x++){
            int maxL=0;
            for(int j = -(kernel-1); j <= (kernel-1); j++){
                for(int i = -(kernel-1); i <=(kernel-1); i++){
                    if(bresy[y+j][x+i] > maxL){
                        maxL = bresy[y+j][x+i];
                    }
                }
            }
            for(int j = -(kernel-1); j <= (kernel-1); j++){
                for(int i = -(kernel-1); i <=(kernel-1); i++){
                    if(bresy[y+j][x+i] < .8 *maxL){
                        bresy[y+j][x+i] =0;
                    }
                }
            }
        }
    }
    createppm(x10, y10, max, "testMax.ppm", bresy, true); //votes
    //what do i do after this? how do i get the red circles on top of the og pic

    //first get red circles and only the red waitttt 
    //createppm(x10, y10, 1, "testing.ppm", temp, true);
    vector<Point> cc;
    for (int i = 0; i < y10; i++) {

        for (int j = 0; j < x10; j++) {

            if (bresy[i][j] > TC) {

                circle(1, Point(j, i)); // fix this to show red and circles 
                circle(2, Point(j, i));
                circle(3, Point(j, i));
                cc.push_back(Point(j, i));
                circle(4, Point(j, i));
                 //bresy[i][j] = 0;

            }

            bresy[i][j] = -11;

        }

    }

    //circle(2, Point(600, 400));
    testheightor(x10, y10, 255, imageC, bresy); //imageCC.ppm
   // cout << "get here?";
    vector<vector<int> > radius; //2d array for every cc, has a vector size 25, radius index at r
    for(int x = 0; x <=cc.size(); x++){
        radius.push_back(vector<int>(25));
    }
    
//for every cc
    int counter;
    for(int x =0; x <=cc.size(); x++){
        for(int r = 0; r <= radius[0].size(); r++){
            counter = Testcircle(r+bb, cc[x]);
            radius[x][r] = counter;
           // if(counter != 0){cout << counter <<endl;}
        }
        //cout << "next" << endl;
    }
    
    // for(int x = 0; x < radius[0].size(); x++){
    //     cout<< radius[0][x] << endl;
    // }
    vector<int> maxRadius;
    for(int x = 0; x <= cc.size(); x++){
        maxRadius.push_back(0);
    }
    vector<Point> cc_updated;
    vector<double> r_updated;
    for(int x = 0; x <= cc.size(); x++){
       // int maxR = 0;
        for(int r =0; r <= radius[0].size(); r++){
            if(radius[x][r] != 0){
                if(radius[x][r] > TCircle * r){
                   // maxR = radius[x][r];
                    cc_updated.push_back(cc[x]);
                    r_updated.push_back(r+bb);
                    //cout << "this is r " << r << endl;
                }
            }   
        }
       // cout << "realR: " << realR << endl;
        // maxRadius[x] = realR;
        //if(realR > 9){
            //circle(realR, cc[x]);
       // }
    }
    cout<< "before: " << cc.size() << endl;
    cout << "first thing: "<< cc_updated.size() << endl;
    //coins w multiple centers: check which center radius thing has more counter thing
    vector<Point> ClearedCC;
    vector<double> ClearedR;
    //for(int i = 0; i < cc_updated.size(); i++){
    while(cc_updated.size() > 0){
        // cout << cc_updated[i].getX() << ", " << cc_updated[i].getY() << " rupdated: " << r_updated[i] << endl;
        Point tempcc = cc_updated[(int)cc_updated.size()-1];
        double tempr = r_updated[(int)r_updated.size()-1];
        // if(cc_updated[i].getY() - cc_updated[i+1].getY() <=4){
        //     if(cc_updated[i].getX() - cc_updated[i+1].getX() <=4) {
        //         if (r_updated[i] > r_updated[i+1]){
        //              //how to remove vector value  
        if((int)ClearedCC.size() == 0){
            ClearedCC.push_back(tempcc);
            ClearedR.push_back(tempr);
        }
        else {
            bool isGood = true;
            for(int i = 0; i< ClearedCC.size(); i++){
                // cout << i << endl;
                if(pow(ClearedCC[i].getX() - tempcc.getX(), 2) + pow(ClearedCC[i].getY() - tempcc.getY(),2) < gap ){
                    isGood = false;
                }
            }
            if(isGood) {
                ClearedCC.push_back(tempcc);
                ClearedR.push_back(tempr);
            }
        }
        cc_updated.pop_back();
        r_updated.pop_back();
       // cout<< cc_updated.size() << endl;
    }
    for(int i = 0; i < ClearedCC.size(); i++){  //circum w red circles
        circle(ClearedR[i], ClearedCC[i], -5, false); //false just means use the copy of bresy not the old bresy
        circle(1, ClearedCC[i]); // fix this to show red and circles 
        //circle(2, ClearedCC[i]);
        circle(3, ClearedCC[i]);
    }
    testheightor(x10, y10, 255, FCi, bresy6);
    
    // //c represents color so -5 is red, -4 is green, -3 blue, -2 yellow, -1 purple
    // for(int i = 0; i < ClearedCC.size(); i++){ //this code is not done at all
    //     //cout << ClearedCC[i].getX() << ", " << ClearedCC[i].getY() << " rupdated: " << ClearedR[i] << endl;
    //     int radius = (int)ClearedR[i];
    //     if(1< radius < 10) { //penny and dime check
    //         if(bresy[ClearedCC[i].getY()][ClearedCC[i].getX()] > 150){
    //             circle(ClearedR[i], ClearedCC[i], -5);
    //         } else {
    //             circle(ClearedR[i],ClearedCC[i], -3);
    //         }
    //     }
    //     else if(10< radius< 16) {
    //         circle(ClearedR[i], ClearedCC[i], -2);
    //     }
    //     else {
    //         circle(ClearedR[i], ClearedCC[i], -1);
    //     }
    // }
    // int index = 0;
    // int highest = 0;
    // for (unsigned int a = 0; a < ClearedCC.size(); a++)
    // {
    //     int count = 1;
    //     int Position = ClearedCC[a];
    //    //int radius = cvRound(circles[a][2]);
    //     for (unsigned int b = a + 1; b < ClearedCC.size(); b++)
    //     {
    //         if (ClearedCC[b][2] == Position)
    //         {
    //             count++;
    //         }
    //     }
    //     if (count >= index)
    //     {
    //         index = count;
    //         highest = Position;
    //     }
    //    // cout << circles[a][2] << endl;
    // }
    // int fpenny = 0;
    // int fnickel = 0;
    // int fdime = 0;
    // int fquarter = 0;
    // int fhalf = 0;
    // int fsilver = 0;
    // int feisan =0;
    // vector<double> type;
    // type.push_back(1.0470); 
    // type.push_back(1.16);
    // type.push_back(3.00);
    // for (size_t i = 0; i < ClearedCC.size(); i++)
    // {
    //     Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    //     double radius = circles[i][2];
    //     // Determine the denomination based on the radius
    //     Scalar color;
    //    // color = Scalar(0,0,255);
    //     //cout << (double)93.3/91 << endl;
    //     if(radius/highest < type[0]){ //penny or dime...for dime use color
    //         //Vec3b colors = image.at<Vec3b>(center);
    //         //cout << (int)colors[2] << " "<< (int)colors[1] << " " << (int)colors[0] << endl
    //         if((colors[2]> colors[1]) && (colors[2] > colors[0])) {
    //                 circle(ClearedR[i], ClearedCC[i], -5); //red circle //scalar is bgr
    //                 fpenny++;
    //             } else {
    //                 color = Scalar(255, 0, 0);
    //                 fdime++;
    //             }  
    //         } else {
    //             color = Scalar(0,0,255);
    //             fpenny++;
    //         }
    //         //cout << radius << endl;
    //     else if((radius/highest > type[0])&& (radius/highest < type[1])) {
    //         color = Scalar(0, 255, 255); //nickels
    //         if(radius < 114.21 && radius > 110){
    //             color = Scalar(255, 192, 203); // pink
    //             feisan++;
    //         }
    //         cout << radius << endl;
    //         fnickel++;
    //     } else if(radius/highest > type[1] && (radius/highest <type[2])) {
    //         color = Scalar(128, 0, 128); //quarter
    //         fquarter++;
    //         //cout << radius << endl;
    //     } else if (radius/highest > type[2]) {
    //         color = Scalar(0, 255, 0); // green
    //         fhalf++;
    //     } 
    //     circle(image, center, cvRound(radius), color, 5);
    // }
    // // Mat edges;
    // // Canny(image, edges, 120, 200);
    // ofstream file("results.txt");
    // file << "number of pennies: " << fpenny << endl;
    // file << "number of nickels: " << fnickel << endl;
    // file << "number of dimes: " << fdime << endl;
    // file << "number of quarters: " << fquarter << endl;
    // file << "number of half-dollars: " << fhalf << endl;
    // file << "number of silver dollars: " << fsilver << endl;
    // cout << "number of pennies: " << fpenny << endl;
    // cout << "number of nickels: " << fnickel << endl;
    // cout << "number of dimes: " << fdime << endl;
    // cout << "number of quarters: " << fquarter << endl;
    // cout << "number of half-dollars: " << fhalf << endl;
    // cout << "number of silver dollars: " << fsilver << endl;
    // if(types==3) {
    //     file << "number of eisan dollars: " << feisan << endl;
    //     cout << "number of eisan dollars: " << feisan << endl;
    // }
    // double total = fpenny * 0.01 + fnickel * 0.05 + fdime * .1 + fquarter *.25 + fhalf *.5;
    // file << "the total: $" << total << endl;
    // cout << "the total: $" << total << endl;
    // file.close();
    //ghost coins??? --> kernel
    testheightor(x10, y10, 255, FCo, bresy);
    cout<< "after: " << ClearedCC.size() << endl;
    cout << "done" ;
    //b) and a bold outline of the coins you found by using the
    // following colors: red for penny, yellow for nickel, blue for dime, purple for quarters, green for half dollar and pink for silver dollar.. So draw a circle around each coin detected using the correct color.
//check +70 radius, add to vector radius
   
}

int main(int argc, char** argv)

{
    //high, low, input, output
    //./l062 -f myimg.ppm [done] -lt 150 [done ] -ht 200 [done] -ff myimagef.ppm [done] -TC 300 [done] -fv myimagev.ppm [done] 
    //-fcc myimageCC.ppm [done] -TCircle 55 [done] -fCi myimageCircles.ppm -fCo myimageCoins.ppm -fR myresults.txt

    //the line above will use 110 and 200 for low and high threshold for te canny edge;  [done]
    //the 300 will be the threshold value used for deciding if a pixel is a candidate for 
    //a center or not (so if a pixel received >=300 votes it means is a high chance that the pixel is a center), 
    //and the thhreshold value of 55 which is 55% is used to identify if a candidate for a center and a certain radius 
    //is a circle or not. Rest of parameters allow the customization of the output files' names and they are self explanatory. 
    //(in case you use other variable values feel free to add them at the end in a similar fashion and specify them in the 
    //document so I know how to use them) Any or all the command line parameters may be missing.
    //cout <<"testinggg" << endl;
    int lowerthres, highthres, TC;
    int minRadius, maxRadius;
    string outfile, filename, grey, nms, fin, www, imageC; //part one
    int gap;
    int TCircle;
    string FCi, FCo, FR;
    int kernel,bb;
    
    FCi = "myimageCircles.ppm"; //red circles
    FCo = "myimageCoins.ppm";

    TCircle = 55;

    TC = 99;
    gap = 12;
    TCircle = 55;

    lowerthres = 100;

    highthres = 150;

    outfile = "image1.ppm";

    nms = "image2.ppm";

    grey = "imageg.ppm";

    filename = "hard.ppm";

    fin = "imagef.ppm";

    www = "imagev.ppm";

    imageC = "imageCC.ppm";

    kernel = 45;

    bb = 50;

    // -f1 myimage1.ppm -f2 myimage2.ppm -ff myimagef.ppm -TC 300 -fv myimagev.ppm -fcc myimageCC.ppm

    for (int i = 0; i < argc; ++i) {

        //cout << argv[i] << "\n";
        if (strcmp(argv[i], "-TCircle") == 0) {

            TCircle = stoi(argv[i + 1]);

            cout << TCircle;

        }
        if (strcmp(argv[i], "-gap") == 0) {

            gap = stoi(argv[i + 1]);

            cout << gap;

        }
        if (strcmp(argv[i], "-fCi") == 0) {

            FCi = argv[i + 1];

            cout << FCi;

        }
        if (strcmp(argv[i], "-fCo") == 0) {

            FCo = argv[i + 1];

            cout << FCo;

        }

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
        if (strcmp(argv[i], "-ker") == 0) {

            kernel = stoi(argv[i + 1]);

            cout << kernel;

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
    parttwo(gap, FCo, FCi, TCircle/100, TC, highthres, lowerthres, filename, nms, grey, fin, outfile, www, imageC, kernel,bb);
}