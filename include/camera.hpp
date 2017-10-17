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

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <string>

#include "sensor.hpp"

#define DEBUG_CAMERA

/**
 * @brief      Class for camera sensor. This class is derived from the base
 * Class Sensor.
 */
class Camera : public Sensor<cv::Mat> {
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
   * @brief      Sets the default VideoCapture object. Call this function if
   * camera is not working.
   *
   * @return     bool: Return true after setting the default video.
   */
  auto setDefaultVideo() -> bool;
  /**
   * @brief      Function to test the working of camera. If the camera is not
   * working it will set the vid_cap_ object to read default video
   *
   * @return     bool: Return true if camera is working, false otherwise.
   */
  auto testCamera() -> bool;
  /**
   * @brief      Override the virtual method "process" of Sensor class. This
   * class processes the image so that Perception module can use it to determine
   * the location of boundary.
   *
   * @return     void: Return nothing.
   */
  auto process() -> void;
  /**
   * @brief      Override the virtual method "process" of Sensor class. This
   * class processes the image so that Perception module can use it to determine
   * the location of boundary. This is an overloaded function which will take an
   * input image and process it.
   *
   * @param[in]  file: Filename of the image which is to be read.
   *
   * @return     void: Return nothing.
   */
  auto process(const cv::Mat &img) -> void;
  /**
   * @brief      Override the virtual method "isAlive" of Sensor class. This
   * method checks if the sensor is running or not.
   *
   * @return     bool: Return "true" if the sensor is running, "false" otherwise
   * otherwise.
   */
  auto isAlive() -> bool;

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
  // stf::string
  //     file_name_;  ///< Filename which needs to be read from the "data" folder
};

#endif  // INCLUDE_CAMERA_HPP_
