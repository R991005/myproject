#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::Mat img(480, 940, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::putText(img, "Hello OpenCVfitdyirtd", {30, 80},
                cv::FONT_HERSHEY_SIMPLEX, 2.0, {255, 255, 255}, 2);
    cv::imshow("Sample", img);
    cv::waitKey(0);

    return 0;
}
