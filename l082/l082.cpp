#include <stdio.h>

#include <cmath>

#include <iostream>

#include <fstream>

#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>

using namespace std;

using namespace cv;

vector < Mat > getPoints(int vertices) {
    vector < Mat > Points;
    if (vertices == 8) {
        //(1,1,1), (1,1,-1), (1,-1,1) , (1,-1,-1), (-1,1,1), (-1,1,-1), (-1,-1,1) , (-1,-1,-1)
        Points.push_back((Mat_ < double > (3, 1) << 1, 1, 1));
        Points.push_back((Mat_ < double > (3, 1) << 1, 1, -1));
        Points.push_back((Mat_ < double > (3, 1) << 1, -1, 1));
        Points.push_back((Mat_ < double > (3, 1) << 1, -1, -1));
        Points.push_back((Mat_ < double > (3, 1) << -1, 1, 1));
        Points.push_back((Mat_ < double > (3, 1) << -1, 1, -1));
        Points.push_back((Mat_ < double > (3, 1) << -1, -1, 1));
        Points.push_back((Mat_ < double > (3, 1) << -1, -1, -1));
    } 
    if (vertices ==6) { 
        Points.push_back((Mat_ < double > (3, 1) << 1, 0, 0));
        Points.push_back((Mat_ < double > (3, 1) << -1, 0, 0));
        Points.push_back((Mat_ < double > (3, 1) << 0, 1, 0));
        Points.push_back((Mat_ < double > (3, 1) << 0, -1, 0));
        Points.push_back((Mat_ < double > (3, 1) << 0, 0, 1));
        Points.push_back((Mat_ < double > (3, 1) << 0, 0, -1));
    }
    return Points;
}

vector<Vec2i> getConnections(int vertices){
    vector<Vec2i> connections;
    if (vertices == 8) {
        connections.push_back({ 0,1 });
        connections.push_back({ 0,2 });
        connections.push_back({ 0,4 });
        connections.push_back({ 1,3 });
        connections.push_back({ 1,5 });
        connections.push_back({ 2,3 });
        connections.push_back({ 2,6 });
        connections.push_back({ 3,7 });
        connections.push_back({ 4,5 });
        connections.push_back({ 4,6 });
        connections.push_back({ 5,7 });
        connections.push_back({ 6,7 });
    }
    if (vertices ==6){ //octahedron
        connections.push_back({ 0,2 });
        connections.push_back({ 0,3 });
        connections.push_back({ 0,4 });
        connections.push_back({ 0,5 });
        connections.push_back({ 1,2 });
        connections.push_back({ 1,3 });
        connections.push_back({ 1,4 });
        connections.push_back({ 1,5 });
        connections.push_back({ 2,4 });
        connections.push_back({ 3,4 });
        connections.push_back({ 3,5 });
        connections.push_back({ 2,5 });
    }
    return connections;
}
Point orthographic(Mat vert, int height, int width){
    return Point2d(
            vert.at < double > (0, 0) * 100 + width/2, 
            vert.at < double > (1, 0) * 100 + height/2
        );
}

