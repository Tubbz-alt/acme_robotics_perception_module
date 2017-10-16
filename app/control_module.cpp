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

ControlModule::ControlModule() {
  is_running_ = true;  // Set the alive flag
}

ControlModule::~ControlModule() {}

auto ControlModule::setPointers() -> void {
}

auto ControlModule::runDiagnostics() -> bool {
}

auto ControlModule::isAlive() -> bool {
  return is_running_;  // Return the alive flag
}

auto ControlModule::computeActionCenter(const std::pair<int, int> &center)
    -> void {
}

auto ControlModule::computeActionPt(
    const std::vector<std::pair<int, int> > &linePts) -> void {
}

auto ControlModule::getControlAction() -> std::string {
  return control_action_;  // Return the calculated control action
}
