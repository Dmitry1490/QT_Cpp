#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <QDebug>

struct contour_sorter // 'less' for contours
{
    bool operator ()( const std::vector<cv::Point>& a, const std::vector<cv::Point> & b )
    {
        cv::Rect ra(cv::boundingRect(a));
        cv::Rect rb(cv::boundingRect(b));
        // scale factor for y should be larger than img.width
        return ( (ra.x + 1000*ra.y) < (rb.x + 1000*rb.y) );
    }
};

int main()
{
    //cv::RNG rng(12345);
    cv::Mat testImage = cv::imread("C:/croppedPlate.png", cv::IMREAD_GRAYSCALE);

    cv::blur( testImage, testImage, cv::Size(3,3) );

    cv::threshold(testImage, testImage, 128, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat contourOutput = testImage.clone();
    cv::findContours( contourOutput, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE );

    std::cerr << "before" << std::endl;
    for (int i = 1; i < contours.size(); i++){
        std::cerr << cv::Mat(contours[i]) << std::endl;
    }

    // sort contours
    std::sort(contours.begin(), contours.end(), contour_sorter());

    // cv::Mat finish;
    // std::cerr << "after" << std::endl;
    // for (int i = 1; i < contours.size(); i++){
    //     //std::cerr << cv::Mat(contours[i]) << std::endl;
    //     finish.push_back(cv::Mat(contours[i]));

    //     //cv::imshow("Contours", cv::Mat(contours[i]));
    // }

    //Draw the contours
    cv::Mat contourImage(testImage.size(), CV_8UC3, cv::Scalar(0,0,0));
    cv::Scalar colors[3];
    colors[0] = cv::Scalar(255, 255, 255);
    for (size_t idx = 0; idx < contours.size(); idx++) {
        cv::drawContours(contourImage, contours, idx, colors[0]);
    }

    //cv::imshow("Input Image", testImage);
    //cv::imshow("Contours", contourImage);
    //cv::waitKey(0);

    char *outText;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

    // Open input image with leptonica library
    //Pix *image = pixRead("C:/phototest.tif");

    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    api->SetImage((uchar*)contourImage.data,
                          contourImage.size().width,
                          contourImage.size().height,
                          contourImage.channels(),
                          contourImage.step1());
    api->Recognize(0);
    // Get OCR result
    outText = api->GetUTF8Text();
    QString oText = QString::fromLocal8Bit(outText);
    //printf("OCR output:\n%s", oText.replace("\n", ""));
    qDebug() << oText.replace("\n", " ");

    // Destroy used object and release memory
    api->End();

    delete api;
    delete [] outText;
    //pixDestroy(&image);

    return 0;
 }
