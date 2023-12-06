#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Usage: ./DetectChange <image1> <image2> <output_image>\n");
        return -1;
    }

    //Image input
    cv::Mat image1 = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread(argv[2], cv::IMREAD_COLOR);

    //Check input data
    if (!image1.data || !image2.data) {
        printf("Error: Could not open or find the images\n");
        return -1;
    }

    //Check size
    if (image1.size() != image2.size()) {
        printf("Error: Images must be of the same size\n");
        return -1;
    }

    //Matrix to hold result
    cv::Mat diffImage;

    //Calculating difference
    cv::absdiff(image1, image2, diffImage);

    cv::imwrite(argv[3], diffImage);

    return 0;
}
