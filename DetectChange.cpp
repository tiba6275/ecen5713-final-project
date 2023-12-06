#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <string>

void captureImage(const char* filename) {
    std::string command = "libcamera-still -o " + std::string(filename);
    system(command.c_str());
}

void compareImages(const char* in1, const char* in2, const std::string& out) {
    cv::Mat image1 = cv::imread(in1, cv::IMREAD_COLOR);
    cv::Mat image2 = cv::imread(in2, cv::IMREAD_COLOR);

    if (!image1.data || !image2.data) {
        std::cerr << "Error: Could not open or find the images\n";
        return;
    }

    if (image1.size() != image2.size()) {
        std::cerr << "Error: Images must be of the same size\n";
        return;
    }

    cv::Mat diffImage;
    cv::absdiff(image1, image2, diffImage);
    cv::imwrite(out, diffImage);
}

int main() {
    const char* inFile1 = "input1.jpg";
    const char* inFile2 = "input2.jpg";
    int outIdx = 0;

    captureImage(inFile1);

    while (true) {
        sleep(5);

        captureImage(inFile2);

        std::string outFile = "out" + std::to_string(outIdx) + ".jpg";

        std::thread comparisonThread(compareImages, inFile1, inFile2, outFile);
        comparisonThread.join();

        outIdx++;

        std::swap(inFile1, inFile2);
    }

    return 0;
}

