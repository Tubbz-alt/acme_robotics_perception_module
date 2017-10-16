/**
 * @file    control_module.hpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Header file for the class "ControlModule". This class is the control module
 * which gets the readings from the Ultrasonic sensor as well as the center of
 * the contour from the camera module. It processes this information and decides
 * what action needs to be taken.
 *
 */

#ifndef INCLUDE_CONTROL_MODULE_HPP_
#define INCLUDE_CONTROL_MODULE_HPP_

#include <math.h>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "perception_module.hpp"
#include "ultrasonic_sensor.hpp"

/**
 * @brief      Class for control module. This class generates the actions based
 * on the inputs from ultrasonic sensor and camera
 */
class ControlModule {
 public:
  /**
   * @brief      Constructor of the class ControlModule
   * @return     void: Return nothing.
   */
  ControlModule();
  /**
   * @brief      Destroys the object of the class ControlModule
   */
  ~ControlModule();
  /**
   * @brief      Create the pointers to the perception and ultrasonic sensor
   *
   * @return     void: Return nothing
   */
  auto setPointers() -> void;
  /**
   * @brief      Determines if the module is running or not.
   *
   * @return     bool: Return "true" if the module is running, "false"
   * otherwise.
   */
  auto isAlive() -> bool;
  /**
   * @brief      Mehod to calculate the action based on the inputs.
   *
   * @param[in]  center:    Center of the detected contour.
   * @param[in]  curr_dist: Current distance reading.
   *
   * @return     void: Return nothing.
   */
  auto computeActionCenter(const std::pair<int, int> &center) -> void;
  /**
   * @brief      Compute the action to be taken from the detected points on the
   * line
   *
   * @param[in]  linePts: Vector of pair of points on the line
   *
   * @return     void: Return nothing
   */
  auto computeActionPt(const std::vector<std::pair<int, int>> &linePts) -> void;
  /**
   * @brief      Gets the computed control action.
   *
   * @return     string: Return the computed control action.
   */
  auto getControlAction() -> std::string;
  /**
   * @brief      Function to check if all the modules are running
   *
   * @return     bool: Return true if all modules are up, false otherwise
   */
  auto runDiagnostics() -> bool;

 private:
  std::unique_ptr<UltrasonicSensor> front_sensor_;  ///< Front distance sensor.
  std::unique_ptr<PerceptionModule>
      perception_module_;       ///< Camera sensor module.
  std::string control_action_;  ///< Computed control action.
  bool is_running_;  ///< Flag to test if the perception module is running or
                     /// not.
};
#endif  // INCLUDE_CONTROL_MODULE_HPP_
