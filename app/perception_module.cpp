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

PerceptionModule::PerceptionModule() {
  is_running_ = true;           // Set the alive flag
  contour_detected_ = false;    // Set the contour detected flag
  largest_contour_area_ = 0.0;  // Initialize the largest area
  largest_contour_id_ = 0;      // Initialize the ID
}

PerceptionModule::~PerceptionModule() {}

auto PerceptionModule::setCameraObj() -> void {
}

auto PerceptionModule::isAlive() -> bool {
  return is_running_;  // Return the alive flag
}

auto PerceptionModule::detectContours(const cv::Mat &raw_image) -> void {
}

auto PerceptionModule::detectCenter() -> void {
}

auto PerceptionModule::computeLinePts() -> void {
}


auto PerceptionModule::getCameraImage() -> cv::Mat {
}

auto PerceptionModule::getPoints() -> std::vector<std::pair<int, int>> {
}

auto PerceptionModule::cameraAlive() -> bool {
}
