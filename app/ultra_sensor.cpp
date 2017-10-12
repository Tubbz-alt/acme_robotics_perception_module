/**
 * @file    ultrasonic_sensor.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Function implementation for the class "UltrasonicSensor".
 *
 */

#include "ultrasonic_sensor.hpp"

UltrasonicSensor::UltrasonicSensor() { is_running_ = true; }

UltrasonicSensor::UltrasonicSensor(float maxDist) {
  is_running_ = true;
  max_distance_ = maxDist;
}

UltrasonicSensor::~UltrasonicSensor() {}

auto UltrasonicSensor::process() -> void {
  // TODO: Implement process method
}

auto UltrasonicSensor::isAlive() -> bool { return is_running_; }

auto UltrasonicSensor::setMaxDistance(float maxDist) -> void {
  max_distance_ = maxDist;
}

auto UltrasonicSensor::getMaxDistance() -> float { return max_distance_; }

auto UltrasonicSensor::getOutput() -> float { return output_current_distance_; }