void part2() { //add perspective projection to the images in the video below
    Mat image = Mat::zeros(600, 800, CV_8UC3); //new image heigth * width
    auto Points = getPoints(8);
    auto connections = getConnections(8);
    VideoWriter video("rotation.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(800, 600));
    Mat rot;
    double eyeX = 10, eyeY=0, eyeZ=0; //(10,0,0)
    double x1, x2, y1, y2, z1, z2, dist=5;
    ofstream outfile("coordinates.txt");
    ofstream outfile2("coordinates2d.txt");
    Vec3d angle = {3.14159 * .02, 0, .03 * 3.14159};
    Rodrigues(angle, rot);
    //cout << "test " << endl;
    for (int i=0; i< 300; i++){
        for(int j = 0; j< Points.size(); j++){ 
            Points[j] = rot * Points[j]; //apply rotation
        }
        // if( i>4){
        //     outfile << "these are the values of the points after rotation: " << endl;
        //     for(int j = 0; j< Points.size(); j++){
        //         outfile << "(" << Points[j].at < double > (0, 0) << ", " << Points[j].at<double>(1, 0) << ", " << Points[j].at<double>(2, 0) << ") , ";
        //     }
        // }
        //cout << "test " << endl;
        for (auto &con: connections) {
            x1 = Points[con[0]].at < double > (0, 0), y1 = Points[con[0]].at < double > (1, 0), z1= Points[con[0]].at < double > (2, 0), x2 = Points[con[1]].at < double > (0, 0), y2 = Points[con[1]].at < double > (1, 0), z2=Points[con[1]].at < double > (2, 0);
            double t1 = (dist-eyeX)/(x1-eyeX);
            double t2 = (dist-eyeX)/(x2-eyeX);
            double tempY1 = t1*y1 + (1-t1)*eyeY;
            double tempY2 = t2*y2 + (1-t2)*eyeY;
            double tempZ1 = t1*z1 + (1-t1)*eyeZ;
            double tempZ2 = t2*z2 + (1-t2)*eyeZ;
            y1 = tempY1;
            y2 = tempY2;
            x1 = tempZ1;
            x2 = tempZ2;
            if(i < 4){
                outfile2 << "(" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")" << endl;
            }
            
            // Points[con[0]].at < double > (0, 0) = x1;
            // Points[con[0]].at < double > (1, 0) = y1;
            // Points[con[0]].at < double > (2, 0) = z1;
            // Points[con[1]].at < double > (0, 0) = x2;
            // Points[con[1]].at < double > (1, 0) = y2;
            // Points[con[1]].at < double > (2, 0) = z2;
            line(image, Point(x1 * 100 + 300 , y1 * 100 + 400), Point(x2 * 100 + 300 , y2 * 100 + 400), Scalar(255, 255, 255));
        }
        if(i < 4){
            for(int j = 0; j< Points.size(); j++){
                outfile << "(" << Points[j].at < double > (0, 0) * 100 << ", " << Points[j].at<double>(1, 0) * 100 << ", " << Points[j].at<double>(2, 0) * 100 << ") , ";
            }
            outfile << endl;
        }
        video.write(image);
        image = Mat::zeros(600, 800, CV_8UC3); 
    }
    auto Points1 = getPoints(6);
    auto connections1 = getConnections(6);
    for (int i=0; i< 300; i++){
        for(int j = 0; j< Points1.size(); j++){ 
            Points1[j] = rot * Points1[j]; //apply rotation
        }
        //cout << "test " << endl;
        for (auto &con: connections1) {
            x1 = Points1[con[0]].at < double > (0, 0), y1 = Points1[con[0]].at < double > (1, 0), z1= Points1[con[0]].at < double > (2, 0), x2 = Points[con[1]].at < double > (0, 0), y2 = Points[con[1]].at < double > (1, 0), z2=Points[con[1]].at < double > (2, 0);
            double t1 = (dist-eyeX)/(x1-eyeX);
            double t2 = (dist-eyeX)/(x2-eyeX);
            double tempY1 = t1*y1 + (1-t1)*eyeY;
            double tempY2 = t2*y2 + (1-t2)*eyeY;
            double tempZ1 = t1*z1 + (1-t1)*eyeZ;
            double tempZ2 = t2*z2 + (1-t2)*eyeZ;
            y1 = tempY1;
            y2 = tempY2;
            x1 = tempZ1;
            x2 = tempZ2;
            // Points[con[0]].at < double > (0, 0) = x1;
            // Points[con[0]].at < double > (1, 0) = y1;
            // Points[con[0]].at < double > (2, 0) = z1;
            // Points[con[1]].at < double > (0, 0) = x2;
            // Points[con[1]].at < double > (1, 0) = y2;
            // Points[con[1]].at < double > (2, 0) = z2;
            line(image, Point(x1 * 100 + 300 , y1 * 100 + 400), Point(x2 * 100 + 300 , y2 * 100 + 400), Scalar(255, 255, 255));
        }
        video.write(image);
        image = Mat::zeros(600, 800, CV_8UC3); 
    }
    //imshow("Square?", image);
    //waitKey(0);
}

int main() {
    part2();
    return 0;
}




