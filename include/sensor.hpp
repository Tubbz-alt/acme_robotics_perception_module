/**
 * @file    sensor.hpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Header filer for the generic class "Sensor". This is the base class
 * which the required modules can derive from. The class has generic virtual
 * methods getOutput and process. The methods should be overloaded by
 * the derived class.
 *
 */

#ifndef INCLUDE_SENSOR_HPP_
#define INCLUDE_SENSOR_HPP_
/**
 * @brief      Class for generic sensor. Particular sensor in the system will
 * inherit this base class.
 */
template <class T>

class Sensor {
 public:
  /**
   * @brief Function to get the output variables of the class
   * @return void: Return nothing
   */
  virtual auto getOutput() -> T = 0;
  /**
   * @brief Function to do the process of respective class
   * @return void: Return nothing
   */
  virtual auto process() -> void = 0;
  /**
   * @brief Function to check whether the sensor is running
   * @return bool: Return "true" if running, "false" otherwise
   */
  virtual auto isAlive() -> bool = 0;
};
#endif  // INCLUDE_SENSOR_HPP_
