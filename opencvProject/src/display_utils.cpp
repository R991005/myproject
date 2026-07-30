#include "../include/display_utils.h"
#include <vector>

void DisplayImage( const std::string& name, const cv::Mat& image )
{
    if (image.empty()) 
    {
        return;
    }

    cv::namedWindow( name, cv::WINDOW_AUTOSIZE );

    cv::imshow(name, image);
}

cv::Mat ToBGR(const cv::Mat& src)
{
    cv::Mat dst;

    if (src.channels() == 1) 
    {
        cv::cvtColor( src, dst, cv::COLOR_GRAY2BGR);
    }
    else 
    {
        dst = src.clone();
    }

    return dst;
}

void ResizeForDisplay( cv::Mat& image, double scale )
{
    if (image.empty()) 
    {
        return;
    }

    cv::resize( image, image, cv::Size(), scale, scale, cv::INTER_AREA);
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
    double scale)
{
    cv::Mat a = ToBGR(img1);
    cv::Mat b = ToBGR(img2);
    cv::Mat c = ToBGR(img3);
    cv::Mat d = ToBGR(img4);
    cv::Mat e = ToBGR(img5);
    cv::Mat f = ToBGR(img6);
    cv::Mat g = ToBGR(img7);
    cv::Mat h = ToBGR(img8);

    ResizeForDisplay(a, scale);
    ResizeForDisplay(b, scale);
    ResizeForDisplay(c, scale);
    ResizeForDisplay(d, scale);
    ResizeForDisplay(e, scale);
    ResizeForDisplay(f, scale);
    ResizeForDisplay(g, scale);
    ResizeForDisplay(h, scale);

    cv::Mat row1;
    cv::Mat row2;
    cv::Mat merged;

    cv::hconcat( std::vector<cv::Mat>{a, b, c, d}, row1 );

    cv::hconcat( std::vector<cv::Mat>{e, f, g, h}, row2 );

    cv::vconcat(row1, row2, merged);

    return merged;
}

void ResizeAllImages( ProcessingResult& result, double scale )
{
    ResizeForDisplay( result.src, scale );
    ResizeForDisplay( result.gray, scale );
    ResizeForDisplay( result.blur, scale );
    ResizeForDisplay( result.canny, scale );
    ResizeForDisplay( result.usm, scale );
    ResizeForDisplay( result.sobelGx, scale );
    ResizeForDisplay( result.sobelGy, scale );
    ResizeForDisplay( result.outline, scale );
    ResizeForDisplay( result.equalizedHist, scale );
}

void DisplayResults( const ProcessingResult& result, double comparisonScale )
{
    DisplayImage( "src", result.src) ;
    DisplayImage( "gray", result.gray );
    DisplayImage( "blur", result.blur );
    DisplayImage( "canny", result.canny );
    DisplayImage( "usm", result.usm );
    DisplayImage( "sobel_gx", result.sobelGx );
    DisplayImage( "sobel_gy", result.sobelGy );
    DisplayImage( "outline", result.outline );
    DisplayImage( "equaliseHist", result.equalizedHist );

    const cv::Mat comparisonWindow = CreateComparisonImage( result.src, result.gray, result.blur, result.canny, result.usm, 
                                                            result.outline, result.sobelGx, result.sobelGy, comparisonScale);

    DisplayImage( "comparison_window", comparisonWindow );
}