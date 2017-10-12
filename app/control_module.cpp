/**
 * @file    control_module.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Function implementation for the class "ControlModule".
 *
 */

#include "control_module.hpp"

ControlModule::ControlModule() {
  // TODO: Implement contructor
}

ControlModule::~ControlModule() {
  // TODO: Implement destructor if needed
}

auto ControlModule::isAlive() -> bool { return is_running_; }

auto ControlModule::computeAction(std::pair<int, int> center, float curr_dist)
    -> void {
  // TODO: Implmenet the method to compute the action
}

auto ControlModule::getControlAction() -> std::string {
  return control_action_;
}