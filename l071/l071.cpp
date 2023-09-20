#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>

using namespace std;

using namespace cv;

int main(int argc, char** argv )
{

    /*
    //next 2 lines would be to create a window and display in the window the image
    //you can uncomment them if you install openCV on your computer
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    */
    //cout << "Let's create a copy now..." << endl;
    
    //now lets create the grayscale image
    int types;
    int distaway, highthres, TC;
    int min_rad, max_rad;

    string grey, fin; //part one

    string FCi, FCo, FR;

    FCi = "imageCircles.jpg"; //red circles
    FCo = "imageCoins.jpg";
    min_rad = 80;
    max_rad = 130;

    TC = 23;
    types = 1;

    distaway = 140;

    highthres = 150;

    grey = "imageg.jpg";

    //string filename = "coins_easy.jpg";

    fin = "imagef.jpg";

    // -f1 myimage1.ppm -f2 myimage2.ppm -ff myimagef.ppm -TC 300 -fv myimagev.ppm -fcc myimageCC.ppm

    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-minr") == 0) {

            min_rad= stoi(argv[i + 1]);

            cout << min_rad << " ";

        }

        if (strcmp(argv[i], "-maxr") == 0) {

            max_rad = stoi(argv[i + 1]);

            cout << max_rad << " ";

        }

        if (strcmp(argv[i], "-type") == 0) {

            types = stoi(argv[i + 1]);

            cout << types<< " ";

        }

        if (strcmp(argv[i], "-fci") == 0) {

            FCi = argv[i + 1];

            cout << FCi<<  " ";

        }
        if (strcmp(argv[i], "-fco") == 0) {

            FCo = argv[i + 1];

            cout << FCo << " ";

        }

        // if (strcmp(argv[i], "-f") == 0) {

        //     filename = argv[i + 1];

        //     cout << filename;

        // }

        if (strcmp(argv[i], "-TC") == 0) {

            TC = stoi(argv[i + 1]);

            cout << TC<< " ";

        }

        if (strcmp(argv[i], "-lt") == 0) {

            distaway = stoi(argv[i + 1]);

            cout << distaway << " ";

        }

        if (strcmp(argv[i], "-fg") == 0) {

            grey = argv[i + 1];

            cout << grey<< " ";

        }

        if (strcmp(argv[i], "-ht") == 0) {

            highthres = stoi(argv[i + 1]);

            cout << highthres << " ";

        }

        if (strcmp(argv[i], "-ff") == 0) {

            fin = argv[i + 1];

            cout << fin << " ";

        }
    }
    Mat image;
    image = imread( argv[1], 1 ); //or filename
    int width = image.cols;
    int height = image.rows;
    imwrite("./copy.jpg", image);
    // Output the size of the image
    cout << "Width: " << width << " pixels" << endl;
    cout << "Height: " << height << " pixels" << endl;
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    Mat gray;
    //cout << "Let's create a grayscale now..." << endl;
    gray = imread( argv[1], IMREAD_GRAYSCALE );
    imwrite(grey, gray);    

    vector<Vec3f> circles;
    cout << "distance each center is away and ht: " << distaway << " "<< highthres << endl;
    cout << "min and max: " << min_rad << " " << max_rad << endl;
    cout << "TC: " << TC << endl;
    GaussianBlur(gray, gray, Size(5, 5), 2, 2);
    Mat edges;
    Canny(gray, edges, highthres/2, highthres);
    imwrite(fin, edges);
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1, distaway, highthres, TC, min_rad, max_rad);
    //cout << "the circle image is ready..." << endl;
; 

