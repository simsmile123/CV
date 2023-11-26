#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
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
void part1() {
    Mat image = Mat::zeros(600, 800, CV_8UC3); //new image heigth * width
    auto Points = getPoints(8);
    auto connections = getConnections(8);
    VideoWriter video("rotation.avi", VideoWriter::fourcc('X', 'V', 'I', 'D'), 10, Size(800, 600));
    Mat rot;
    Vec3d angle = {3.14159 * .02, 0, .03 * 3.14159};
    Rodrigues(angle, rot);
    for (int i=0; i< 300; i++){
        for(auto &con : connections) {
            line(image, orthographic(Points[con[0]], 600, 800), orthographic(Points[con[1]], 600, 800), Scalar(255, 255, 255)); //draw line
        }
        video.write(image);
        image = Mat::zeros(600, 800, CV_8UC3); 
        for(int j = 0; j< Points.size(); j++){
            Points[j] = rot * Points[j];
        }
    }
    auto Points1 = getPoints(6);
    auto connections1 = getConnections(6);
        for (int i=0; i< 300; i++){
        for(auto &con : connections1) {
            line(image, orthographic(Points1[con[0]], 600, 800), orthographic(Points1[con[1]], 600, 800), Scalar(255, 255, 255)); //draw line
        }
        video.write(image);
        image = Mat::zeros(600, 800, CV_8UC3); 
        for(int j = 0; j< Points1.size(); j++){
            Points1[j] = rot * Points1[j];
        }
    }
}
int main() {
    part1();
    return 0;
}