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
using namespace std;
const int l = 400;
const int f = 400;
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
    static list<Point> getSorted(list<Point> listOfPoints) {
        listOfPoints.sort(sortFunct); // invoke system sort with sortFunct comparator
        return listOfPoints;
    }
    ~Point() {

    }  // destructor; called when the delete is called
private:
    double x;
    double y;
    static bool sortFunct(Point i, Point j) { return (j.x > i.x); }; // compare by x-value
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
    file.open("quickhull.ppm");
    file << "P3\n" << l << " " << f << "\n1\n";
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < f; j++)
        {
            file << arr[j][i] << " ";
            file << arr[j][i] << " ";
            file << arr[j][i] << " ";
        }
        file << std::endl;
    }
    file.close();
}
//picks the right bresenham
void totalbresenham(Point a, Point b) {
    double x1, y1, x2, y2;
    x1 = a.getX() * l;
    y1 = a.getY() * f;
    x2 = b.getX()* l;
    y2 = b.getY()* f;

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
    double m; //slope
    double b;

};
double calcTri(double x, double y, double x1, double y1, double x2, double y2) {
    double a = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
    double b = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    double c = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
    double s = (a + b + c) * 0.5;
    double area = sqrt((s - a) * (s - b) * (s - c) * s);
    return area;
}
list<Point> getpartonepoints() {
    list<Point> listy;
    ofstream file;
    file.open("points.txt");
    createarr(l, f);
    srand(time(NULL));
    for (int i = 0; i < 60; i++) {
        Point z = Point((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX)); //creates a point with x and y values between 0 and 1
        file << setprecision(23) << z.getX() << "  " << z.getY() << endl;
        listy.push_back(z);
        // illuminate(z.getX() * l, z.getY() * f);
        // circle(3, z);
         //circle(2, z);
    }
    return listy;
}
double dist(Point a, Point b) {
    return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY()));
}
void FindHull(vector<Point> Sk, Point a, Point b, vector<Point>& convexHull) {
    if (Sk.size() == 0) {
        return;
    }
    double max_dist = 0;
    Point C;
    double error = 0.000001;
    vector<Point> s1, s2, s0;
    double slopeLine = (b.getY() - a.getY()) / (b.getX() - a.getX());
    double yintercept = b.getY() - slopeLine * (b.getX());
    Line temp = Line(a, b, slopeLine, yintercept);
    double perpSlope = -1 / slopeLine;
    double tempYint, intersectionX, intersectionY;
    for (int i = 0; i < Sk.size(); i++)
    {
        if ((Sk[i].getX() != a.getX() || Sk[i].getY() != a.getY()) &&
            (Sk[i].getX() != b.getX() || Sk[i].getY() != b.getY())) // not a or b
        {
            tempYint = Sk[i].getY() - Sk[i].getX() * perpSlope; //b = y -mx
            intersectionX = (yintercept - tempYint) / (perpSlope - slopeLine);
            intersectionY = slopeLine * intersectionX + yintercept;
            if (dist(Sk[i], Point(intersectionX, intersectionY)) > max_dist) {
                max_dist = dist(Sk[i], Point(intersectionX, intersectionY));
                C = Point(Sk[i].getX(), Sk[i].getY());
            }
        }
    }
    for (int i = 0; i < convexHull.size(); i++) //adds C between a and b
    {
        if ((convexHull[i].getX() == a.getX() && convexHull[i].getY() == a.getY()))
        {
            convexHull.insert(convexHull.begin() + i + 1, C);
            i = convexHull.size() + 1;
          //  cout << "this is the new one " <<C.getX() << " " << C.getY() << endl;
        }
    }
    for (int i = 0; i < Sk.size(); i++) //sorts the remaining points into subsets
    {
        if ((Sk[i].getX() == C.getX() && Sk[i].getY() == C.getY())) {
            continue;
        }
        if (abs((calcTri(Sk[i].getX(), Sk[i].getY(), a.getX(), a.getY(), b.getX(), b.getY()) +
            calcTri(Sk[i].getX(), Sk[i].getY(), C.getX(), C.getY(), b.getX(), b.getY()) +
            calcTri(Sk[i].getX(), Sk[i].getY(), C.getX(), C.getY(), a.getX(), a.getY())) -
            calcTri(a.getX(), a.getY(), b.getX(), b.getY(), C.getX(), C.getY())) < error) {
          //  cout << "point inside tri " << Sk[i].getX() << endl;
            s0.push_back(Sk[i]);
        }
        else {
           // tempYac = Sk[i].getX() * ac_slope + ac_int;
            //tempYcb = Sk[i].getX() * bc_slope + bc_int;
            ////(x2-x1)(y3-y1) - (y2-y1)(x3-x1)
            double which_side, which_side1;
            which_side = (b.getX() - C.getX()) * (Sk[i].getY() - C.getY()) - (b.getY() - C.getY()) * (Sk[i].getX() - C.getX());
            which_side1 = (C.getX() - a.getX()) * (Sk[i].getY() - a.getY()) - (C.getY() - a.getY()) * (Sk[i].getX() - a.getX());

            if (which_side < 0) {
                s2.push_back(Sk[i]);
               // cout << "does this do anything1" << endl;
            }
            else if(which_side1 < 0) {
                s1.push_back(Sk[i]);
               // cout << "does this do anything2" << endl;
            }
        }
    }
    FindHull(s1, a, C, convexHull);
    FindHull(s2, C, b, convexHull);
}
//vector<Point> FindHull(vector<Point>& sixty, Point a, Point b) { }
void QuickHull(vector<Point>& sixty) {
    vector<Point> convexHull = {};
    //Find the points with minimum and maximum x coordinates
//If many points with the same minimum/maximum x exist, use ones with minimum/maximum y correspondingly.
// cout << minX.getX() << " " << minX.getY() << " " <<maxX.getX() << " " << maxX.getY();
    Point minX = sixty[0];
    Point maxX = sixty[sixty.size() - 1];
    int count = 1;
    while(count>0){
        if (sixty[count].getX() == minX.getX()) {
            if (sixty[count].getY() < minX.getY()) {
                minX = sixty[count];
                count++;
            }
        }
        else {
            count = 0;
        }
    }
    int countback = sixty.size() -2;
    while (countback > 0) {
        if (sixty[countback].getX() == maxX.getX()) {
            if (sixty[countback].getY() > minX.getY()) {
                maxX = sixty[countback];
                countback--;
            }
        }
        else {
            countback = 0;
        }
    }
    convexHull.push_back(minX);
    convexHull.push_back(maxX);
  //  totalbresenham(minX, maxX);
    vector<Point> s1, s2;
    //s1 holds points below the line, s2 holds points above line min to max
    double yLine, yLine1; //with a given x, the line's y
    for (int i = 1; i < sixty.size() - 1; i++) { //(x2-x1)(y3-y1) - (y2-y1)(x3-x1)
        yLine = (minX.getX() - maxX.getX()) * (sixty[i].getY() - maxX.getY()) - (minX.getY() - maxX.getY()) * (sixty[i].getX() - maxX.getX()); //b to a
        yLine1 = (maxX.getX() - minX.getX()) * (sixty[i].getY() - minX.getY()) - (maxX.getY() - minX.getY()) * (sixty[i].getX() - minX.getX());
        if (yLine <0) {
            s2.push_back(sixty[i]);
        }
        else if(yLine1 <0) {
            s1.push_back(sixty[i]);
        }
    }
    vector<Point>& temp = convexHull;
    FindHull(s1, minX, maxX, temp);
    FindHull(s2, maxX, minX, temp);
    convexHull.push_back(minX);
    for (Point s : sixty) {
        illuminate(s.getX(), s.getY());
        circle(3, s);
        circle(2, s);
    }
    totalbresenham(convexHull[convexHull.size() - 1], convexHull[0]);
    for (int i = 0; i < convexHull.size()-1; i++) {
        totalbresenham(convexHull[i], convexHull[i + 1]);
    }
    //return convexHull;
}
void partone() {
    list<Point> listy = Point::getSorted(getpartonepoints());
    vector<Point> sixty{ std::begin(listy), std::end(listy) };
    vector<Point>& six = sixty;
    QuickHull(six);
    createppm();
    
}
int main()
{
    partone();
}