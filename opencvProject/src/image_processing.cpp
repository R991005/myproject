#include "../include/image_processing.h"

#include <iostream>
#include <utility>
#include <vector>

namespace {
// 渡された処理の実行時間をミリ秒で返す
template <typename Function>
double MeasureExecutionTime(Function&& function)
{
    const int64 start = cv::getTickCount();

    std::forward<Function>(function)();

    const int64 end = cv::getTickCount();

    return (end - start) * 1000.0 / cv::getTickFrequency();
}

}  // namespace

cv::Mat ConvertToGray( const cv::Mat& src )
{
    cv::Mat dst;

    cv::cvtColor( src, dst, cv::COLOR_BGR2GRAY );

    return dst;
}

cv::Mat ApplyMedianBlur( const cv::Mat& src, int kernelSize )
{
    cv::Mat dst;

    cv::medianBlur( src, dst, kernelSize);

    return dst;
}

cv::Mat ApplyCanny( const cv::Mat& src, double threshold1, double threshold2 )
{
    cv::Mat dst;

    cv::Canny(
        src,
        dst,
        threshold1,
        threshold2);

    return dst;
}

cv::Mat ApplyUSM( const cv::Mat& src, int blurKernelSize, float amount)
{
    const cv::Mat blurred = ApplyMedianBlur(src, blurKernelSize);

    cv::Mat srcFloat;
    cv::Mat blurredFloat;
    cv::Mat sharpenedFloat;
    cv::Mat sharpened;

    src.convertTo(srcFloat, CV_32F);
    blurred.convertTo(blurredFloat, CV_32F);

    sharpenedFloat = srcFloat + amount * (srcFloat - blurredFloat);

    sharpenedFloat.convertTo(sharpened, CV_8U);

    return sharpened;
}

void ApplySobel( const cv::Mat& gray, cv::Mat& sobelGx, cv::Mat& sobelGy )
{
    cv::Mat gx;
    cv::Mat gy;

    cv::Sobel( gray, gx, CV_32F, 1, 0, 3 );

    cv::Sobel( gray, gy, CV_32F, 0, 1, 3 );

    cv::convertScaleAbs(gx, sobelGx);
    cv::convertScaleAbs(gy, sobelGy);
}

bool ProcessImage( const std::string& filePath, int blurKernelSize, double cannyThreshold1, double cannyThreshold2,
                   float usmMultiplier, ProcessingResult& result, ProcessingTimes& times)
{
    result.src = cv::imread(filePath, cv::IMREAD_COLOR);

    if (result.src.empty()) 
    {
        std::cerr << "Failed to load image: " << filePath << '\n';
        return false;
    }

    // グレースケール化
    times.gray = MeasureExecutionTime([&]() {
        result.gray = ConvertToGray(result.src);
    });

    // メディアンフィルター
    times.median = MeasureExecutionTime([&]() {

        result.blur = ApplyMedianBlur( result.gray, blurKernelSize );

    });

    // Cannyエッジ検出
    times.canny = MeasureExecutionTime([&]() {

        result.canny = ApplyCanny( result.blur, cannyThreshold1, cannyThreshold2 );
    
    });

    // アンシャープマスキング
    times.usm = MeasureExecutionTime([&]() {

        result.usm = ApplyUSM( result.gray, blurKernelSize, usmMultiplier);
    
    });

    // Sobelフィルター
    ApplySobel( result.gray, result.sobelGx, result.sobelGy );

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // 輪郭検出
    times.contourDetection =
        MeasureExecutionTime([&]() {

            cv::findContours( result.canny, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );

        });

    // 輪郭描画
    result.outline = result.src.clone();

    times.contourDrawing =
        MeasureExecutionTime([&]() {

            cv::drawContours( result.outline, contours, -1, cv::Scalar(0, 255, 0), 2);

        });

    // ヒストグラム平坦化
    cv::equalizeHist( result.gray, result.equalizedHist);

    return true;
}