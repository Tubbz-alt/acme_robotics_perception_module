/**
 * @file    test_camera.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Testing file for the Camera class.
 */

#include <gtest/gtest.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "camera.hpp"
/**
 * @brief      Class for the testing of Camera class. Creates a protected camera
 * object which can be used for testing.
 */
class TestCamera : public ::testing::Test {
 protected:
  Camera cam;  // Create an instance of camera sensor
};

/**
 * @brief      Dummy test function to check the working of tests
 */
TEST_F(TestCamera, dummyTest) {
  EXPECT_EQ(1, 1);  // Dummy test to check the working of test
}
/**
 * @brief      Test to check the working of camera module
 */
TEST_F(TestCamera, isAlive) {
  // Test to check whether camera is running or not
  EXPECT_EQ(cam.isAlive(), true);
}
/**
 * @brief      Test to check default video setup method
 */
TEST_F(TestCamera, defaultVideoSetup) {
  // Test to check if setDefaultVideo method works or not
  EXPECT_EQ(cam.setDefaultVideo(), true);
}
