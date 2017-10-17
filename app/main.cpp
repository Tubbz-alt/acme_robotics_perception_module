/**
 * @file    main.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * The file to run the perception module. The flags are defined such that it
 * will read the image in the "data" folder.
 *
 * To run the module use following commands:
 * $ ./app/perception_module ../data/caution_tape1.jpg
 *
 * While running the module make sure to give the path to the image.
 *
 */

#include <string>
#include <utility>
#include "control_module.hpp"

int main(int argc, char* argv[]) {
  std::cout << "[INFO] Starting the controller..."
            << std::endl;  // Starting the module

  if (argc == 2) {  // Check if the argument is provided
    std::string imgName(
        argv[1]);  // Create the string from the arguments in the argument
    cv::Mat img = cv::imread(imgName);  // Read the string

    PerceptionModule pm;  // Instantiate the PerceptionModule
    if (pm.isAlive()) {
      pm.computeLinePts(img);  // Compute the points on the detected line
    } else {
      std::cout << "[ERROR] Perception module is not running." << std::endl;
    }

    ControlModule cm;  // Instantiate the ControlModule
    if (cm.runDiagnostics()) {
      cm.computeActionPt(pm.getPoints());  // Compute the action
      std::cout << "[INFO] The computed control action is:" << std::endl
                << cm.getControlAction()
                << std::endl;  // Display the computed action
    } else {
      std::cout << "[ERROR] Please ensure all modules are running."
                << std::endl;
    }
  } else {
    std::cout << "[ERROR] Please provide path to image." << std::endl;
  }

  return 0;
}
