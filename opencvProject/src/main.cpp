#include <opencv2/opencv.hpp>
#include "../include/display_utils.h"
#include "../include/image_processing.h"
#include <iostream>
#include <string>

namespace {

constexpr int BLUR_KERNEL_SIZE = 21;
constexpr double CANNY_THRESHOLD_1 = 80.0;
constexpr double CANNY_THRESHOLD_2 = 200.0;
constexpr float USM_MULTIPLIER = 3.0F;
// 個別表示画像の倍率
constexpr double DISPLAY_SCALE = 0.3;
// 比較画像を作成時の画像倍率
constexpr double COMPARISON_WINDOW_SCALE = 0.4;
const std::string COMPARISON_OUTPUT_PATH = "./comparison.png";

void PrintProcessingTimes(
    const ProcessingTimes& times)
{
    std::cout << "ConvertGray time: " << times.gray << " ms\n";

    std::cout << "ApplyBlur time: " << times.median << " ms\n";

    std::cout << "Canny time: " << times.canny << " ms\n";

    std::cout << "Unsharp Masking time: " << times.usm << " ms\n";

    std::cout << "Edge Detection time: " << times.contourDetection << " ms\n";

    std::cout << "Edge Drawing time: " << times.contourDrawing << " ms\n";
}

}  // namespace

int main()
{
    const std::string fileSrc = "./plant.jpeg";

    std::cout << "Kernel Size: " << BLUR_KERNEL_SIZE << '\n';

    ProcessingResult result;
    ProcessingTimes times;

    const bool succeeded = ProcessImage( fileSrc, BLUR_KERNEL_SIZE, CANNY_THRESHOLD_1, 
                                         CANNY_THRESHOLD_2, USM_MULTIPLIER, result, times);

    if (!succeeded) 
    {
        return 1;
    }

    PrintProcessingTimes(times);

    ResizeAllImages( result, DISPLAY_SCALE );

    const bool comparisonSaved = DisplayAndSaveResults(
        result,
        COMPARISON_WINDOW_SCALE,
        COMPARISON_OUTPUT_PATH );

    if (comparisonSaved)
    {
        std::cout << "Comparison image saved: "
                  << COMPARISON_OUTPUT_PATH << '\n';
    }
    else
    {
        std::cerr << "Failed to save comparison image: "
                  << COMPARISON_OUTPUT_PATH << '\n';
    }

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
