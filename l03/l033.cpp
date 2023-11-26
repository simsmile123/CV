
#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <iomanip>
#include <list>
#include <cmath>
#include <vector>
#include <chrono>
#include <algorithm>

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

class Basket {
public:
    Basket() {
        a = Point(99.0, 99.0);
        b = Point(99.0, 99.0);
        dist = 99.0;
    }
    Basket(Point a1, Point b1, double dist1) {
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
        Point z = Point((double)rand() / (RAND_MAX), (double)rand() / (RAND_MAX)); //creates a point with x and y values between 0 and 1
        file << setprecision(23) << z.getX() << "  " << z.getY() << endl;
    }
    //}
    //if (x == "no") {
    //    file << setprecision(23) << 0.98999999999999999111822 << " " << 0.50000000000000000000000 << endl << 0.95857070123659116056558 << " " << 0.61877366956345547510665 << endl <<
    //        0.90061598205910109449235 << " " << 0.72186199137205808717965;
    //}
  //  file.close();
}
double dist(Point a, Point b) {
    return sqrt((a.getX() - b.getX()) * (a.getX() - b.getX()) + (a.getY() - b.getY()) * (a.getY() - b.getY()));
}
list<Point> getpoints() {
    ifstream file1; //opens pt.txt
    file1.open("points10k.txt"); //why does this not work with points1k but works with points if both files are at the same place???
    string temp, delimeter;
    list<Point> m;
    int pos;
    delimeter = " ";

    while (getline(file1, temp)) {
        //getline(file1, temp);
        pos = temp.find(delimeter, 0);
        m.push_back(Point(stod(temp.substr(0, pos)), stod(temp.substr(pos + 2, temp.length()))));
    }
    file1.close();
    return m;
}
ofstream file2("results.txt");
void partone() { //fix opening before friday, do brute force in class/weeknd
    list<Point> l = getpoints();
    for (Point x : l) {
        cout << setprecision(25) << x.getX() << " " << x.getY() << endl;
    }
    cout << "end of list" << endl;
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
    cout << "2 closest points" << "(" << save_one.getX() << ", " << save_one.getY() << ") and (" << save_two.getX() << ", " << save_two.getY() << ")" << endl;
    cout << "min dist: " << min_dist << endl;
    file2 << setprecision(23) << "USING PART ONE:" << endl << "2 closest points are:" << "(" << save_one.getX() << ", " << save_one.getY() << ") and (" << save_two.getX() << ", " << save_two.getY() << ")" << endl;
    file2 << "min dist: " << min_dist << endl;
    file2 << "Time difference = " <<
        std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " seconds" << std::endl;
    cout << "Time difference = " <<
        std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " seconds" << std::endl;
    //  createppm();
}

