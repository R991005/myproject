#include "../include/image_processing.h"

// グレースケール
cv::Mat ConvertToGray(const cv::Mat& src){
    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
    return dst;
}

// メディアンフィルタ
cv::Mat ApplyMedianBlur(const cv::Mat& src, int ksize){
    cv::Mat dst;
    cv::medianBlur(src, dst, ksize);
    return dst;
}

// Canny
cv::Mat ApplyCanny(const cv::Mat& src, double th1, double th2){
    cv::Mat dst;
    cv::Canny(src, dst, th1, th2);
    return dst;
}

// Unsharp Masking 
cv::Mat ApplyUSM(const cv::Mat& src, int blurKsize, float amount){
    cv::Mat img_blur, gray_f, blur_f, diff, sharp, sharp_f;

    img_blur = ApplyMedianBlur(src, blurKsize);
    src.convertTo(gray_f, CV_32F);
    img_blur.convertTo(blur_f, CV_32F);
    
    diff = gray_f - blur_f; // 差分算出
    sharp_f = gray_f + ( amount * diff); // 元画像に差分を加算
    sharp_f.convertTo(sharp, CV_8U);
    return sharp;
}