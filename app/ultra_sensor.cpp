/**
 * @file    ultrasonic_sensor.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Class implementation for the class UltrasonicSensor. Simulate the sensor
 * readings by generating pseudo random numbers
 *
 */

#include <limits>
#include "ultrasonic_sensor.hpp"

UltrasonicSensor::UltrasonicSensor() {
  is_running_ = true;    // Set the alive flag
  seed_ = time(0);       // Set the seed for pseudo random number generator
  max_distance_ = 10.0;  // Set the max distance
  output_current_distance_ =
      max_distance_ + 10.0;  // Initialize the current distance reading
}

UltrasonicSensor::~UltrasonicSensor() {}

auto UltrasonicSensor::setSeed(const int &seed) -> void {
  seed_ = seed;  // Set constant seed if needed
}

auto UltrasonicSensor::process() -> void {
  float randReading = static_cast<float>(rand_r(&seed_)) /
                      RAND_MAX;  // Generate a pseudo random number

  if (randReading > 0.00001 &&
      randReading < 0.99) {  // Check if it is a valid reading
    output_current_distance_ = 5 + randReading;  // Set the current reading
  } else {
    output_current_distance_ =
        max_distance_ +
        10.0;  // If reading is greater than max distance  set it to invalid
  }
}

auto UltrasonicSensor::isAlive() -> bool {
  return is_running_;  // Return the alive flag
}

auto UltrasonicSensor::setMaxDistance(float maxDist) -> void {
  max_distance_ = maxDist;  // Set the max distance
}

auto UltrasonicSensor::getMaxDistance() -> float {
  return max_distance_;  // Return the max distance
}

auto UltrasonicSensor::getOutput() -> float {
  return output_current_distance_;  // Return the pre-processed image
}
