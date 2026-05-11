#pragma once
#include <opencv2/opencv.hpp>

cv::Mat ConvertToGray(const cv::Mat& src);
cv::Mat ApplyMedianBlur(const cv::Mat& src, int ksize);
cv::Mat ApplyCanny(const cv::Mat& src, double th1, double th2);
cv::Mat ApplyUSM(const cv::Mat& src, int blurKsize, float amount);