/**
 * @file    perception_module.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Implementation file for the class PerceptionModule. Uncomment the
 * DEBUG_PERCEPTION_MODULE to debug the module.
 *
 */

#include "perception_module.hpp"
#include <math.h>
#include <memory>
#include <utility>
#include <vector>

#define PERCEPTION_MODULE_DEBUG
#define PERCEPTION_MODULE_USE_LINE_PTS

PerceptionModule::PerceptionModule() {
  is_running_ = true;           // Set the alive flag
  contour_detected_ = false;    // Set the contour detected flag
  largest_contour_area_ = 0.0;  // Initialize the largest area
  largest_contour_id_ = 0;      // Initialize the ID
  setCameraObj();
}

PerceptionModule::~PerceptionModule() {}

auto PerceptionModule::setCameraObj() -> void {
  camera_obj_ =
      std::make_unique<Camera>();  // Create an unique pointer to Camera object
}

auto PerceptionModule::isAlive() -> bool {
  return is_running_;  // Return the alive flag
}

#ifndef PERCEPTION_MODULE_USE_LINE_PTS

auto PerceptionModule::detectContours(const cv::Mat &raw_image) -> void {
  cv::findContours(raw_image, contours_, heirarchy_, cv::RETR_TREE,
                   cv::CHAIN_APPROX_SIMPLE,
                   cv::Point(0, 0));  // Find the contours in the input image

  contour_image_ =
      cv::Mat::zeros(raw_image.size(), CV_8UC3);  // Initialize the image

  if (!contours_.empty()) {  // Check if the contours are detected
    float prevArea = 0.0;    // Initialize previous area variable
    float currArea = 0.0;    // Initialize current area variable

    int num = 0;                // Initiailize the counter
    for (auto i : contours_) {  // Iterate over all contours
      cv::approxPolyDP(cv::Mat(i), i, cv::arcLength(cv::Mat(i), true) * 0.001,
                       true);  // Find the convex points

      currArea = cv::contourArea(i);  // Set the current area

      if (currArea > prevArea) {  // Check if the current area is greater than
                                  // previous area
        largest_contour_area_ =
            currArea;               // Set the largest area to current contour
        largest_contour_id_ = num;  // Set the ID to current value of counter
        prevArea = currArea;        // Set previous area to current area
      }
      contour_detected_ = true;  // Set contour detected flag to true
      num++;                     // Increment the counter
    }
  } else {
    contour_detected_ = false;  // Set contour detected flag to false
  }

#ifdef DEBUG_PERCEPTION_MODULE

  std::cout << "Contour ID: " << largest_contour_id_
            << std::endl;  // Display the largest contour ID
  std::cout << "Contour Area: " << largest_contour_area_
            << std::endl;  // Display the largest contour area
  cv::drawContours(contour_image_, contours_, largest_contour_id_,
                   (255, 255, 255), 2, 5, heirarchy_, 0,
                   cv::Point());              // Draw the largest contour
  cv::imshow("Debug Image", contour_image_);  // Show the image for debugging
  cv::waitKey(3000);                          // Wait for 3 seconds

#endif  // PERCEPTION_MODULE_DEBUG
}

auto PerceptionModule::detectCenter() -> void {
  largest_contour_ = contours_[largest_contour_id_];  // Set the largest contour
  cv::Moments m =
      cv::moments(largest_contour_, true);  // Find moments of the contour
  int centerX = m.m10 / m.m00;              // Find X coordinate of the center
  int centerY = m.m01 / m.m00;              // Find Y coordinate of the center
  center_ =
      std::make_pair(centerX, centerY);  // Create a pair of the center points
}

auto PerceptionModule::getCenter() -> std::pair<int, int> {
  return center_;  // Return the center
}

#else

auto PerceptionModule::computeLinePts() -> void {
  camera_obj_->process();
  cv::Mat raw_image = camera_obj_->getOutput();
  cv::Mat linesImg =
      cv::Mat::zeros(raw_image.size(), CV_8UC3);  // Initialize a local image
  cv::HoughLinesP(
      raw_image, lines_, 1, CV_PI / 180,
      200);  // Use Hough transform to find the lines in the input image
  cv::Vec4i l = lines_[0];  // Get tje highest voted line
  points_.push_back(std::make_pair(
      l[0], l[1]));  // Create a vector of the points on the detected line
  points_.push_back(std::make_pair(
      l[2], l[3]));  // Create a vector of the points on the detected line

#ifdef DEBUG_PERCEPTION_MODULE

  std::cout << "Length of lines_: " << lines_.size()
            << std::endl;  // Display the number of lines detected
  std::cout << "Point 1: " << l[0] << "," << l[1]
            << std::endl;  // Display the first point on the line
  std::cout << "Point 2: " << l[2] << "," << l[3]
            << std::endl;  // Display the second point on the line
  cv::line(linesImg, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
           cv::Scalar(0, 0, 255), 3, cv::LINE_AA);  // Draw the detected line

  cv::imshow("Detected Line", linesImg);  // Show the image
  cv::waitKey(3000);                      // Wait for 3 seconds before closing the window

#endif  // PERCEPTION_MODULE_DEBUG
}

#endif  // PERCEPTION_MODULE_USE_LINE_PTS

auto PerceptionModule::getCameraImage() -> cv::Mat {
  cv::Mat retImg =
      camera_obj_
          ->getOutput();  // Get the processed output image from camera object
  return retImg;          // Return the image
}

auto PerceptionModule::getPoints() -> std::vector<std::pair<int, int>> {
  auto copyPoints = points_;  // Copy the points in the local variable
  points_.clear();            // Reset the vector
  return copyPoints;          // Return the points
}

auto PerceptionModule::cameraAlive() -> bool {
  return camera_obj_->isAlive();  // Return whether the camera is running or not
}
