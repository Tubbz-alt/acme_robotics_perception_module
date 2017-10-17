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

#include <opencv2/imgcodecs.hpp>

#include <memory>
#include <utility>
#include <vector>

#include "camera.hpp"

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
   * @brief      Create a pointer to camera object
   *
   * @return     void: Return nothing
   */
  auto setCameraObj() -> void;
  /**
 * @brief      Determines if the module is running or not.
 *
 * @return     bool: Return "true" if the module is running, "false"
 * otherwise.
 */
  auto isAlive() -> bool;
  /**
   * @brief      Function to detect the contours in the incoming frame.
   *
   * @param[in]  raw_image: The image in which contours are to be found.
   *
   * @return     void: Return nothing.
   */
  auto detectContours(const cv::Mat &raw_image) -> void;
  /**
   * @brief      Method to get the center of the detected contours.
   *
   * @param[in]  raw_image: The image which is to be processed.
   *
   * @return     void: Return nothing.
   */
  auto detectCenter() -> void;
  /**
   * @brief      Finds the best fitting line using the Hough transforms and
   * returns the points on the line
   *
   * @return     void: Return nothing
   */
  auto computeLinePts() -> void;
  /**
   * @brief      Overload the function to read the specifc file. Find the best
   * fitting line using the Hough transforms and returns the points on the line
   *
   * @param[in]  file: The image to be read by the module.
   *
   * @return     void: Return nothing.
   */
  auto computeLinePts(const cv::Mat &img) -> void;
  /**
   * @brief      Function to return the points on the detected line.
   *
   * @return     std::vector<std::pair<int, int>>: Return vector of pair of the
   * points on the detected line.
   */
  auto getPoints() -> std::vector<std::pair<int, int>>;
  /**
   * @brief      Gets the location of the center of the contour.
   *
   * @return     std::pair<int>: Return the center of the contour.
   */
  auto getCenter() -> std::pair<int, int>;
  /**
   * @brief      Function to check if camera is running or not
   *
   * @return     bool: Return the value returned by Camera::isAlive
   */
  auto cameraAlive() -> bool;

 private:
  std::unique_ptr<Camera> camera_obj_;  ///< Object of the Camera sensor.
  std::vector<std::vector<cv::Point>> contours_;  ///< Vectors of contours.
  std::vector<cv::Vec4i> heirarchy_;              ///< Heirarchy of contours.
  std::pair<int, int> center_;
  cv::Mat contour_image_;       ///< Image containing detected contours.
  bool contour_detected_;       ///< Flag to indicated whether the contour is
                                /// detected or not.
  int largest_contour_id_;      ///< ID of the largest contour detected.
  float largest_contour_area_;  ///< Area of the largest contour detected.
  std::vector<cv::Point>
      largest_contour_;  ///< Largest contour detected in the image.
  bool is_running_;  ///< Flag to test if the perception module is running or
                     /// not.
  std::vector<cv::Vec4i> lines_;
  std::vector<std::pair<int, int>> points_;  ///< Vector of points of line.
  cv::Mat raw_image_;
};
#endif  //  INCLUDE_PERCEPTION_MODULE_HPP_
