/**
 * @file    test_control_module.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Testing file for the ControlModule class.
 */

#include <gtest/gtest.h>

#include "control_module.hpp"
#include "perception_module.hpp"
/**
 * @brief      Class for testing the ControlModule of the code. Create instances
 * of perception and control modules which can be used later for testing.
 */
class TestControlModule : public ::testing::Test {
 protected:
  ControlModule cm;     // Create instance of ControlModule class
  PerceptionModule pm;  // Create instance of PerceptionModule class
};
/**
 * @brief      Dummy test to check the working of tests
 */
TEST_F(TestControlModule, dummyTest) {
  EXPECT_EQ(1, 1);  // Dummy test to check working of the file
}
/**
 * @brief      Test to check the working of control module
 */
TEST_F(TestControlModule, isAlive) {
  // Test to check whether control module is running or not
  EXPECT_EQ(cm.isAlive(), true);
}
/**
 * @brief      Test to run diagnostic tests for all modules
 */
TEST_F(TestControlModule, diagnosticTest) {
  // Test to check if all modules are working
  EXPECT_EQ(cm.runDiagnostics(), true);
}
/**
 * @brief      Test to check the working of the control module.
 */
TEST_F(TestControlModule, processWorking1) {
  cv::Mat img = cv::imread("../data/test_caution_tape1.png");
  pm.computeLinePts(
      img);  // Detect the line in the input image and compute points
             // on it
  cm.computeActionPt(
      pm.getPoints());  // Pass the detected points to compute control action
  // Expected output for the test image
  EXPECT_EQ(cm.getControlAction(), "Go left laterally at angle: 89.999992");
}

TEST_F(TestControlModule, processWorking2) {
  cv::Mat img = cv::imread("../data/test_caution_tape2.png");
  pm.computeLinePts(
      img);  // Detect the line in the input image and compute points
             // on it
  cm.computeActionPt(
      pm.getPoints());  // Pass the detected points to compute control action
  // Expected output for the test image
  EXPECT_EQ(cm.getControlAction(), "Go forward at angle: 0.000000");
}

TEST_F(TestControlModule, processWorking3) {
  cv::Mat img = cv::imread("../data/test_caution_tape3.png");
  pm.computeLinePts(
      img);  // Detect the line in the input image and compute points
             // on it
  cm.computeActionPt(
      pm.getPoints());  // Pass the detected points to compute control action
  // Expected output for the test image
  EXPECT_EQ(cm.getControlAction(), "Go right laterally at angle: 89.999992");
}

TEST_F(TestControlModule, processWorking4) {
  cv::Mat img = cv::imread("../data/test_caution_tape4.png");
  pm.computeLinePts(
      img);  // Detect the line in the input image and compute points
             // on it
  cm.computeActionPt(
      pm.getPoints());  // Pass the detected points to compute control action
  // Expected output for the test image
  EXPECT_EQ(cm.getControlAction(), "Go back at angle: 0.000000");
}