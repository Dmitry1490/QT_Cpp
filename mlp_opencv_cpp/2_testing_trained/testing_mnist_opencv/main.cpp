#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


int main() {
    // Load the trained model
    cv::Ptr<cv::ml::ANN_MLP> mlp = cv::ml::ANN_MLP::load("c:/trained_digit_model.xml");

    // Load the image you want to classify
    //cv::Mat testImage = cv::imread("C:/mnist_png/testing/1/5.png", cv::IMREAD_GRAYSCALE);  // Assuming the image is grayscale
    cv::Mat testImage = cv::imread("C:/184.png", cv::IMREAD_GRAYSCALE);

    cv::resize(testImage,testImage,cv::Size(28,28));
    // Flatten the image
    cv::Mat flattenedImage = testImage.reshape(1, 1);
    cv::Mat input;
    flattenedImage.convertTo(input, CV_32F);

    // Perform prediction
    cv::Mat output;
    mlp->predict(input, output);

    std::cout<<output<<std::endl;
    // Find the class with the highest probability
    cv::Point classIdPoint;
    double confidence;
    cv::minMaxLoc(output, nullptr, &confidence, nullptr, &classIdPoint);

    int predictedClass = classIdPoint.x;

    // Display the result
    std::cout << "Predicted class: " << predictedClass << " with confidence: " << confidence << std::endl;

    return 0;
}
