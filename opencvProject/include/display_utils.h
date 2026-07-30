#pragma once

#include <opencv2/opencv.hpp>
#include "image_processing.h"
#include <string>

void DisplayImage( const std::string& name, const cv::Mat& image );

cv::Mat ToBGR(const cv::Mat& src);

cv::Mat CreateComparisonImage(
    const cv::Mat& img1,
    const cv::Mat& img2,
    const cv::Mat& img3,
    const cv::Mat& img4,
    const cv::Mat& img5,
    const cv::Mat& img6,
    const cv::Mat& img7,
    const cv::Mat& img8,
    double scale);

void ResizeForDisplay( cv::Mat& image, double scale );

void ResizeAllImages( ProcessingResult& result, double scale );

void DisplayResults( const ProcessingResult& result, double comparisonScale );