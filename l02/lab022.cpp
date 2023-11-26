// lab022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>      // std::setprecision
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
const int l = 800;
const int f = 800;
int arr[l][f];
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
        cout << "point delete";
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
    Line(const Line& pt) { p1 = pt.p1; p2 = pt.p2; m = pt.m; b = pt.b; und = false; }
    ~Line() {
        cout << "point delete";
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
//saves square info
class Box {
public:
    Box() {
        area = 99.0;
        v1 = Point(99.0, 99.0);
        v2 = Point(99.0, 99.0);
        v3 = Point(99.0, 99.0);
        v4 = Point(99.0, 99.0);
        a = Line(v1, v2, 99.0, 99.0);
        b = Line(v2, v3, 99.0, 99.0);
        c = Line(v3, v4, 99.0, 99.0);
        d = Line(v4, v1, 99.0, 99.0);
    }
    Box(double area1, Line a1, Line b1, Line c1, Line d1, Point v11, Point v12, Point v13, Point v14) {
        area = area1;
        v1 = v11;
        v2 = v12;
        v3 = v13;
        v4 = v14;
        a = a1;
        b = b1;
        c = c1;
        d = d1;
    }
    Box(const Box& bo) { area = bo.area; a = bo.a; b = bo.b; c = bo.c; d = bo.d; v1 = bo.v1; v2 = bo.v2; v3 = bo.v3; v4 = bo.v4; }
    ~Box() {
        cout << "box delete";
    }  // destructor; called when the delete is called
    double getArea() { return area; }
    Point getV1() { return v1; }
    Point getV2() { return v2; }
    Point getV3() { return v3; }
    Point getV4() { return v4; }
    Line geta() { return a; }
    Line getb() { return b; }
    Line getc() { return c; }
    Line getd() { return d; }
private:
    double area;
    Point v1, v2, v3, v4;
    Line a, b, c, d;
};
void createarr(int s1, int s2) {
    for (int i = 0; i < s1; i++) {
        for (int j = 0; j < s2; j++) {
            arr[i][j] = 1;
        }
    }
}
void printArray() {
    for (int x = 0; x < l; x++) {
        for (int y = 0; y < f; y++) {
            cout << arr[x][y] << " ";
        }
        cout << "\n";
    }
}
//shades in everything
void illuminate(int bx, int by)
{
    // cout << bx << by << "\n";
    if (0 < bx and bx < l and 0 < by and by < f) {
        arr[bx][by] = 0;
    }

}
//all the bresenhams
void bresenhamxpos(double x1, double y1, double x2, double y2) {
    cout << "xpos";
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
    cout << "xneg";
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
    cout << "ypos";
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
    cout << "yneg";
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
//makes a ppm file
void createppm() {
    ofstream file;
    file.open("l022.ppm");
    file << "P3\n" << l << " " << f << "\n1\n";
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < f; j++)
        {
            file << arr[i][j] << " ";
            file << arr[i][j] << " ";
            file << arr[i][j] << " ";
        }
        file << std::endl;
    }
    file.close();
}
//picks the right bresenham
void totalbresenham(Line x) {
    double x3, y3, x4, y4;
    x3 = 0;
    x4 = 799;
    y3 = x.getb();
    cout << "totalbres d inter" << x.getb();
    y4 = x.getb() + x.getm() * x4;
    double x1 = x3 * l;
    double y1 = y3 * f;
    double x2 = x4 * l;
    double y2 = y4 * f;
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

//calculates the areas of the triangles
double area(double x, double y, double x1, double y1, double x2, double y2) {
    double a = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
    double b = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    double c = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
    double s = (a + b + c) * 0.5;
    double area = sqrt((s - a) * (s - b) * (s - c) * s);
    return area;
}
//finds four random pts that meet requirements, stores in pt.txt, puts testing pts in log.txt
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
    file2.open("point.txt");
    //note: 10/06/2022 10 am updated, i realise my formatting for points.txt is slightly off,
    //but i don't want to change it as then i have to change everything in my main that dealt with this formatting
    // which literally took me three hours to figure out as this is my first time using c++ and
    //im running out of time and have many things to do as college apps are due in three weeks 
    //i hope you understand thanks
    file2 << std::setprecision(19) << "(" << x << "," << y << ") , (" << x1 << "," << y1 << ") , (" << x2 << "," << y2 << ") , (" << x3 << "," << y3 << ")";
    std::cout << std::setprecision(19) << "(" << x << "," << y << ") , (" << x1 << "," << y1 << ") , (" << x2 << "," << y2 << ") , (" << x3 << "," << y3 << ")";
    file2.close();
    file.close();
    //return arr;
}
//renders a circle
void circle(double r, Point p) {
    double cy1 = p.getY();
    double cx1 = p.getX();
    double cy = cy1 * f;
    double cx = cx1 * l;
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
        illuminate(x + cx, y + cy);
        illuminate(x + cx, -y + cy);
        illuminate(-x + cx, y + cy);
        illuminate(-x + cx, -y + cy);
        illuminate(y + cx, x + cy);
        illuminate(y + cx, -x + cy);
        illuminate(-y + cx, x + cy);
        illuminate(-y + cx, -x + cy);
        y2_new -= (2 * x) + 3;
    }
}
//makesquare does all the math to find one square, called six times
Box makesquare(Point pta, Point ptc, Point ptb, Point ptd, bool E) {
    //draw line from pt a to pt c (three)
    double ac_slope = (pta.getY() - ptc.getY()) / (pta.getX() - ptc.getX());
    double ac_intercept = pta.getY() - ac_slope * pta.getX(); //y = mx+ b
    //double ey = ac_intercept + ac_slope * 0;
    //double ey1 = ac_intercept + ac_slope * 799;
    // cout << ac_slope << " " << ac_intercept << "this is ey" << ey << "this is ey1" << ey1;
    Line ac = Line(pta, ptc, ac_slope, ac_intercept);
    //removed all rendering from makesq
    //totalbresenham(0, ey, 799, ey1); //line??? this could be ac, ab, or ad
    //draw line from pt b to line ac
    double b_slope = -1 / ac_slope;
    double e_other1 = ptb.getY() - b_slope * ptb.getX();
    // double ey2 = b_slope * 0 + e_other1;
    // double ey3 = b_slope * 799 + e_other1;
    Line bfake = Line(ptb, b_slope, e_other1);
    //totalbresenham(0, ey2, 799, ey3);
    double ac_dx = pta.getX() - ptc.getX();
    double ac_dy = pta.getY() - ptc.getY();
    //make pt e on line with b that intersects ac so that be = ac (2 options)
    double x5, y5;
    if (E) {
        x5 = ptb.getX() + ac_dy;
        y5 = ptb.getY() - ac_dx;
    }
    else {
        x5 = ptb.getX() - ac_dy;
        y5 = ac_dx + ptb.getY();
    }
    Point pte = Point(x5, y5); //creates pt e for either if statement aprts
    //circle(5, x5, y5); // totalbresenham(x5, y5, ptb.getX(), ptb.getY());
    //draw line from d to e
    double de_slope = (ptd.getY() - y5) / (ptd.getX() - x5);
    double de_line = ptd.getY() - de_slope * ptd.getX();
    //  double dey2 = de_slope * 0 + de_line;
    //  double dey3 = de_slope * 799 + de_line;
      // totalbresenham(x5, y5, ptd.getX(), ptd.getY());
    Line d = Line(ptd, pte, de_slope, de_line);
    cout << "this is lines d intercept" << d.getb();
    //totalbresenham(d);
     // totalbresenham(0, dey2, 799, dey3);
      // totalbresenham(x5, y5, ptb.getX(), ptb.getY());
       //take pt a and pt c and draw perp line from a to line de and c to line de
    double opp = -1 / de_slope;
    double a_line = pta.getY() - opp * pta.getX();
    double c_line = ptc.getY() - opp * ptc.getX();
    //double ay2 = opp * 0 + a_line;
    //double ay3 = opp * 799 + a_line;
    //double cy2 = opp * 0 + c_line;
    //double cy3 = opp * 799 + c_line;
    Line a = Line(pta, opp, a_line);
    Line c = Line(ptc, opp, c_line);
    // totalbresenham(0, ay2, 799, ay3);
    // totalbresenham(0, cy2, 799, cy3);
     //take pt b and make a perp line from b to line a or line c
    double b_line = ptb.getY() - de_slope * ptb.getX();
    //double bey2 = de_slope * 0 + b_line;
    //double bey3 = de_slope * 799 + b_line;
    // totalbresenham(x5, y5, ptd.getX(), ptd.getY());
    Line b = Line(ptb, de_slope, b_line);
    //totalbresenham(0, bey2, 799, bey3);
    //findintercept(a, b);
    //double x = (e_other1 - a_line) / (b_slope - opp);
    //double y = opp * x + a_line;
    //cout << x << "this is y " << y;
    //circle(5, x, y);
    //cout << "SIMRITH THIS IS YOUR A SLOPE " << a.getm() << " , " << a.getb();
    //cout << "SIMRITH THIS IS YOUR B SLOPE " << b.getm() << " , " << b.getb();
    //cout << "SIMRITH THIS IS YOUR C SLOPE " << c.getm() << " , " << c.getb();
    //cout << "SIMRITH THIS IS YOUR D SLOPE " << d.getm() << " , " << d.getb();
    //findintercept(a, d);
    double x = (d.getb() - a.getb()) / ((1 / a.getm()) + a.getm());
    double y = a.getm() * x + a.getb();
    // Point a = Point(x, y);
    //circle(5, x, y);
    //findintercept(c, b);
    double cx = (b.getb() - c.getb()) / ((1 / c.getm()) + c.getm());
    double cy = c.getm() * cx + c.getb();
    // Point b = Point(cx, cy);
  //  circle(5, cx, cy);
    //findintercept(c, d);
    double dx = (d.getb() - c.getb()) / ((1 / c.getm()) + c.getm());
    double dy = c.getm() * dx + c.getb();
    //  circle(5, dx, dy);
      // Point c = Point(dx, dy);
       //findintercept(a, b);
    double bx = (b.getb() - a.getb()) / ((1 / a.getm()) + a.getm());
    double by = a.getm() * bx + a.getb();
    //   circle(5, bx, by);
    cout << x << " " << y;
    //  Point d = Point(bx, by);
    double area = (x - bx) * (x - bx) + (y - by) * (y - by);
    Point p = Point(x, y);
    cout << "this is my area" << area;
    return Box(area, a, b, c, d, p, Point(cx, cy), Point(dx, dy), Point(bx, by));
}
void parttwo() {
    ifstream file1("point.txt"); //opens pt.txt
    string temp, delimeter;
    //double array1[8]; //(0.4406262398144474846,0.8002563554795983913) , (0.2676778466139713708,0.8880275887325662643) , (0.4741050447096163967,0.3292641987365337308), (0.7663808099612414715,0.2310251167332987576)
    if (file1.is_open()) {
        getline(file1, temp);
    }
    cout << temp << endl;
    vector<string> arr; //stores each coord
    vector<double> arr2; //splits coord to x and y and stores
    delimeter = " , ";
    string t;
    temp.erase(remove(temp.begin(), temp.end(), '('), temp.end());
    temp.erase(remove(temp.begin(), temp.end(), ')'), temp.end());
    //seperates by " , " and prints it so I can check
  //  cout << temp << endl;
    int start, end = -1 * delimeter.size();
    do {
        start = end + delimeter.size();
        end = temp.find(delimeter, start);
        cout << temp.substr(start, end - start) << endl;
        arr.push_back(temp.substr(start, end - start));
    } while (end != -1);
    //seperates string by just commas and adds each to an array so i can use them to create points
    string delimeter2 = ",";
    int size = arr.size();
    for (int i = 0; i < size; i++) {
        int start1, end1 = -1 * delimeter2.size();
        start1 = end1 + delimeter2.size();
        end1 = arr[i].find(delimeter2, start1);
        cout << endl << arr[i].substr(start1, end1 - start1) << endl << arr[i].substr(end1 - start1 + delimeter2.size(), end1);
        arr2.push_back(stof(arr[i].substr(start1, end1 - start1)));
        arr2.push_back(stof(arr[i].substr(end1 - start1 + delimeter2.size(), end1)));
    }
    file1.close();
    createarr(l, f);
    Point pta = Point(arr2[0], arr2[1]);
    Point ptc = Point(arr2[2], arr2[3]);
    Point ptb = Point(arr2[4], arr2[5]);
    Point ptd = Point(arr2[6], arr2[7]);
    //creates the OG 4 points
    circle(3, pta);
    circle(3, ptc);
    circle(3, ptd);
    circle(3, ptb);
    //creates all six boxes
    Box s0 = makesquare(pta, ptb, ptc, ptd, true);
    Box s1 = makesquare(pta, ptb, ptc, ptd, false);
    Box s2 = makesquare(pta, ptc, ptb, ptd, true);
    Box s3 = makesquare(pta, ptc, ptb, ptd, false);
    Box s4 = makesquare(pta, ptd, ptb, ptc, true);
    Box s5 = makesquare(pta, ptd, ptb, ptc, false);
    // if (s.getArea() < s1.getArea())
    Box ar[6] = { s1,s0,s2,s3,s4,s5 };
    Box s = s1;
    //finds the box with the smallest area!!!!!!!!!!!
    for (int x = 0; x < 6; x++) {
        if (ar[x].getArea() < s.getArea()) {
            s = ar[x];
        }
    }
    // cout << "this is ur simrith simrith v1 x" << s.getV1().getX();
    totalbresenham(s.geta());
    totalbresenham(s.getb());
    totalbresenham(s.getc());
    totalbresenham(s.getd());
    circle(3, s.getV1());
    circle(3, s.getV2());
    circle(3, s.getV3());
    circle(3, s.getV4());
    /*cout << s.getArea() << "this is line a" << s.geta().getb();*/
   // totalbresenham(0, a.geta().getb(), 799, a.geta().getb() + a.geta().getm() * 799);
    // makesquare(pta, ptb, ptc, ptd);
    ofstream file3;
    file3.open("output.txt");
    //put points in 
    file3 << "(" << pta.getX() << "," << pta.getY() << ") , (" << ptb.getX() << "," << ptb.getY() << ") , (" << ptc.getX() << "," << ptc.getY() << ") , (" << ptd.getX() << "," << ptd.getY() << ")" << endl;
    file3 << "(" << s0.getV1().getX() << "," << s0.getV1().getY() << ") , (" << s0.getV2().getX() << "," << s0.getV2().getY() << ") , (" << s0.getV3().getX() << "," << s0.getV3().getY() << ") , (" << s0.getV4().getX() << "," << s0.getV4().getY() << ")" << " Area = " << s0.getArea() << endl;
    file3 << "(" << s1.getV1().getX() << "," << s1.getV1().getY() << ") , (" << s1.getV2().getX() << "," << s1.getV2().getY() << ") , (" << s1.getV3().getX() << "," << s1.getV3().getY() << ") , (" << s1.getV4().getX() << "," << s1.getV4().getY() << ")" << " Area = " << s1.getArea() << endl;
    file3 << "(" << s2.getV1().getX() << "," << s2.getV1().getY() << ") , (" << s2.getV2().getX() << "," << s2.getV2().getY() << ") , (" << s2.getV3().getX() << "," << s2.getV3().getY() << ") , (" << s2.getV4().getX() << "," << s2.getV4().getY() << ")" << " Area = " << s2.getArea() << endl;
    file3 << "(" << s3.getV1().getX() << "," << s3.getV1().getY() << ") , (" << s3.getV2().getX() << "," << s3.getV2().getY() << ") , (" << s3.getV3().getX() << "," << s3.getV3().getY() << ") , (" << s3.getV4().getX() << "," << s3.getV4().getY() << ")" << " Area = " << s3.getArea() << endl;
    file3 << "(" << s4.getV1().getX() << "," << s4.getV1().getY() << ") , (" << s4.getV2().getX() << "," << s4.getV2().getY() << ") , (" << s4.getV3().getX() << "," << s4.getV3().getY() << ") , (" << s4.getV4().getX() << "," << s4.getV4().getY() << ")" << " Area = " << s4.getArea() << endl;
    file3 << "(" << s5.getV1().getX() << "," << s5.getV1().getY() << ") , (" << s5.getV2().getX() << "," << s5.getV2().getY() << ") , (" << s5.getV3().getX() << "," << s5.getV3().getY() << ") , (" << s5.getV4().getX() << "," << s5.getV4().getY() << ")" << " Area = " << s5.getArea() << endl;
    file3.close();
    createppm();
}
int main()
{
   // partone();
    parttwo();
    //std::cout << "Hello World!\n";
}