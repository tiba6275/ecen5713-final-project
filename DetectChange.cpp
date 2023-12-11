#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <string>
#include <gst/gst.h>

void captureImage(const char* filename) {
    std::string command = "libcamera-jpeg -n -o " + std::string(filename) + " --width 1640 --height 1232";
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

    cv::Mat diffImage, hsvImage;
    cv::absdiff(image1, image2, diffImage);
    cv::cvtColor(diffImage, hsvImage, cv::COLOR_BGR2HSV);
    
    std::vector<cv::Mat> hsvChannels(3);
    cv::split(hsvImage, hsvChannels);
    cv::Mat mask, thresholdedImage;
    cv::threshold(hsvChannels[2], mask, 50, 255, cv::THRESH_BINARY);
    
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    cv::morphologyEx(mask, thresholdedImage, cv::MORPH_CLOSE, kernel);
    
    cv::Mat colorDiff = cv::Mat::zeros(image2.size(), image2.type());
    image2.copyTo(colorDiff, thresholdedImage);

    cv::imwrite(out, colorDiff);
}

int main(int argc, char *argv[]) {
    const char* inFile1 = "in1.jpg";
    const char* inFile2 = "in2.jpg";
    int outIdx = 0;

    gst_init(&argc, &argv);

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " SERVER_IP PORT" << std::endl;
        return 1;
    }

    std::string serverIp = argv[1];
    std::string port = argv[2];

    captureImage(inFile1);

    while (true) {
        captureImage(inFile2);

        std::string outFile = "out" + std::to_string(outIdx) + ".jpg";

        std::thread comparisonThread(compareImages, inFile1, inFile2, outFile);
        comparisonThread.join();

        std::string pipelineStr = "filesrc location=" + outFile + " ! tcpclientsink host=" + serverIp + " port=" + port;
        GstElement *pipeline = gst_parse_launch(pipelineStr.c_str(), NULL);
        gst_element_set_state(pipeline, GST_STATE_PLAYING);

        GstBus *bus = gst_element_get_bus(pipeline);
        GstMessage *msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

        if (msg != NULL)
            gst_message_unref(msg);
        gst_object_unref(bus);
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);

        outIdx++;

        //std::swap(inFile1, inFile2);
    }

    return 0;
}

