/**
 * @file    test_perception_module.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Testing file for the PerceptionModule class.
 */

#include <gtest/gtest.h>

#include "perception_module.hpp"
/**
 * @brief      Class to test the working of PerceptionModule
 */
class TestPerceptionModule : public ::testing::Test {
 protected:
  PerceptionModule pm;  // Create an instance of PerceptionModule class
};

TEST_F(TestPerceptionModule, dummyTest) {
  EXPECT_EQ(1, 1);  // Dummy test to check the working of tests
}

TEST_F(TestPerceptionModule, isAlive) {
  // Test to check whether PerceptionModule is working or not
  EXPECT_EQ(pm.isAlive(), true);
}
