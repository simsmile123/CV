#include <stdio.h>

#include <cmath>

#include <iostream>

#include <fstream>

#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>

using namespace cv;
int main(){// Define the transformation matrices for fluid motion
    cv::Mat R = cv::getRotationMatrix2D(cv::Point2f(0.5, 0.5), 10.0, 1.0);
    cv::Mat S = (cv::Mat_<double>(2, 3) << 1.0, 0.0, 0.0, 0.0, 1.2, 0.0);
    cv::Mat H = (cv::Mat_<double>(2, 3) << 1.0, 0.1, 0.0, 0.1, 1.0, 0.0);

    // Define the sequence of transformations
    std::vector<cv::Mat> transforms;
    transforms.push_back(cv::Mat::eye(2, 3, CV_64FC1));  // Identity transformation
    transforms.push_back(R);                            // Rotation transformation
    transforms.push_back(S);                            // Stretching transformation
    transforms.push_back(H);                            // Shearing transformation

    // Apply the sequence of transformations to an image
    cv::Mat img = cv::imread("input.jpg");
    for (int i = 0; i < transforms.size(); i++) {
        cv::warpAffine(img, img, transforms[i], img.size());
        cv::imshow("Fluid Motion", img);
        cv::waitKey(1000);  // Wait for 1 second between frames
    }
}