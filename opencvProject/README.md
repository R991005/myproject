# OpenCV Image Processing Portfolio

## Overview
This project is a basic image processing pipeline implemented in C++ using OpenCV.

The application reads an input image and applies several processing steps such as grayscale conversion, median blur, Canny edge detection, unsharp masking (USM), Sobel filtering, histogram equalization, and contour extraction.

The processed results are displayed individually and also combined into a comparison image.

## Technologies
- C++
- OpendCV
- CMake
- Visual Studio / VS Code

## Features 
- Convert input image to grayscale
- Apply median blur
- Apply Canny edge detection
- Apply unsharp masking (USM)
- Apply Sobel filter in x and y directions
- Extract contours using `findContours`
- Apply histogram equalization
- Generate a comparison image

## Result
### Comparison Image
![comparison](comparison.png)

## Processing Time
Average processing time was measured over 100 runs.

| Process | Time (ms) |
|---|---:|
| ConvertToGray | 0.039384ms |
| ApplyMedianBlur | 2.18832ms |
| ApplyCanny | 0.060691ms |
| ApplyUSM | 2.66679ms |
| Contour extraction | 0.046373ms |
| Contour drawing | 0.030404ms |


## Highlights
- Implemented USM manually using blur and image difference
- Measured average processing time over multiple runs
- Compared multiple image processing results in one combined output image
- Separated code into header and source files for readability

## How to Run
1. Build the project with CMake
2. Place the input image in the project directory
3. Run the executable
4. Check the displayed processing results and comparison image

## Future Improvements
- Add Gaussian blur comparison
- Compare different kernel sizes systematically
- Apply the pipeline to public medical or dental image datasets
- Improve contour filtering by removing small noisy regions