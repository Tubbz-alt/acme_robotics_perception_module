/**
 * @file    main.cpp
 * @author  nrparikh
 * @copyright MIT license
 *
 * @brief DESCRIPTION
 * The file to run the perception module. The flags are defined such that it
 * will read the image in the "data" folder.
 *
 */

#include <utility>
#include "control_module.hpp"

int main() {
  std::cout << "[INFO] Starting the controller..."
            << std::endl;  // Starting the module

  PerceptionModule pm;  // Instantiate the PerceptionModule
  if (pm.isAlive()) {
    pm.computeLinePts();  // Compute the points on the detected line
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
    std::cout << "[ERROR] Please ensure all modules are running." << std::endl;
  }

  return 0;
}
