#pragma once

#include <opencv2/opencv.hpp>
#include <string>

// 画像処理結果
struct ProcessingResult {
    cv::Mat src;
    cv::Mat gray;
    cv::Mat blur;
    cv::Mat canny;
    cv::Mat usm;
    cv::Mat sobelGx;
    cv::Mat sobelGy;
    cv::Mat outline;
    cv::Mat equalizedHist;
};

// 各処理の実行時間（ミリ秒）
struct ProcessingTimes {
    double gray = 0.0;
    double median = 0.0;
    double canny = 0.0;
    double usm = 0.0;
    double contourDetection = 0.0;
    double contourDrawing = 0.0;
};

cv::Mat ConvertToGray( const cv::Mat& src );

cv::Mat ApplyMedianBlur( const cv::Mat& src, int kernelSize );

cv::Mat ApplyCanny( const cv::Mat& src, double threshold1, double threshold2 );

cv::Mat ApplyUSM( const cv::Mat& src, int blurKernelSize, float amount );

void ApplySobel( const cv::Mat& gray, cv::Mat& sobelGx, cv::Mat& sobelGy );

bool ProcessImage( const std::string& filePath, int blurKernelSize, double cannyThreshold1,
                   double cannyThreshold2, float usmMultiplier, ProcessingResult& result, ProcessingTimes& times );