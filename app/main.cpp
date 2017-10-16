/**
 * @file    main.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * Dummy main file.
 *
 */

#include <utility>
#include "control_module.hpp"

int main() {
  // UltrasonicSensor sensor1;
  // sensor1.setMaxDistance(10.03);
  // std::cout << "Max distance:" << sensor1.getMaxDistance() << std::endl;
  // sensor1.process();
  // std::cout << "Current distance:" << sensor1.getOutput() << std::endl;
  // std::cout << "Is running?" << sensor1.isAlive() << std::endl;
  std::cout << " done" << std::endl;
  Camera cam;
  // cam.setDebugFlag(true);
  // std::cout<<"Camera running? "<< cam.testCamera()<<std::endl;
  cam.process();
  cv::Mat thresholdImg = cam.getOutput();

  // std::cout<< "cam initialization done"<<std::endl;
  PerceptionModule pm;
  // std::cout<< "PM initialization done"<<std::endl;
  // pm.detectContours(thresholdImg);
  // std::cout<< "PM contours done"<<std::endl;
  // pm.computeLinePts(thresholdImg);
  // std::cout<< "PM center done"<<std::endl;
  // std::pair<int, int> center = pm.getCenter();
  // std::cout << "The center of the lasrgest contour is: " << center.first <<
  // ", "
  //           << center.second << std::endl;

  ControlModule cm;
  cm.computeActionPt(pm.getPoints());
  std::cout << cm.getControlAction() << std::endl;
  return 0;
}
