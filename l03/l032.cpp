
#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <iomanip>
#include <list>
#include <cmath>
#include <vector>
#include <chrono>

using namespace std;
const int p = 800;
const int b = 800;
int arr[p][b];
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
    double m;
    double b;

};
class Basket {
public:
    Basket() {  
        a = Point(99.0, 99.0);
        b = Point(99.0, 99.0);
        dist = 99.0;
    }
    Basket(Point a1, Point b1, double dist1){
        a = a1;
        b = b1;
        dist = dist1;
    }
    Point getA() {
        return a;
    }
    Point getB() {
        return b;
    }
    double getDist() {
        return dist;
    }
    Basket(const Basket& pt) { a = pt.a; b = pt.b; dist = pt.dist; }
    Basket compare(Basket j) {
        if (j.getDist() > this->getDist()) {
            return *this;
        }
        else {
            return j;
        }
    }
    ~Basket() {

    }  // destructor; called when the delete is called
private:
    Point a;
    Point b;
    double dist;
};
void createarr(int s1, int s2) {
    for (int i = 0; i < s1; i++) {
        for (int j = 0; j < s2; j++) {
            arr[i][j] = 1;
        }
    }
}
void printArray() {
    for (int x = 0; x < p; x++) {
        for (int y = 0; y < b; y++) {
            cout << arr[x][y] << " ";
        }
        cout << "\n";
    }
}
//shades in everything
void illuminate(int bx, int by, bool color)
{
    // cout << bx << by << "\n";
    if (color) {
        if (0 < bx and bx < p and 0 < by and by < b) {
            arr[bx][by] = 0;
        }
    }
    if (!color) {
        //cout << "  THIS IS REDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD";
        if (0 < bx and bx < p and 0 < by and by < b) {
            arr[bx][by] = 9;
        }
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
        illuminate(i, j, true);
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
        illuminate(i, j, true);
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
        illuminate(j, i, true);
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
        illuminate(j, i, true);
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
        illuminate(i, y1, true);
    }
}
void bresenham6(double x1, double y1, double x2, double y2) { //if x1 and x2 = 0
    if (y1 > y2) {
        swap(y1, y2);
    }
    for (int i = y1; i < y2; i++) {
        illuminate(x1, i, true);
    }
}
//makes a ppm file
void createppm() {
    ofstream file;
    file.open("l031.ppm");
    file << "P3\n" << p << " " << b << "\n1\n";
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (arr[i][j] != 9) {
                file << arr[i][j] << " ";
                file << arr[i][j] << " ";
                file << arr[i][j] << " ";
            }
            if (arr[i][j] == 9) {
                file << 1 << " ";
                file << 0 << " ";
                file << 0 << " ";
            }
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
    double x1 = x3 * p;
    double y1 = y3 * b;
    double x2 = x4 * p;
    double y2 = y4 * b;
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
void circle(double r, Point p1, bool color) {
    double cy1 = p1.getY();
    double cx1 = p1.getX();
    double cy = cy1 * p;
    double cx = cx1 * b;
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
        if (color) {
            illuminate(x + cx, y + cy, true);
            illuminate(x + cx, -y + cy, true);
            illuminate(-x + cx, y + cy, true);
            illuminate(-x + cx, -y + cy, true);
            illuminate(y + cx, x + cy, true);
            illuminate(y + cx, -x + cy, true);
            illuminate(-y + cx, x + cy, true);
            illuminate(-y + cx, -x + cy, true);
        }
        if (!color) {
            illuminate(x + cx, y + cy, false);
            illuminate(x + cx, -y + cy, false);
            illuminate(-x + cx, y + cy, false);
            illuminate(-x + cx, -y + cy, false);
            illuminate(y + cx, x + cy, false);
            illuminate(y + cx, -x + cy, false);
            illuminate(-y + cx, x + cy, false);
            illuminate(-y + cx, -x + cy, false);
        }
        y2_new -= (2 * x) + 3;
    }
}
void partzero() {
    string x;
    ofstream file;
    srand(time(NULL)); //lol makes it diff 60 pts oops
    cout << "how many points do you want in integers" << endl;
    cin >> x;
    createarr(p, b);
    file.open("points.txt");
        //generate 60
    for (int i = 0; i < stof(x); i++) {
            Point z = Point((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX));
            file << setprecision(23) << z.getX() << " " << z.getY() << endl;
    }
    //}
    //if (x == "no") {
    //    file << setprecision(23) << 0.98999999999999999111822 << " " << 0.50000000000000000000000 << endl << 0.95857070123659116056558 << " " << 0.61877366956345547510665 << endl <<
    //        0.90061598205910109449235 << " " << 0.72186199137205808717965;
    //}
    file.close();
}
double dist(Point a, Point b) {
    return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY()));
}
list<Point> getpoints() {
    ifstream file1("points.txt"); //opens pt.txt
    string temp, delimeter;
    list<Point> m;
    int pos;
    delimeter = " ";

    while (getline(file1, temp)) {
        //getline(file1, temp);
        pos = temp.find(delimeter, 0);
        m.push_back(Point(stof(temp.substr(0, pos)), stof(temp.substr(pos + 1, temp.length()))));
    }
    file1.close();
    for (Point x : m) {
        //cout << x.getX() << " " << x.getY() <<endl;
        circle(3, x, true);
        circle(2, x, true);
    }
    return m;
}
ofstream file2("results.txt");
void partone() { //fix opening before friday, do brute force in class/weeknd
    list<Point> l = getpoints();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    double min_dist = 1130.0;
    //list<Point>::iterator it = l.begin();
    //list<Point>::iterator it1 = l.begin();
    Point save_one, save_two;
    for (list<Point>::iterator it = l.begin(); it != l.end(); it++) {
        for (list<Point>::iterator it1 = next(it); it1 != l.end(); it1++) {
            /*    Point temp = &it;
                Point temp1 = &it1;*/
            double temp = dist(*it, *it1);
            //cout << "this is dist: "<< dist(*it, *it1) << endl;
            if (temp < min_dist) {
                save_one = *it;
                save_two = *it1;
                min_dist = temp;
            }
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    circle(3, save_one, false);
    circle(2, save_one, false);
    circle(3, save_two, false);
    circle(2, save_two, false);
    cout << "2 closest points" << "(" << save_one.getX() << ", " << save_one.getY() << ") and (" << save_two.getX() << ", " << save_two.getY() << ")" << endl;
    cout << "min dist: " << min_dist << endl;
    file2 << "USING PART ONE:" << endl << "2 closest points are:" << "(" << save_one.getX() << ", " << save_one.getY() << ") and (" << save_two.getX() << ", " << save_two.getY() << ")" << endl;
    file2 << "min dist: " << min_dist << endl;
    file2 << "Time difference = " <<
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "microseconds" << std::endl;
    cout << "Time difference = " <<
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "microseconds" << std::endl;
  //  createppm();
}

Basket ms(vector<Point> &v, int begin, int end) {
    //double min_dist = 1130.0;
    if ((end-begin) == 1) { //base cases
        return Basket(v[0], v[1], dist(v[0], v[1]));
    }
    if ((end-begin) == 2) { //base cases
        double d = dist(v[0], v[1]); //0
        double d1 = dist(v[1], v[2]); //1
        double d2 = dist(v[0], v[2]); //2
        if (d < d1 and d < d2) {
            return Basket(v[0], v[1], d);;
        }
        if (d1 < d and d1 < d2) {
            return Basket(v[1], v[2],d1);
        }
        else {
            return Basket(v[0], v[2],d2);
        }
    }
    //more than 3 points
    else {
        int index = (end + begin) / 2;
        double min_dist = 1130.0;
        Basket segment;
        Basket segment1 = ms(v, begin, index);
        Basket segment2 = ms(v, index + 1, end);
        if (segment1.getDist() < segment2.getDist()) {
            segment =  segment1;
        }
        else {
            segment = segment2;
        }
        vector<Point> right;
        vector<Point> left;
        //create two vectors one w right stuf one w left stuf
        Point temp;
        min_dist = segment.getDist(); // the smallest dist of one of the two sides
        for (int i = begin; i < index; i++) { //left 0 to mid basically
            temp = v[i];
            if (abs(v[index].getX() - temp.getX()) < min_dist) {
                left.push_back(temp);
            }
        }
        Point temp1;
        for (int f = index; f < end; f++) {
            temp1 = v[f];
            if (abs(temp1.getX() - v[index].getX()) < min_dist) {
                right.push_back(temp1);
            }
        }
       // cout << "this is begin, index, end" << begin << " ," << index << " ," << end << endl;
        //for (Point z : left) {
        //    cout << "L " << z.getX() << endl;
        //}
        //for (Point l : right) {
        //    cout << "R " << l.getX()<<endl;
        //}
        double temp3;
       // Point save_one1, save_two2;

        for (int r = 0; r < right.size(); r++) {
            //cout << "hi right" << endl;
            for (int l = 0; l < left.size(); l++) {
                temp3 = dist(right[r], left[l]);
                //cout << "this is dist: "<< dist(*it, *it1) << endl;
               // cout << "this is left" << endl;
                if (temp3 < min_dist) {
                    min_dist = temp3;
                    segment = Basket(right[r], left[l], temp3);
                }
            }
        }
        //cout << "SIMRITH LOOK EHRE " <<save_one1.getX() << " " << min_dist;
        return segment;
    }
}
    
   // return //min(ms(v{ v.begin(), (int)(size SS+ 1) / 2}, (int)(size + 1) / 2), ms(v{(int)(size + 1) / 2, size}, (int)(size + 1) / 2));

    //recursive here how do you keep track of all the baskets 0, size()/2 size()/2+1, end

void parttwo() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    list<Point> l = Point::getSorted(getpoints());
    vector<Point> m{ std::begin(l), std::end(l) };
    
    //for (Point z : m) {
    //    cout << z.getX() << " ";
    //}
    vector<Point> &lol = m;
    Basket b = ms(lol, 0, m.size()-1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  //  cout << "this is the smallest value " << b.getDist();
    
    cout << "(" << b.getA().getX() << ", " << b.getA().getY() << ") and (" << b.getB().getX()
        << ", " << b.getB().getY() << ") with a distance of " << b.getDist();
    cout << "Time difference = " <<
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "microseconds" << std::endl;
    file2 << "USING PART TWO" << endl << "2 closest points are:(" << b.getA().getX() << ", " << b.getA().getY() << ") and (" << b.getB().getX()
        << ", " << b.getB().getY() << ")" <<endl << "min dist:" << b.getDist() << endl;
    file2 << "Time difference = " <<
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "microseconds" << std::endl;
 
}
int main()
{
   partzero();
   partone();
   parttwo();
}


