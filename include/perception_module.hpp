/**
 * @file    perception_module.hpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Header file for the class "PerceptionModule". This class gets the
 * pre-processed image as an input and finds the contours in the image. It then
 * finds the center of the contours which is the output of the class. This
 * center is then passed on to the "Controller" module.
 *
 */

#ifndef INCLUDE_PERCEPTION_MODULE_HPP_
#define INCLUDE_PERCEPTION_MODULE_HPP_

#include "camera.hpp"

#include <utility>

/**
 * @brief      Class for perception module. This class finds the contours and
 * the center of the contours in the image provided as an input.
  */
class PerceptionModule {
 public:
  /**
   * @brief      Constructor of the class PerceptionModule.
   *
   * @return     void: Return nothing.
   */
  PerceptionModule();
  /**
   * @brief      Destroys the object of the class PerceptionModule.
   *
   * @return     void: Return nothing.
   */
  ~PerceptionModule();
  /**
 * @brief      Determines if the module is running or not.
 *
 * @return     bool: Return "true" if the module is running, "false"
 * otherwise.
 */
  auto isAlive() -> bool;
  /**
   * @brief      Method to get the center of the detected contours.
   *
   * @param[in]  raw_image: The image which is to be processed.
   *
   * @return     void: Return nothing.
   */
  auto detectCenter(cv::Mat raw_image) -> void;
  /**
   * @brief      Gets the location of the center of the contour.
   *
   * @return     std::pair<int>: Return the center of the contour.
   */
  auto getCenter() -> std::pair<int, int>;

 private:
  Camera camera_obj_;           ///< Object of the Camera sensor.
  std::pair<int, int> center_;  ///< Center of the detected contour.
  bool is_running_;  ///< Flag to test if the perception module is running or
                     /// not.
};
#endif  //  INCLUDE_PERCEPTION_MODULE_HPP_