#include <QCoreApplication>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat frame;  
    //--- INITIALIZE VIDEOCAPTURE
    VideoCapture cap;
    // Load the trained model
    cv::Ptr<cv::ml::ANN_MLP> mlp = cv::ml::ANN_MLP::load("c:/trained_digit_model.xml");

    // open the default camera using default API
    cap.open(0);

    // OR advance usage: select any API backend
    //int deviceID = 0;             // 0 = open default camera
    //int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    //cap.open(deviceID, apiID);

    // check if we succeeded
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }
    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;

    int widht  = cap.get(CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CAP_PROP_FRAME_HEIGHT);

    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);

        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        std::array bbox_size {60,60};
        Rect rec(widht / 2 - bbox_size[0] / 2, height / 2 - bbox_size[1] / 2, bbox_size[0], bbox_size[1]);
        //rectangle(frame, rec, Scalar(255), 1, 8, 0);
        Mat roi = frame(rec);

        Mat image;
        cvtColor(roi, image, COLOR_BGRA2GRAY);
        //resize(roi, roi, Size(200, 200));
        resize(image, image, Size(28,28));

        //Blur the image with Gaussian kernel
        GaussianBlur(image, image, Size(1, 1), 0);
        threshold( image, image, 5, 255, THRESH_BINARY_INV + THRESH_OTSU);
        //adaptiveThreshold( image, image,255,ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY,11,2);


        Mat flattenedImage = image.reshape(1, 1);
        cv::Mat input;
        flattenedImage.convertTo(input, CV_32F);

        // Perform prediction
        cv::Mat output;
        mlp->predict(input, output);

        //std::cout<<output<<std::endl;
        // Find the class with the highest probability
        cv::Point classIdPoint;
        double confidence;
        cv::minMaxLoc(output, nullptr, &confidence, nullptr, &classIdPoint);

        int predictedClass = classIdPoint.x;

        //std::cout << "Predicted class: " << predictedClass << " with confidence: " << confidence << std::endl;

        if(confidence > 1){
            // Display the result
            std::cout << "Predicted class: " << predictedClass << " with confidence: " << confidence << std::endl;
        }

        imshow("Frame", image);
        imshow("Live", frame);

        imwrite("testimg.png", image);

        if (waitKey(5) >= 0)

            break;
    }

    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}



//Blur the image with 5x5 Gaussian kernel
// GaussianBlur(frame, frame, Size(35, 35), 0);
// threshold( frame, frame, 70, 255, THRESH_BINARY_INV + THRESH_OTSU);

// //Find the contours. Use the contourOutput Mat so the original image doesn't get overwritten
// std::vector<std::vector<cv::Point> > contours;
// Mat contourOutput = frame.clone();
// findContours( contourOutput, contours, RETR_TREE, CHAIN_APPROX_SIMPLE );

// //Draw the contours
// Mat contourImage(frame.size(), CV_8UC3, cv::Scalar(0,0,0));
// Scalar colors[3];
// colors[0] = cv::Scalar(255, 255, 255);
// colors[1] = cv::Scalar(255, 255, 255);
// colors[2] = cv::Scalar(255, 255, 255);
// for (size_t idx = 0; idx < contours.size(); idx++) {
//     drawContours(contourImage, contours, idx, colors[idx % 3]);
//}