Basket ms(vector<Point>& v, int begin, int end) {
    //double min_dist = 1130.0;
    if ((end - begin) == 1) { //base cases
        return Basket(v[0], v[1], dist(v[0], v[1]));
    }
    if ((end - begin) == 2) { //base cases
        double d = dist(v[0], v[1]); //0
        double d1 = dist(v[1], v[2]); //1
        double d2 = dist(v[0], v[2]); //2
        if (d < d1 and d < d2) {
            return Basket(v[0], v[1], d);;
        }
        if (d1 < d and d1 < d2) {
            return Basket(v[1], v[2], d1);
        }
        else {
            return Basket(v[0], v[2], d2);
        }
    }
    //more than 3 points
    else {
        int index = (end + begin) / 2;
        // double min_dist = 1130.0;
        Basket segment;
        Basket segment1 = ms(v, begin, index);
        Basket segment2 = ms(v, index + 1, end);
        if (segment1.getDist() < segment2.getDist()) {
            segment = segment1;
        }
        else {
            segment = segment2;
        }
        vector<Point> right;
        vector<Point> left;
        //create two vectors one w right stuf one w left stuf

        double min_dist = segment.getDist(); // the smallest dist of one of the two sides
        for (int i = begin; i <= index; i++) { //left 0 to mid basically
            Point temp = v[i];
            if (abs(v[index].getX() - temp.getX()) < min_dist) {
                left.push_back(temp);
            }
        }
        // cout << "this is middle x    " << v[index].getX() << endl;
        for (int f = index + 1; f <= end; f++) {
            Point temp1 = v[f];
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
        if (right.size() > 0 && left.size() > 0) {
            for (size_t r = 0; r < right.size(); r++) {
                //cout << "hi right" << endl;
                for (size_t l = 0; l < left.size(); l++) {
                    double temp3 = dist(right[r], left[l]);
                    if (temp3 == 0) {
                        continue;
                    }
                    if (temp3 < min_dist) {
                        min_dist = temp3;
                        segment = Basket(right[r], left[l], temp3);
                    }
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
    list<Point> l = Point::getSorted(getpoints());
    vector<Point> m{ std::begin(l), std::end(l) };
    //for (Point z : m) {
    //    cout << z.getX() << " ";
    //}
    vector<Point>& lol = m;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Basket b = ms(lol, 0, m.size() - 1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //  cout << "this is the smallest value " << b.getDist();
    cout << setprecision(23) << "USING PART TWO" << endl << "2 closest points are:(" << b.getA().getX() << ", " << b.getA().getY() << ") and (" << b.getB().getX()
        << ", " << b.getB().getY() << ")" << endl << "min dist:" << b.getDist() << endl;
    cout << "Time difference = " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
    file2 << setprecision(23) << "USING PART TWO" << endl << "2 closest points are:(" << b.getA().getX() << ", " << b.getA().getY() << ") and (" << b.getB().getX()
        << ", " << b.getB().getY() << ")" << endl << "min dist:" << b.getDist() << endl;
    file2 << "Time difference = " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;

}

bool comparey(Point p, Point p2) {
    return p.getY() < p2.getY();
}

Basket threerecur(vector<Point>& v, int begin, int end) {
    //double min_dist = 1130.0;
    if ((end - begin) == 1) { //base cases
        return Basket(v[0], v[1], dist(v[0], v[1]));
    }
    if ((end - begin) == 2) { //base cases
        double d = dist(v[0], v[1]); //0
        double d1 = dist(v[1], v[2]); //1
        double d2 = dist(v[0], v[2]); //2
        if (d < d1 and d < d2) {
            return Basket(v[0], v[1], d);;
        }
        if (d1 < d and d1 < d2) {
            return Basket(v[1], v[2], d1);
        }
        else {
            return Basket(v[0], v[2], d2);
        }
    }
    //more than 3 points
    else {
        int index = (end + begin) / 2;
        // double min_dist = 1130.0;
        Basket segment;
        Basket segment1 = threerecur(v, begin, index);
        Basket segment2 = threerecur(v, index + 1, end);
        if (segment1.getDist() < segment2.getDist()) {
            segment = segment1;
        }
        else {
            segment = segment2;
        }
        vector<Point> vectorStrip;
        //create two vectors one w right stuf one w left stuf
        double min_dist = segment.getDist(); // the smallest dist of one of the two sides
        for (int i = begin; i <= end; i++) {
            if (abs(v[i].getX() - v[index].getX()) < min_dist) {
                vectorStrip.push_back(v[i]);
            }
        }
        //cout << "this is begin, index, end " << begin << ", " << index << ", " << end << "    " << min_dist << "           ";
        //cout << "vectorstrip size: " << vectorStrip.size() << endl;
        sort(vectorStrip.begin(), vectorStrip.end(), comparey);
        //g) for each point in vectorStrip calculate the distance to max of 15 
             //following points to see if you can find a smaller distance than d, 
             //then update the d and the points. This is O(15n)=O(n)
        for (size_t i = 0; i < vectorStrip.size(); i++) {
            for (size_t j = i + 1; j <= i + 15; j++) {
                if (j >= vectorStrip.size()) {
                    break;
                }
                if (dist(vectorStrip[i], vectorStrip[j]) == 0) {
                    continue;
                }
                if (min_dist > dist(vectorStrip[i], vectorStrip[j])) {
                    min_dist = dist(vectorStrip[i], vectorStrip[j]);
                    segment = Basket(vectorStrip[i], vectorStrip[j], dist(vectorStrip[i], vectorStrip[j]));
                }
            }
        }
        return segment;
    }
}
void partthree() {
    list<Point> l = Point::getSorted(getpoints());
    vector<Point> m{ std::begin(l), std::end(l) };
    vector<Point>& lol = m;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Basket b = threerecur(lol, 0, m.size() - 1);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //  cout << "this is the smallest value " << b.getDist();
    cout << "USING PART THREE" << endl << "2 closest points are:(" << b.getA().getX() << ", " << b.getA().getY() << ") and (" << b.getB().getX()
        << ", " << b.getB().getY() << ")" << endl << "min dist:" << b.getDist() << endl;
    cout << "Time difference = " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
    file2 << setprecision(23) << "USING PART THREE" << endl << "2 closest points are:(" << b.getA().getX() << ", " << b.getA().getY() << ") and (" << b.getB().getX()
        << ", " << b.getB().getY() << ")" << endl << "min dist:" << b.getDist() << endl;
    file2 << "Time difference = " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
}
int main()
{
   // partzero(); //comment out
     // partone();
    parttwo();
    partthree();
}