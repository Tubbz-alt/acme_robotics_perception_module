/**
 * @file    camera.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Function implementation for the class "Camera".
 *
 */

#include "camera.hpp"

Camera::Camera() { is_running_ = true; }

Camera::~Camera() {
  // TODO: Implement destructor
}

auto Camera::process() -> void {
  // TODO: Implement process method
}

auto Camera::isAlive() -> bool { return is_running_; }

auto Camera::getVideoCapture() -> cv::VideoCapture { return vid_cap_; }

auto Camera::getOutput() -> cv::Mat { return output_processed_image_; }