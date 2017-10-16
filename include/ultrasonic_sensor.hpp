/**
 * @file    ultrasonic_sensor.hpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Header file for the class "UltrasonicSensor". This class is derived from the
 * base class "Sensor". It has private members as max_distance_, is_running_ and
 * output_current_distance_. The getOutput method returns the current distance
 * reading while process method updates the current distance reading.
 *
 */

#ifndef INCLUDE_ULTRASONIC_SENSOR_HPP_
#define INCLUDE_ULTRASONIC_SENSOR_HPP_

#include <stdlib.h>
#include <ctime>
#include <iostream>

#include "sensor.hpp"

class UltrasonicSensor : public Sensor<float> {
 public:
  /**
   * @brief Constructor of the class UltrasonicSensor. Set the is_running_ flag
   * to true.
   *
   * @return void: Return nothing.
   */
  UltrasonicSensor();
  /**
   * @brief Destructor of the class UltrasonicSensor
   *
   * @return void: Return nothing.
   */
  ~UltrasonicSensor();
  /**
   * @brief      Method to set constant seed if needed
   *
   * @param[in]  seed: Constant value to be set as seed
   *
   * @return     void: Return nothing
   */
  auto setSeed(const int &seed) -> void;
  /**
   * @brief Override the virtual method "process" of Sensor class. This method
   * takes the current distance reading and updates its reading value.
   *
   * @return void: Return nothing
   */
  auto process() -> void;
  /**
   * @brief Override the virtual method "isAlive" of Sensor class. This method
   * checks if the sensor is running or not.
   *
   * @return bool: Return "true" if the sensor is running, "false" otherwise.
   */
  auto isAlive() -> bool;
  /**
   * @brief Method to set the max distance parameter of the class.
   *
   * @param maxDist: Pass the value which is set to be as maximum distance
   *
   * @return void: Return nothing.
   */
  auto setMaxDistance(float maxDist) -> void;
  /**
   * @brief Method to get the max distance parameter of the class.
   *
   * @return float: Return the maximum distance that can be read by the
   * sensor(max_distance_).
   */
  auto getMaxDistance() -> float;
  /**
   * @brief Override the method "getOutput" of Sensor class. This method returns
   * the output value of the class which is the current distance reading taken
   * by the sensor.
   *
   * @return float: Return the current distance read by the
   * sensor(output_current_distance_).
   */
  auto getOutput() -> float;

 private:
  float max_distance_;  ///< Maximum distance that can be read by the sensor.
  float output_current_distance_;  ///< Current distance reading. Output of the
                                   /// class.
  bool is_running_;  ///< Flag to test if the ultrasonic sensor is running or
                     /// not.
  unsigned int seed_;
};

#endif  // INCLUDE_ULTRASONIC_SENSOR_HPP_
