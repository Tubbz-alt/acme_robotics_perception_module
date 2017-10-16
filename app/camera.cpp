/**
 * @file    camera.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Class implementation for the class Camera. Uncomment the DEBUG_CAMERA if you
 * want to debug the code.
 *
 */

#include "camera.hpp"

#define DEBUG_CAMERA

Camera::Camera() {
  is_running_ = true;  // Set the flag to true
  vid_cap_ =
      cv::VideoCapture(0);  // Change the value to 1 if using secondary camera
}

Camera::~Camera() {}

#ifndef DEBUG_CAMERA

auto Camera::testCamera() -> bool {
  if (is_running_) {
    cv::Mat img;
    vid_cap_ >> img;
    if (img.empty()) {  // Check if the image is read or not
      std::cout << "[ERROR] Image data is empty." << std::endl;  // Raise error
      std::cout << "[INFO] Setting default video." << std::endl;
      return false;       // Return false since camera is not functioning
      setDefaultVideo();  // Set the path to default video
    } else {
      return true;  // Return true since camera is running
    }
  } else {
    std::cout << "[ERROR] Camera not running."
              << std::endl;  // Raise error since camera is not up
    return false;            // Return false since camera is not functioning
  }
}

#endif  // DEBUG_CAMERA

auto Camera::setDefaultVideo() -> bool {
  vid_cap_ = cv::VideoCapture(
      "../data/video1.avi");  // Initialize the video object to default video
  return true;
}

auto Camera::process() -> void {
  cv::Mat inputImg, thresholdImg1, thresholdImg2,
      combinedImg;  // Create local variables

#ifdef DEBUG_CAMERA

  std::cout << "[DEBUG] Debugging camera sensor." << std::endl;
  inputImg =
      cv::imread("../data/caution_tape_vertical.jpg");  // Read debug image
  cv::inRange(inputImg, cv::Scalar(22, 22, 0), cv::Scalar(38, 255, 255),
              thresholdImg1);  // Thresholding the image for Yellow
  cv::inRange(inputImg, cv::Scalar(0, 0, 0), cv::Scalar(179, 255, 30),
              thresholdImg2);  // Thresholding the image for Black

  cv::addWeighted(thresholdImg1, 0.5, thresholdImg2, 0.5, 0.0,
                  combinedImg);  // Weighted sum of two thresholded images
  cv::dilate(combinedImg, combinedImg,
             cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7),
                                       cv::Point()));  // Morphological dilation
                                                       // using ellipse as a
                                                       // structuring element
  cv::erode(combinedImg, output_processed_image_,
            cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5),
                                      cv::Point()));  // Morphological erosion
                                                      // using ellipse as a
                                                      // structuring element

  cv::imshow("Debug image",
             output_processed_image_);  // Display the debug image

  cv::waitKey(3000);  // Wiat for 3 seconds before closing the window
// cv::imwrite("../data/expectedImg.jpg", output_processed_image_);
#else

  vid_cap_ >> inputImg;  // Read the frame

  cv::inRange(inputImg, cv::Scalar(22, 22, 0), cv::Scalar(38, 255, 255),
              thresholdImg1);  // Thresholding the image for Yellow
  cv::inRange(inputImg, cv::Scalar(0, 0, 0), cv::Scalar(179, 255, 30),
              thresholdImg2);  // Thresholing the image for Black

  cv::addWeighted(
      thresholdImg1, 0.5, thresholdImg2, 0.5, 0.0,
      output_processed_image_);  // Weighted sum of the thresholded images

  cv::dilate(combinedImg, combinedImg,
             cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(7, 7),
                                       cv::Point()));  // Morphological dilation
                                                       // using ellipse as a
                                                       // structuring element
  cv::erode(combinedImg, output_processed_image_,
            cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5),
                                      cv::Point()));  // Morphological erosion
                                                      // using ellipse as a
                                                      // structuring element
#endif
}

auto Camera::isAlive() -> bool {
  return is_running_;  // Return the alive flag
}

auto Camera::getOutput() -> cv::Mat {
  return output_processed_image_;  // Return the processed image
}
