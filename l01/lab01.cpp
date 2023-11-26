#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
const int p = 800;
const int b = 800;
int arr[p][b];

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
}void illuminate(int bx, int by)
{
   // cout << bx << by << "\n";
    if (0 < bx and bx < p and 0 < by and by < b) {
        arr[bx][by] = 0;
    }
    
}

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
        illuminate(j,i);
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
void createppm() {
    ofstream file;
    file.open("l011.ppm");
    file << "P3\n" << p << " " << b<< "\n1\n";
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
void totalbresenham(int x1, int y1, int x2, int y2) {
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
        else if (fraction <0) {
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
void circle(double r, double cx, double cy) {
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
        illuminate(x+cx, y+cy);
        illuminate(x + cx, -y + cy);
        illuminate(-x + cx, y + cy);
        illuminate(-x + cx, -y + cy);
        illuminate(y + cx, x + cy);
        illuminate(y + cx, -x + cy);
        illuminate(-y + cx, x + cy);
        illuminate(-y + cx, -x+cy);
        y2_new -= (2 * x) + 3;
    }
}
void generateranddots() {
    srand(time(NULL));
    double x = (double) rand() / (RAND_MAX) *p;
    double y = (double)rand() / (RAND_MAX)*b;
    double x1 = (double)rand() / (RAND_MAX)*p;
    double y1 = (double)rand() / (RAND_MAX)*b;
    double x2 = (double)rand() / (RAND_MAX)*p;
    double y2 = (double)rand() / (RAND_MAX)*b;
   // circle(80, 400, 400);
   
   // circle(3.0, 25.0,25.0);
    totalbresenham(x, y, x1, y1);
    totalbresenham(x1, y1, x2, y2);
    totalbresenham(x2, y2, x, y);
    cout << x << " " << y << " " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    double a = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
    double b = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    double c = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
    double s = (a + b + c) * 0.5;
    double r = sqrt((s - a) * (s - b) * (s - c) / s);

    double perimeter = a + b  +c;
    double ix = (b * x + c * x1 + a * x2) / perimeter;
    double iy = (b * y + c * y1 + a * y2) / perimeter;
    double iradius = sqrt(((s - a) * (s - b) * (s - c)) / s);
    circle(iradius, (int)ix, (int)iy); ///incenter
    
    double R = (a * b * c) / (4 * (r * s));

    double middlex = (x + x1) * 0.5;
    double middlex1 = (x1 + x2) * 0.5;
    double middley = (y + y1) * 0.5;
    double middley1 = (y1 + y2) * 0.5;


    //y- y0 = m(x-x0)
    //int cy = (int)(middlex - middlex1 + m1 * middley1 - m * middley) / (m1 - m);
    //int cx = middlex1 - m1 * middley1 + m1 * cy;

    //cout << " "<< cx << " " << cy << " "<< R;
    double nineptradius = R * 0.5;
    double sl = (double)(y1 - y) / (x1 - x);
    double sl1 = (double)(y2 - y1) / (x2 - x1);
    double m = -1 / sl;
    double m1 = -1 / sl1;
    double a_inter = middley1 - m1 * middlex1;
    double b_inter = middley - m * middlex;
    double cx = (a_inter - b_inter) / (m - m1);
    double cy = cx * m + b_inter;
    circle(R, (int) cx, (int)cy);

    double a_inter1 = y2 - m * x2; //y = gx+a
    double b_inter1 = y - m1 * x; //y = mx+b
    double ox = (a_inter1 - b_inter1) / (m1 - m);
    double oy = ox * m1 + b_inter1;

    double nx = (ox + cx) * 0.5;
    double ny =(oy + cy) * 0.5;
    cout << ox << " " << oy;
    //cout << ox << " " << oy << " " <<cx << " " << cy << endl;
    circle(nineptradius,(int) nx,(int) ny); //fix this
    ////drawline(cx, cy, nx, ny); 
    //cout << nineptradius << " " << nx << " " << ny;
    double e_slope = (oy - cy) / (ox - cx);
    ////x = 0 
    //x = 799 y = mx+b b = y -mx
    double e_intercept = cy - e_slope * cx;
    double e_other = oy - e_slope * ox;
    double ey = e_slope * 0 + e_intercept;
    double ey1 = e_slope * 799 + e_other;
    totalbresenham(0,(int) ey, 799, (int)ey1); //line???
  //  circle(R, intersectionx, intersectiony);
    
}

int main()
{
    ofstream file;
    //bresenham1(0, 0, 5, 3);
    //bresenham2(5,3, 0, 0);
    createarr(p, b);
    //bresenham1(0, 0, 5, 3);
    generateranddots();
    createppm();
   /// printArray();
  /*  file.open("lab1.cpp");
    file << "Writing this to a file.\n";
    file.close();*/
    //cout << "\n\nHello World,\nWelcome to my first C ++ program\n\n" << endl;
    return 0;
} 