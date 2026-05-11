#include "../include/display_utils.h"

// 画像表示
void DisplayImage(const std::string name, const cv::Mat& img){
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    cv::imshow(name, img);
}

cv::Mat ToBGR(const cv::Mat& src){
    cv::Mat dst;
    if (src.channels() == 1) 
    {
        cv::cvtColor(src, dst, cv::COLOR_GRAY2BGR);
    } 
    else 
    {
        dst = src.clone();
    }
    return dst;
}

cv::Mat CreateComparisonImage(
    const cv::Mat& img1,
    const cv::Mat& img2,
    const cv::Mat& img3,
    const cv::Mat& img4,
    const cv::Mat& img5,
    const cv::Mat& img6,
    const cv::Mat& img7,
    const cv::Mat& img8,
    double scale
){
    cv::Mat a = ToBGR(img1);
    cv::Mat b = ToBGR(img2);
    cv::Mat c = ToBGR(img3);
    cv::Mat d = ToBGR(img4);
    cv::Mat e = ToBGR(img5);
    cv::Mat f = ToBGR(img6);
    cv::Mat g = ToBGR(img7);
    cv::Mat h = ToBGR(img8);

    cv::resize(a, a, cv::Size(), scale, scale, cv::INTER_AREA);
    cv::resize(b, b, cv::Size(), scale, scale, cv::INTER_AREA);
    cv::resize(c, c, cv::Size(), scale, scale, cv::INTER_AREA);
    cv::resize(d, d, cv::Size(), scale, scale, cv::INTER_AREA);
    cv::resize(e, e, cv::Size(), scale, scale, cv::INTER_AREA);
    cv::resize(f, f, cv::Size(), scale, scale, cv::INTER_AREA);
    cv::resize(g, g, cv::Size(), scale, scale, cv::INTER_AREA);
    cv::resize(h, h, cv::Size(), scale, scale, cv::INTER_AREA);

    cv::Mat row1, row2, merged;
    cv::hconcat(std::vector<cv::Mat>{a, b, c, d}, row1);
    cv::hconcat(std::vector<cv::Mat>{e, f, g, h}, row2);
    cv::vconcat(row1, row2, merged);

    return merged;
}