//(x, y,r)
//highest is the most common radius ie penny
    int index = 0;
    int highest = 0;
    for (unsigned int a = 0; a < circles.size(); a++)
    {
        int count = 1;
        int Position = circles[a][2];
       //int radius = cvRound(circles[a][2]);
        for (unsigned int b = a + 1; b < circles.size(); b++)
        {
            if (circles[b][2] == Position)
            {
                count++;
            }
        }
        if (count >= index)
        {
            index = count;
            highest = Position;
        }
       // cout << circles[a][2] << endl;
    }
    cout << "mode: " << highest << " "<< index << endl; //penny's radius
    for(int i = 0; i<circles.size(); i++){
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        double radius = circles[i][2];
        circle(image, center, cvRound(radius), Scalar(0, 0, 255), 5);
    }
    imwrite(FCi, image);
    // int averageRadius =0;
    // for (size_t i = 0; i < circles.size(); i++)
    // {
    //    // Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    //     averageRadius += circles[i][2];

    // }
    // averageRadius = averageRadius/circles.size();
    //cout << averageRadius << endl;
    int fpenny = 0;
    int fnickel = 0;
    int fdime = 0;
    int fquarter = 0;
    int fhalf = 0;
    int fsilver = 0;
    int feisan =0;
    vector<double> type;
    if(types == 1) {
    type.push_back(1.0470); 
    type.push_back(1.16);
    type.push_back(3.00);
    };
    if(types == 2) {
    type.push_back(1.0470); 
    type.push_back(1.16);
    type.push_back(3.00);
    //type.push_back(1.77);
    };
    if(types ==3) {
    highest = highest +2;
    cout << highest << endl;
    type.push_back(1.09); 
    type.push_back(1.45);
    type.push_back(1.6);
    //type.push_back(1.28);
    };
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        double radius = circles[i][2];
        // Determine the denomination based on the radius
        Scalar color;
       // color = Scalar(0,0,255);
        //cout << (double)93.3/91 << endl;
        if(radius/highest < type[0]){ //penny or dime...for dime use color
            Vec3b colors = image.at<Vec3b>(center);
            //cout << (int)colors[2] << " "<< (int)colors[1] << " " << (int)colors[0] << endl;
            if(types == 3) {
                if((colors[2]> colors[1]) && (colors[2] > colors[0])) {
                    color = Scalar(0,0,255);
                    fpenny++;
                } else {
                    color = Scalar(255, 0, 0);
                    fdime++;
                }  
            } else {
                color = Scalar(0,0,255);
                fpenny++;
            }
            //cout << radius << endl;
        }
        else if((radius/highest > type[0])&& (radius/highest < type[1])) {
            color = Scalar(0, 255, 255); //nickels
            if(radius < 114.21 && radius > 110){
                color = Scalar(255, 192, 203); // pink
                feisan++;
            }
            cout << radius << endl;
            fnickel++;
        } else if(radius/highest > type[1] && (radius/highest <type[2])) {
            color = Scalar(128, 0, 128); //quarter
            fquarter++;
            //cout << radius << endl;
        } else if (radius/highest > type[2]) {
            color = Scalar(0, 255, 0); // green
            fhalf++;
        } 
        // if (.98 < radius/ pennyCount < 1.02) // penny
        //     color = Scalar(0, 0, 255); // red
        // else if (1.1 < radius / pennyCount < 1.273) // nickel
        //     color = Scalar(0, 255, 255); // yellow
        // else if (.92 < radius / pennyCount < .98) // dime
        //     color = Scalar(255, 0, 0); // blue
        // else //1.27333
        //     color = Scalar(128, 0, 128); // purple
        // else if (radius >= 55 && radius <= 60) // half dollar
        //     color = Scalar(0, 255, 0); // green
        // else // silver dollar or other large coin
        //     color = Scalar(255, 192, 203); // pink
//most common radius == penny, what ratio to penny for other coins set ratio, available online ratios
        // Draw the colored circle around the coin
      //  if(types == 3){
            //if(radius != 114.2){
        circle(image, center, cvRound(radius), color, 5);
            //}
       // }
    }
    // Mat edges;
    // Canny(image, edges, 120, 200);
    ofstream file("results.txt");
    file << "number of pennies: " << fpenny << endl;
    file << "number of nickels: " << fnickel << endl;
    file << "number of dimes: " << fdime << endl;
    file << "number of quarters: " << fquarter << endl;
    file << "number of half-dollars: " << fhalf << endl;
    file << "number of silver dollars: " << fsilver << endl;
    cout << "number of pennies: " << fpenny << endl;
    cout << "number of nickels: " << fnickel << endl;
    cout << "number of dimes: " << fdime << endl;
    cout << "number of quarters: " << fquarter << endl;
    cout << "number of half-dollars: " << fhalf << endl;
    cout << "number of silver dollars: " << fsilver << endl;
    if(types==3) {
        file << "number of eisan dollars: " << feisan << endl;
        cout << "number of eisan dollars: " << feisan << endl;
    }
    double total = fpenny * 0.01 + fnickel * 0.05 + fdime * .1 + fquarter *.25 + fhalf *.5;
    file << "the total: $" << total << endl;
    cout << "the total: $" << total << endl;
    file.close();
    //imshow("Coin Detection", image);
    imwrite(FCo, image);
    waitKey(0);
    
    return 0;
}