#define _USE_MATH_DEFINES
#include <opencv2/opencv.hpp>
#include "../include/image_processing.h"
#include "../include/display_utils.h"
#include <iostream>
#include <cmath>

#define BLUR_KERNEL_SIZE    (7)       // ぼかしカーネルサイズ
#define CANNY_THRESHOLD_1   (80)      // CANNY闘値１
#define CANNY_THRESHOLD_2   (200)     // CANNY闘値2
#define USM_MULTIPLIER      (3)       // USM倍率
#define COMPARISON_WINDOW_SIZE (0.1)  // 比較画像各ウィンドウサイズ倍率

int main() {
    std::string file_src = "./rail.jpeg";
    std::string file_dst = "dst.png"; // 出力画像のファイル名
    cv::Mat img_src = cv::imread(file_src, cv::IMREAD_COLOR);
    
    if (!img_src.data){
        std::cout << "error" << std::endl;
        return 0;
    }

    std::cout << "Kernal Size: " << BLUR_KERNEL_SIZE << std::endl;

    // 処理時間
    int n = 100;
    double t1 = 0;
    double t2 = 0;

    double total_ms_gray = 0;
    // グレイスケール化
    cv::Mat img_gray;
    for (int i = 0; i < n; i++){
        t1 = cv::getTickCount();
        img_gray = ConvertToGray(img_src);
        t2 = cv::getTickCount();
        total_ms_gray += (t2 - t1)* 1000.0 / cv::getTickFrequency();
    }
    // 平均算出
    double ave_time_gray = total_ms_gray / (double)n;
    std::cout << "ConvertGray time: " << ave_time_gray << "ms" << std::endl;
    
    // メディアン処理
    double total_ms_median = 0.0;
    cv::Mat img_blur;
    for (int i = 0; i < n; i++){
        t1 = cv::getTickCount();
        img_blur = ApplyMedianBlur(img_gray, BLUR_KERNEL_SIZE);
        t2 = cv::getTickCount();
        total_ms_median += (t2 - t1)* 1000.0 / cv::getTickFrequency();
    }
    // 平均算出
    double ave_time_blue = total_ms_median / (double)n;
    std::cout << "ApplyBlur time: " << ave_time_blue << "ms" << std::endl;

    // Canny処理
    double total_ms_canny = 0.0;
    cv::Mat img_canny;
    for (int i = 0; i < n; i++){
        t1 = cv::getTickCount();
        img_canny = ApplyCanny(img_blur, CANNY_THRESHOLD_1, CANNY_THRESHOLD_2); 
        t2 = cv::getTickCount();
        total_ms_canny += (t2 - t1)* 1000.0 / cv::getTickFrequency();
    }
    // 平均算出
    double ave_time_canny = total_ms_canny / (double)n;
    std::cout << "Canny time: " << ave_time_canny << "ms" << std::endl;
    
    // USM処理
    double total_ms_usm = 0.0;
    cv::Mat img_usm;
    for (int i = 0; i < n; i++){    
        t1 = cv::getTickCount();
        img_usm = ApplyUSM(img_gray, BLUR_KERNEL_SIZE, USM_MULTIPLIER);
        t2 = cv::getTickCount();
        total_ms_usm += (t2 - t1)* 1000.0 / cv::getTickFrequency();
    }
    // 平均算出
    double ave_time_usm = total_ms_usm / (double)n;
    std::cout << "Unsharp Masking time: " << ave_time_usm << "ms" << std::endl;

    // Sobelフィルタ
    cv::Mat img_sobel_gx, img_sobel_gy,img_sobel_gx_abs, img_sobel_gy_abs;
    cv::Sobel(img_gray, img_sobel_gx, CV_32F, 1, 0, 3);
    cv::Sobel(img_gray, img_sobel_gy, CV_32F, 0, 1, 3);
    cv::convertScaleAbs(img_sobel_gx, img_sobel_gx_abs);
    cv::convertScaleAbs(img_sobel_gy, img_sobel_gy_abs);

    // 輪郭抽出処理
    double total_ms_outline = 0.0;
    cv::Mat img_outline, img_binary;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<std::vector<cv::Point>> contours;
    for (int i = 0; i < n; i++){  
        t1 = cv::getTickCount();
        cv::findContours( img_canny, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        t2 = cv::getTickCount();
        total_ms_outline += (t2 - t1)* 1000.0 / cv::getTickFrequency();
    }
    // 平均算出
    double ave_time_outline = total_ms_outline / (double)n;
    std::cout << "Edge Detection time: " << ave_time_outline << "ms" << std::endl;

    // 輪郭描画処理
    double total_ms_draw = 0.0;
    for (int i = 0; i < n; i++){
        img_outline = img_src.clone();
        t1 = cv::getTickCount();
        cv::drawContours(img_outline, contours, -1, cv::Scalar(0, 255, 0), 2);
        t2 = cv::getTickCount();
        total_ms_draw += (t2 - t1)* 1000.0 / cv::getTickFrequency();
    }
    // 平均算出
    double ave_time_draw = total_ms_draw / (double)n;
    std::cout << "Edge Drawing time: " << ave_time_draw << "ms" << std::endl;

    // ヒストグラム平坦化
    cv::Mat hist;
    cv::equalizeHist(img_gray, hist);

    // 画像をウィンドウに出力
    DisplayImage("src", img_src);
    DisplayImage("gray", img_gray);
    DisplayImage("blur", img_blur);
    DisplayImage("canny", img_canny);
    DisplayImage("usm", img_usm);
    DisplayImage("sobel_gx", img_sobel_gx_abs);
    DisplayImage("sobel_gy", img_sobel_gy_abs);
    DisplayImage("outline", img_outline);
    DisplayImage("equaliseHist", hist);

    // 比較一覧をウィンドウに出力
    cv::Mat comparison_window;
    comparison_window = CreateComparisonImage(img_src, img_gray, img_blur, img_canny, 
                                              img_usm, img_outline, img_sobel_gx_abs, img_sobel_gy_abs, 
                                              COMPARISON_WINDOW_SIZE);
    DisplayImage("comparison_window", comparison_window);

    cv::waitKey(0);

    return 0;
}
