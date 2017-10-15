/**
 * @file    test_ultrasonic_sensor.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Testing file for the UltrasonicSensor.
 */

#include <gtest/gtest.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>

#include "ultrasonic_sensor.hpp"
/**
 * @brief      Class to test the working of Ultrasonic sensor
 */
class TestUltrasonicSensor : public ::testing::Test {
 protected:
  UltrasonicSensor sensor;  // Create an instance of Ultrasonic sensor
};

TEST_F(TestUltrasonicSensor, dummyTest) {
  EXPECT_EQ(1, 1);  // Dummy test to check the working of tests
}

TEST_F(TestUltrasonicSensor, isAlive) {
  // Test to check whether ultrasonic sensor is working or not
  EXPECT_EQ(sensor.isAlive(), true);
}

TEST_F(TestUltrasonicSensor, setMaxDistance) {
  sensor.setMaxDistance(10.03);  // Set the max distance using the method
  // Test to check if setter and getter methods work correctly
  EXPECT_NEAR(sensor.getMaxDistance(), 10.03, 0.0001);
}

TEST_F(TestUltrasonicSensor, sensorReading) {
  sensor.setSeed(0);  // Set the seed to a constant value
  sensor.process();   // Take the reading of the sensor
  // Test the closeness of the two readings
  EXPECT_NEAR(sensor.getOutput(), 5.000471475, 0.00001);
}
