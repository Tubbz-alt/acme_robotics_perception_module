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
 * @brief      Class for testing the ControlModule of the code
 */
class TestControlModule : public ::testing::Test {
 protected:
  ControlModule cm;     // Create instance of ControlModule class
  PerceptionModule pm;  // Create instance of PerceptionModule class
};

TEST_F(TestControlModule, dummyTest) {
  EXPECT_EQ(1, 1);  // Dummy test to check working of the file
}

TEST_F(TestControlModule, isAlive) {
  // Test to check whether control module is running or not
  EXPECT_EQ(cm.isAlive(), true);
}

TEST_F(TestControlModule, diagnosticTest) {
  // Test to check if all modules are working
  EXPECT_EQ(cm.runDiagnostics(), true);
}

TEST_F(TestControlModule, processWorking) {
  pm.computeLinePts();  // Detect the line in the input image and compute points
                        // on it
  cm.computeActionPt(
      pm.getPoints());  // Pass the detected points to compute control action
  // Expected output for the test image
  EXPECT_EQ(cm.getControlAction(), "Go left laterally at angle: 89.999985");
}
