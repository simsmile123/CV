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
Mat_<double> projector(Mat_<double> a,Mat_<double> e,Mat_<double> n, Mat_<double> point){
    // Mat result, result2, result3;
    // subtract(a, e, result);
    // subtract(point, e, result2);
    // add(((result.dot(n)/result2.dot(n)) *result2), e, result3);
    return ((a - e).dot(n)/ (point - e).dot(n)) * (point - e) + e;
    //return result3; //add(result.dot(n)/result2.dot(n) *result2, e, result3);
}
void part2(Mat_ <double> a, Mat_ <double> e, Mat_ <double> n) { //add perspective projection to the images in the video below
    Mat image = Mat::zeros(600, 800, CV_8UC3); //new image heigth * width
    auto Points = getPoints(8);
    // for(int i=0; i< Points.size(); i++){
    //     Points[i] = Points[i] * 100;
    // }
    auto connections = getConnections(8);
    VideoWriter video("rotation.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(800, 600));
    Mat rot;
    //double eyeX = 400, eyeY=0, eyeZ=0; 
    //codouble x1, x2, y1, y2, z1, z2, dist=200;
    //a and n

    ofstream outfile("coordinates.txt");
    ofstream outfile2("coordinates2d.txt");
    ofstream logFile;
    logFile.open("log.txt");
    // auto perspective = (Mat_ < double > (4, 4) << 1, 0, 0, 0, 
    // 0, 1, 0, 0, 
    // 0, 0, 0, 0, 
    // 0, 0,  -1/10, 1);
    Vec3d angle = {3.14159 /180 * 5, 0, 3.14159/180 * 5};
    Rodrigues(angle, rot);
    //cout << "test " << endl;
    for (int i=0; i< 300; i++){
        if(i<4){
            outfile << i +1 << "th set of coordinates" << endl;
        }
        for(int j = 0; j< Points.size(); j++){ 
            Points[j] = rot * Points[j]; //apply rotation
            if(i<4){
                outfile << Points[j] << ", ";
            }
        }
        outfile << endl;
        auto Pv1 = projector(a, e, n, Points[0]);
        auto Pv2 =  projector(a, e, n, Points[1]);
        auto Pv3 = projector(a, e, n, Points[2]);
        vector<Mat_<double>> allPoints;  
        // for(int i = 0; i< Points.size(); i++){ UNCOMMENT IF ALL ELSE FAILS
        //     auto temp = projector(a, e, n, Points[i]);
        //     //cout << temp << endl;
        //     allPoints.push_back(temp); //stores 8 3 by 1s
        // }
        Mat_<double> a1 = Pv1 - Pv2;
        Mat_<double> b1 = Pv3 - Pv2;
        Mat_<double> v1 = a1;
        Mat_<double> v2 = b1 - ((b1.dot(v1))/(v1.dot(v1)))*v1;
        //cout<< << endl;//v1.at<double>(1,0) << endl;
        double distance1 = v1.at<double>(0,0) * v1.at<double>(0,0) + v1.at<double>(1,0) * v1.at<double>(1,0) +v1.at<double>(2,0) * v1.at<double>(2,0);
        double distance2 = v2.at<double>(0,0) * v2.at<double>(0,0) + v2.at<double>(1,0) * v2.at<double>(1,0) +v1.at<double>(2,0) * v2.at<double>(2,0);

        //cout << distance1 << endl;
        Mat_<double> zeroes = (Mat_<double>(3,1)<<0,0,0);
        auto Pv4 = projector(a, e, n, zeroes);
        Mat_<double> p0 = Pv4;
        Mat_<double> w1 = (Mat_<double> (3,1) << v1.at<double>(0,0)/sqrt(distance1), v1.at<double>(1,0)/sqrt(distance1), v1.at<double>(2,0)/sqrt(distance1));
        Mat_<double> w2 = (Mat_<double> (3,1) << v2.at<double>(0,0)/sqrt(distance2), v2.at<double>(1,0)/sqrt(distance2), v2.at<double>(2,0)/sqrt(distance2));
        Mat_<double> combined2;
        // hconcat(p0,w1, combined);
        // hconcat(combined, w2, combined2);
        combined2 = (Mat_<double> (3,3) << p0.at<double>(0,0), v1.at<double>(0,0)/sqrt(distance1), v2.at<double>(0,0)/sqrt(distance2),p0.at<double>(0,1), v1.at<double>(0,1)/sqrt(distance1), v2.at<double>(0,1)/sqrt(distance2), p0.at<double>(0,2), v1.at<double>(0,2)/sqrt(distance1), v2.at<double>(0,2)/sqrt(distance2));
        Mat_<double> inverseM = combined2.inv();
        if(i == 0){
            logFile << "The plane defined by (x-a)*n =0 is: " << endl;
            logFile << "a: " << a << endl << "n: " << n << endl;
            logFile << "The eye e is:" << e << endl;
        }
        if (i < 4) {
            logFile << "this is the " << i + 1 << "th coordinates of p0, w1, w2" << endl;
            logFile << "po: " << p0 << endl << "w1: " << w1 << endl << "w2: " << w2 << endl;
        }
        for(int i =0; i< Points.size(); i++){
            Mat_<double> temp = inverseM * Points[i];
            //cout << combined2 << endl;
            allPoints.push_back(temp); //stores 8 3 by 1s
        }
        double x1, y1, x2, y2;
        for (auto &con: connections) {
            x1 = allPoints[con[0]].at<double>(0) * 100;
            y1 = allPoints[con[0]].at<double>(1) * 100;
            x2 = allPoints[con[1]].at<double>(0) * 100;
            y2 = allPoints[con[1]].at<double>(1) * 100;
            //cout << x1 << " " << y1 << endl;
            if (i < 4) {
                outfile2 << "(" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")" <<endl;
            }
            line(image, Point(x1 +400 , y1 + 300), Point(x2+ 400 , y2 + 300), Scalar(255, 255, 255));
        }
        //combined2 contains the po, w1, and w2
        //invert it and multiple by coordinates of vertices
        // if(i < 4)2
        //     outfile2 << "(" << z1 << ", " << y1 << ")" << endl;
        // }
        // line(image, Point(x1 * 100 + 400 , y1 * 100 + 300), Point(x2 * 100 + 400 , y2 * 100 + 300), Scalar(255, 255, 255));
        // }
        // if(i < 4){
        //     for(int j = 0; j< Points.size(); j++){
        //         outfile << "(" << Points[i].at < double > (0, 0) << ", " << Points[i].at<double>(1, 0) << ", " << Points[i].at<double>(2, 0) << ") , ";
        //     }
        //     outfile << endl;
        // }
        video.write(image);
        image = Mat::zeros(600, 800, CV_8UC3); 
    }
    auto PointsT = getPoints(6);
    // for(int i=0; i< Points.size(); i++){
    //     Points[i] = Points[i] * 100;
    // }
    auto connectionsT = getConnections(6);
    for (int i=0; i< 300; i++){
        for(int j = 0; j< PointsT.size(); j++){ 
            PointsT[j] = rot * PointsT[j]; //apply rotation
        }
        outfile << endl;
        auto Pv1T = projector(a, e, n, PointsT[0]);
        auto Pv2T =  projector(a, e, n, PointsT[1]);
        auto Pv3T = projector(a, e, n, PointsT[2]);
        vector<Mat_<double>> allPointsT;  
        // for(int i = 0; i< Points.size(); i++){ UNCOMMENT IF ALL ELSE FAILS
        //     auto temp = projector(a, e, n, Points[i]);
        //     //cout << temp << endl;
        //     allPoints.push_back(temp); //stores 8 3 by 1s
        // }
        Mat_<double> a1T = Pv1T - Pv2T;
        Mat_<double> b1T = Pv3T - Pv2T;
        Mat_<double> v1T = a1T;
        Mat_<double> v2T = b1T - ((b1T.dot(v1T))/(v1T.dot(v1T)))*v1T;
        //cout<< << endl;//v1.at<double>(1,0) << endl;
        double distance1T = v1T.at<double>(0,0) * v1T.at<double>(0,0) + v1T.at<double>(1,0) * v1T.at<double>(1,0) +v1T.at<double>(2,0) * v1T.at<double>(2,0);
        double distance2T = v2T.at<double>(0,0) * v2T.at<double>(0,0) + v2T.at<double>(1,0) * v2T.at<double>(1,0) +v1T.at<double>(2,0) * v2T.at<double>(2,0);

        //cout << distance1 << endl;
        Mat_<double> zeroesT = (Mat_<double>(3,1)<<0,0,0);
        auto Pv4T = projector(a, e, n, zeroesT);
        Mat_<double> p0T = Pv4T;
        Mat_<double> w1T = (Mat_<double> (3,1) << v1T.at<double>(0,0)/sqrt(distance1T), v1T.at<double>(1,0)/sqrt(distance1T), v1T.at<double>(2,0)/sqrt(distance1T));
        Mat_<double> w2T = (Mat_<double> (3,1) << v2T.at<double>(0,0)/sqrt(distance2T), v2T.at<double>(1,0)/sqrt(distance2T), v2T.at<double>(2,0)/sqrt(distance2T));
        Mat_<double> combined2T;
        // hconcat(p0,w1, combined);
        // hconcat(combined, w2, combined2);
        combined2T = (Mat_<double> (3,3) << p0T.at<double>(0,0), v1T.at<double>(0,0)/sqrt(distance1T), v2T.at<double>(0,0)/sqrt(distance2T),p0T.at<double>(0,1), v1T.at<double>(0,1)/sqrt(distance1T), v2T.at<double>(0,1)/sqrt(distance2T), p0T.at<double>(0,2), v1T.at<double>(0,2)/sqrt(distance1T), v2T.at<double>(0,2)/sqrt(distance2T));
        Mat_<double> inverseMT = combined2T.inv();
        for(int i =0; i< PointsT.size(); i++){
            Mat_<double> temp = inverseMT * PointsT[i];
            //cout << combined2 << endl;
            allPointsT.push_back(temp); //stores 8 3 by 1s
        }
        double x1T, y1T, x2T, y2T;
        for (auto &con: connectionsT) {
            x1T = allPointsT[con[0]].at<double>(0) * 100;
            y1T = allPointsT[con[0]].at<double>(1) * 100;
            x2T = allPointsT[con[1]].at<double>(0) * 100;
            y2T = allPointsT[con[1]].at<double>(1) * 100;
            line(image, Point(x1T +400 , y1T + 300), Point(x2T+ 400 , y2T + 300), Scalar(255, 255, 255));
        }
        //combined2 contains the po, w1, and w2
        //invert it and multiple by coordinates of vertices
        // if(i < 4)2
        //     outfile2 << "(" << z1 << ", " << y1 << ")" << endl;
        // }
        // line(image, Point(x1 * 100 + 400 , y1 * 100 + 300), Point(x2 * 100 + 400 , y2 * 100 + 300), Scalar(255, 255, 255));
        // }
        // if(i < 4){
        //     for(int j = 0; j< Points.size(); j++){
        //         outfile << "(" << Points[i].at < double > (0, 0) << ", " << Points[i].at<double>(1, 0) << ", " << Points[i].at<double>(2, 0) << ") , ";
        //     }
        //     outfile << endl;
        // }
        video.write(image);
        image = Mat::zeros(600, 800, CV_8UC3); 
    }
}

int main(int argc, char** argv){
    Mat_<double> e = (Mat_ <double> (3,1) << 0, 0, 7);
    Mat_<double> a = (Mat_ <double>  (3,1) << 0, 0, 2);
    Mat_<double> n = (Mat_ <double> (3,1) << 0, 0, 1);
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-a") == 0) { 
            string temp = argv[i+1]; // "(1, 2, 3)"
            temp = temp.substr(1, temp.length() - 2);
            std::stringstream ss(temp);
            double num;
            int x = 0;
            while (ss >> num) {
                a(x, 0) = num;
                ss.ignore();
                x++;
            }
        }
        if (strcmp(argv[i], "-e") == 0) {
            string temp = argv[i+1]; // "(1, 2, 3)"
            temp = temp.substr(1, temp.length() - 2);
            std::stringstream ss(temp);
            double num;
            int x = 0;
            while (ss >> num) {
                e(x, 0) = num;
                ss.ignore();
                x++;
            }
         }
        if (strcmp(argv[i], "-n") == 0) {
                        string temp = argv[i+1]; // "(1, 2, 3)"
            temp = temp.substr(1, temp.length() - 2);
            std::stringstream ss(temp);
            double num;
            int x = 0;
            while (ss >> num) {
                n(x, 0) = num;
                ss.ignore();
                x++;
            }
        }
    }
    //cout << a ;
    part2(a, e, n);
    return 0;
}
