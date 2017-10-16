/**
 * @file    control_module.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Implementation file for the class ControlModule. The class computes the
 * action based on the readings from camera and ultrasonic sensor.
 *
 */

#include "control_module.hpp"
#include <memory>
#include <string>
#include <utility>
#include <vector>

#define CONTROL_MODULE_USE_LINE_PTS

ControlModule::ControlModule() {
  is_running_ = true;  // Set the alive flag
  setPointers();       // Call the function to create pointers
}

ControlModule::~ControlModule() {}

auto ControlModule::setPointers() -> void {
  perception_module_ =
      std::make_unique<PerceptionModule>();  // Create a unique pointer to
                                             // PerceptionModule
  front_sensor_ =
      std::make_unique<UltrasonicSensor>();  // Create a unique pointer to
                                             // UltrasonicSensor
}

auto ControlModule::runDiagnostics() -> bool {
  if (perception_module_->isAlive() && is_running_ &&
      perception_module_
          ->cameraAlive()) {  // Check if all the modules are working
    return true;              // Return true if all are working
  } else {
    return false;  // Return false otherwise
  }
}

auto ControlModule::isAlive() -> bool {
  return is_running_;  // Return the alive flag
}

#ifndef CONTROL_MODULE_USE_LINE_PTS

auto ControlModule::computeActionCenter(const std::pair<int, int> &center)
    -> void {
  int centerY = center.first;   // Get the center value (x coordinate)
  int centerX = center.second;  // Get the center value (y coordinate)

  int rows = (perception_module_->getCameraImage())
                 .rows;  // Calculate the number of rows in the input image
  int cols = (perception_module_->getCameraImage())
                 .cols;  // Calculate the number of columns in the input image

  front_sensor_->process();  // Take the reading of ultrasonic sensor

  if (front_sensor_->getOutput() <
      front_sensor_
          ->getMaxDistance()) {  // Check if the sensor reading is valid or not
    if (centerX < (cols / 2)) {  // Check the if the located point is below the
                                 // center of the image
      control_action_ = "Go forward!";
    } else if (centerX > (cols / 2)) {  // Check the if the located point is
                                        // above the center of the image
      control_action_ = "Go back!";
    } else if (centerY < (rows / 2)) {  // Check the if the located point is on
                                        // the right of the center of the image
      control_action_ = "Go left!";
    } else if (centerY > (rows / 2)) {  // Check the if the located point is on
                                        // the left of the center of the image
      control_action_ = "Go right!";
    }
  } else {
    control_action_ = "Go back!";
  }
}

#else

auto ControlModule::computeActionPt(
    const std::vector<std::pair<int, int> > &linePts) -> void {
  front_sensor_->process();  // Take the reading of the ultrasonic sensor
  if (front_sensor_->getOutput() <
      front_sensor_
          ->getMaxDistance()) {  // Check if the sensor reading is valid or not
    auto pt1 = linePts[0];       // Initialize the first point
    auto pt2 = linePts[1];       // Initialize the second point
    float denom = pt2.first - pt1.first;  // Calculate the denominator for slope

    if (pt2.first - pt1.first == 0) {  // Check if the difference is 0
      denom = pow(10, -4);  // Set the 0 to a very low value in order to avoid
                            // division by 0 error
    }
    float slope =
        -(pt2.second - pt1.second) / denom;   // Calculate the slope of the line
    float theta = atan(slope) * 180 / CV_PI;  // Calculate the angle

    int rows = (perception_module_->getCameraImage())
                   .rows;  // Get the number of rows in the input image
    int cols = (perception_module_->getCameraImage())
                   .cols;  // Get the number of columns in the input image

    if (abs(pt1.second - pt2.second) < 10) {  // Check if the line is horizontal
      if (pt1.second < (rows / 2) &&
          pt2.second <
              (rows /
               2)) {  // Locate the points with respect to center of the image
        control_action_ = "Go back at angle: " + std::to_string(theta);
      } else if (pt1.second > (rows / 2) &&
                 pt2.second > (rows / 2)) {  // Locate the points with respect
                                             // to center of the image
        control_action_ = "Go forward at angle: " + std::to_string(theta);
      }
    } else if (abs(pt1.first - pt2.first) <
               10) {  // Check if the line is vertical or not
      if (pt1.first < (cols / 2) &&
          pt2.first < (cols / 2)) {  // Locate the points with respect to the
                                     // center of the image
        control_action_ =
            "Go right laterally at angle: " + std::to_string(theta);
      } else if (pt1.first > (cols / 2) &&
                 pt2.first > (cols / 2)) {  // Locate the points with respect to
                                            // the center of the image
        control_action_ =
            "Go left laterally at angle: " + std::to_string(theta);
      }
    }

  } else {
    control_action_ = "Go back.";
  }
}
#endif  // CONTROL_MODULE_USE_LINE_PTS

auto ControlModule::getControlAction() -> std::string {
  return control_action_;  // Return the calculated control action
}
