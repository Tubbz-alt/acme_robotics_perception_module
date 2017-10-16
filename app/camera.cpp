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

Camera::Camera() {
  is_running_ = true;  // Set the flag to true
}

Camera::~Camera() {}

auto Camera::testCamera() -> bool {
}

auto Camera::setDefaultVideo() -> bool {
}

auto Camera::process() -> void {
}

auto Camera::isAlive() -> bool {
  return is_running_;  // Return the alive flag
}

auto Camera::getOutput() -> cv::Mat {
  return output_processed_image_;  // Return the processed image
}
