/**
 * @file    camera.hpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Header file for the class "Camera". This class is derived from the
 * base class "Sensor". The private members of the class include vid_cap_,
 * is_running_, and output_processed_image_. The getOutput method returns the
 * processed image while the process method processes the image suitable for
 * finding the center of the contours.
 *
 */
#ifndef INCLUDE_CAMERA_HPP_
#define INCLUDE_CAMERA_HPP_

#include "sensor.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

/**
 * @brief      Class for camera sensor. This class is derived from the base
 * Class Sensor.
 */
// template <class T>
class Camera : public Sensor <cv::Mat>{
 public:
  /**
   * @brief      Constructor of the class Camera. Set is_running_ flag to true.
   *
   * @return     void: Return nothing
   */
  Camera();
  /**
   * @brief      Destroys the object of the class. Set is_running_ to false.
   *
   * @return     void: Return nothing.
   */
  ~Camera();
  /**
   * @brief      Override the virtual method "process" of Sensor class. This
   * class processes the image so that Perception module can use it to determine
   * the location of boundary.
   *
   * @return     void: Return nothing.
   */
  auto process() -> void;
  /**
   * @brief      Override the virtual method "isAlive" of Sensor class. This
   * method checks if the sensor is running or not.
   *
   * @return     bool: Return "true" if the sensor is running, "false" otherwise
   * otherwise.
   */
  auto isAlive() -> bool;
  /**
   * @brief      Gets the video capture object private to the class.
   *
   * @return     cv::VideoCapture: Return the video capture object(vid_cap_).
   */
  auto getVideoCapture() -> cv::VideoCapture;
  /**
   * @brief      Override the method "getOutput" of Sensor class. This method
   * returns the pre-processed image suitable for further processing.
   *
   * @return     cv::Mat: Return processed image(output_processed_image_).
   */
  auto getOutput() -> cv::Mat;

 private:
  cv::VideoCapture vid_cap_;        ///< Video capture object of OpenCV
  cv::Mat output_processed_image_;  ///< Process image which is the output of
                                    /// the class
  bool is_running_;  ///< Flag to test if the camera sensor is running or not
};

#endif  // INCLUDE_CAMERA_HPP_
