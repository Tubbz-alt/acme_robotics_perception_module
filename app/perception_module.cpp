/**
 * @file    perception_module.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Function implementation for the class "PerceptionModule".
 *
 */

#include "perception_module.hpp"

PerceptionModule::PerceptionModule() {
  // TODO: Implement constructor
}

PerceptionModule::~PerceptionModule() {
  // TODO: Implement destructor if needed
}

auto PerceptionModule::isAlive() -> bool { return is_running_; }

auto PerceptionModule::detectCenter(cv::Mat raw_image) -> void {
  // TODO: Implement the method to detect the center
}

auto PerceptionModule::getCenter() -> std::pair<int, int> { return center_; }