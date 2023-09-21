#include <stdio.h>
#include <opencv2/calib3d.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
int CHECKERBOARD[2]{7,7}; 
int main(int argc, char** argv){
    string filename = "withChessBoard.MOV";
    VideoCapture cap(filename);
    if (!cap.isOpened())
    {
        cout << "Error opening video file" << endl;
        return -1;
    }

    // Get video properties
    int frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
    double fps = cap.get(CAP_PROP_FPS);
    vector<Mat> images;
    // Create VideoWriter object to save the video
    VideoWriter writer("vr.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, Size(frameWidth, frameHeight));

    // Process each frame
    while (true)
    {
        Mat frame;
        bool success = cap.read(frame);
        if (!success || frame.empty())
            break;
        images.push_back(frame);

        // Wait for 30 milliseconds (33.33 frames per second)
       // waitKey(30);
    }
    std::vector<std::vector<cv::Point3f> > objpoints;
 
  // Creating vector to store vectors of 2D points for each checkerboard image
    std::vector<std::vector<cv::Point2f> > imgpoints;
    std::vector<std::vector<cv::Point3f> > objpoints20;
  // Creating vector to store vectors of 2D points for each checkerboard image
    std::vector<std::vector<cv::Point2f> > imgpoints20;
    std::vector<std::vector<cv::Point2f> > everyCornerpt;
    std::vector<cv::Point2f> previousPoint;
 
  // Defining the world coordinates for 3D points
    std::vector<cv::Point3f> objp;
    for(int i{0}; i<CHECKERBOARD[1]; i++)
    {
        for(int j{0}; j<CHECKERBOARD[0]; j++) {
            objp.push_back(cv::Point3f(j,i,0));
        }
    }
    cv::Mat frame, gray;
  // vector to store the pixel coordinates of detected checker board corners 
    std::vector<cv::Point2f> corner_pts;
    bool success;
    // Looping over all the images in the directory
    for(int i{0}; i<images.size(); i++)
    {
      frame = images[i];
      cv::cvtColor(frame,gray,cv::COLOR_BGR2GRAY);  
      success = cv::findChessboardCorners(gray, cv::Size(CHECKERBOARD[0], CHECKERBOARD[1]), corner_pts, cv::CALIB_CB_ADAPTIVE_THRESH | cv::CALIB_CB_FAST_CHECK | cv::CALIB_CB_NORMALIZE_IMAGE);
      if(success)
      {
        cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 30, 0.001);
        cv::cornerSubPix(gray,corner_pts,cv::Size(11,11), cv::Size(-1,-1),criteria);
        objpoints.push_back(objp);
        imgpoints.push_back(corner_pts);
        everyCornerpt.push_back(corner_pts);
        previousPoint = corner_pts;
        if(i%20 == 0){
            objpoints20.push_back(objp);
            imgpoints20.push_back(corner_pts);
        }
      } //do optical flow 
      else {
        Mat prevF;
        prevF = images[i-1];
        Mat prevG;
        cv::cvtColor(prevF,prevG,cv::COLOR_BGR2GRAY);  
        vector<uchar> status;
        vector<float> err;
        // Calculate optical flow
        cv::calcOpticalFlowPyrLK(prevG, gray, previousPoint, corner_pts, status, err);
        everyCornerpt.push_back(corner_pts);
        cv::TermCriteria criteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 30, 0.001);
        cv::cornerSubPix(gray,corner_pts,cv::Size(11,11), cv::Size(-1,-1),criteria);
        previousPoint = corner_pts;
      }

    }
 
    //cv::destroyAllWindows();
 
    cv::Mat cameraMatrix,distCoeffs,R,T;
    cv::calibrateCamera(objpoints20, imgpoints20, cv::Size(gray.rows,gray.cols), cameraMatrix, distCoeffs, R, T);
    //solvePnP and
    std::vector<cv::Point3f> dcubepoints = {cv::Point3f(1, 1, 0), cv::Point3f(1, -1, 0), cv::Point3f(1, 1, 0), cv::Point3f(-1, -1, 0)};
    std::vector<cv::Point3f> cubeVertices;
    cubeVertices.push_back(Point3f(1, 1, 0)); //x,y,z
    cubeVertices.push_back(Point3f(1, -1, 0));
    cubeVertices.push_back(Point3f(-1, 1, 0));
    cubeVertices.push_back(Point3f(-1, -1, 0));
    cubeVertices.push_back(Point3f(1, 1, 3));
    cubeVertices.push_back(Point3f(1, -1, 3));
    cubeVertices.push_back(Point3f(-1, 1, 3));
    cubeVertices.push_back(Point3f(-1, -1, 3));
    for(int i{0}; i<images.size(); i++)
    {
        std::vector<cv::Point2f> image4points;
        image4points.push_back(everyCornerpt[i][16]);
        image4points.push_back(everyCornerpt[i][18]);
        image4points.push_back(everyCornerpt[i][30]);
        image4points.push_back(everyCornerpt[i][32]);

        cv::Mat rvec, tvec;
        cv::solvePnP(dcubepoints, image4points, cameraMatrix, distCoeffs, rvec, tvec);

        std::vector<cv::Point2f> projectedPoints;
        cv::projectPoints(cubeVertices, rvec, tvec, cameraMatrix, distCoeffs, projectedPoints);
        cv::Scalar color(0, 255, 0);  // Green
        for (int j = 0; j < 4; j++)
        {
            cv::line(images[i], projectedPoints[j], projectedPoints[(j + 1) % 4], color, 2);  // Base
            cv::line(images[i], projectedPoints[j], projectedPoints[j + 4], color, 2);        // Connecting lines
            cv::line(images[i], projectedPoints[j + 4], projectedPoints[(j + 1) % 4 + 4], color, 2);  // Vertical lines
            cv::line(images[i], projectedPoints[j], projectedPoints[j + 4], color, 2);        // Diagonal lines
        }
        writer.write(images[i]);
    }

    cv::destroyAllWindows();
    return 0;
}
