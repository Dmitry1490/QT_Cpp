#include <iostream>
#include <vector>
#include <getopt.h>

#include <opencv2/opencv.hpp>

#include "inference.h"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    //std::string projectBasePath = "/home/user/ultralytics"; // Set your ultralytics base path

    //bool runOnGPU = true;
    bool runOnGPU = false;
    Mat frame;
    VideoCapture cap;
    cap.open(0);

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

    //
    // Pass in either:
    //
    // "yolov8s.onnx" or "yolov5s.onnx"
    //
    // To run Inference with yolov8/yolov5 (ONNX)
    //

    // Note that in this example the classes are hard-coded and 'classes.txt' is a place holder.
    //Inference inf("yolov5s.onnx", cv::Size(640, 640), "classes.txt", runOnGPU);
    Inference inf("yolov8s.onnx", cv::Size(640, 480), "classes.txt", runOnGPU);

    for (;;)
    {

        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);

        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        // Inference starts here...
        std::vector<Detection> output = inf.runInference(frame);

        int detections = output.size();
        std::cout << "Number of detections:" << detections << std::endl;

        for (int i = 0; i < detections; ++i)
        {
            Detection detection = output[i];

            cv::Rect box = detection.box;
            cv::Scalar color = detection.color;

            // Detection box
            cv::rectangle(frame, box, color, 2);

            // Detection box text
            std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
            cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
            cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);

            cv::rectangle(frame, textBox, color, cv::FILLED);
            cv::putText(frame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
        }
        // Inference ends here...

        // This is only for preview purposes
        float scale = 0.8;
        cv::resize(frame, frame, cv::Size(frame.cols*scale, frame.rows*scale));
        cv::imshow("Inference", frame);

        cv::waitKey(-1);
    }
}
