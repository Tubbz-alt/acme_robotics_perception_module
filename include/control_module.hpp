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

#include "perception_module.hpp"
#include "ultrasonic_sensor.hpp"

#include <string>

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
  auto computeAction(std::pair<int, int> center, float curr_dist) -> void;
  /**
   * @brief      Gets the computed control action.
   *
   * @return     string: Return the computed control action.
   */
  auto getControlAction() -> std::string;

 private:
  UltrasonicSensor front_sensor_;       ///< Front distance sensor.
  PerceptionModule perception_module_;  ///< Camera sensor module.
  std::string control_action_;          ///< Computed control action.
  bool is_running_;  ///< Flag to test if the perception module is running or
                     ///not.
};
#endif  // INCLUDE_CONTROL_MODULE_HPP_