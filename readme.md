# Perception Module for Unmanned Aerial Vehicle 
[![Build Status](https://travis-ci.org/nr-parikh/acme_robotics_perception_module.svg?branch=master)](https://travis-ci.org/nr-parikh/acme_robotics_perception_module)
[![Coverage Status](https://coveralls.io/repos/github/nr-parikh/acme_robotics_perception_module/badge.svg?branch=master)](https://coveralls.io/github/nr-parikh/acme_robotics_perception_module?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/LICENSE)

## Overview

This is a naive perception module for the Unmanned Aerial Vehicle by Acme Robotics. The new robot being developed by Acme robotics has a downward facing camera and a front facing ultrasonic sensor. The task of the robot is to detect the boundary lines which might be there on the ground and head in the direction opposite to that of the boundary lines. It should simultaneously also monitor the incoming reading from the ultrasonic sensor and avoid obstacles if any. The developed perception module has the capability of combining the information from different sensors and decide the heading direction. The details about the module are discussed in detail here.

## Dependencies 
To build and run the module successfully, following dependencies should be met:
* CMake version at least 3.2.1
* OpenCV 3.2 or higher: To download and build the library, please follow the instructions given [here](https://www.learnopencv.com/install-opencv3-on-ubuntu/) or if you have ROS kinetic installed on the system, this dependenct is met and no extra steps need to be followed.
* For unit testing this project depends on *gtest* framework by Google.

## Instructions to build the module
Before building the module, please ensure that the dependencies are met. Please follow the instructions given below to build the module.

```
$ git clone https://github.com/nr-parikh/acme_robotics_perception_module.git
$ cd <path to repository>
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Instructions to run the module and tests
Once the module is built correctly, to run the executable type the following command:
```
$ cd <build folder of the module>
$ ./app/perception_module <path to image/filename of the image>
```

To run the unit tests, please execute the command given below:
```
$ cd <build folder of the module>
$ ./test/cpp-test
```

## Solo Iterative Process
While developing this module SIP process was followed. The link to the SIP sheet for this module is [here](https://docs.google.com/spreadsheets/d/1xeEtkg9tZwtrnPBAMPW0ByWKBNMoUEidjYDhUrIFllk/edit?usp=sharing). Please note that the legend for the code tags is mentioned in the sheet itself. 

The spreadsheet contains *product backlog* which gives overview of how the project was executed. The second spreadsheet is  *Task backlog* which gives details of how each of the task were executed and the time consumed. The thirs spreadsheet is *Release backlog* which shows the improvements in the estimation of the time required to complete certain task as the module is developed.

## Sensors 
This module relies on the information incoming from two different sensors. The sensors which it uses are: 

* RGB camera
* Ultrasonic Sensor

The camera is downward facing. The position of the camera is such that it becomes easier for it to get the information of the things on the ground. The module creates a camera object which uses OpenCV's *VideoCapture* oject to read frames of the incoming video stream. If there is a need for debugging, the camera has debugging mode. A flag can be used to toggle the debug mode. In the debug mode, the camera reads a default image provided in the *data* folder. The camera module has *is_running_* flag which indicates whether the camera is running or not. 

Ultrasonic sensor is front facing. The location is such that it can detect the obstacles in the front of the robot. In this module the readings from the sensor are simulated using pseudo-random number generator. But the logic is treats it as sensor readings and not as random numbers. The ultrasonic sensor also has *is_running_* flag which indicates whether the sensor is running or not. 

## Algorithm
The task at hand for robot is to be within the boundary it sees on the ground while avoiding the obstacles it sees in front of it. The main task for the perception module is to detect the caution tape in the image. To detect the tape a particular feature of the caution tape, the fact that it is yellow and black, is used. Since, the colors of the tape are already known it becomes easier to detect the tape. *Camera* module pre-processes the image. Pre-processing includes finding the *inRange* pixels i.e. find the pixels which are within the range of *yellow* and *black* colors. Adding the two images will give the *blob* of tape in the image. The *perception* module then uses this pre-processed image as an input to determine the location of the tape in it. To locate the line in the given module has 2 methods: 

* First is to *Hough transforms* to find the lines. OpenCV's *Houghlines* function finds the possible lines in the image and sorts them according the number of votes. The highest voted line is the first element of the vector which can be used to find the points on that line. 

* Second method is to find the largest closed contour in the image which is probably the tape. To detect the largest contour, the simplest way is to iterate over all possible closed contours and find the largest contour based on its area. The center of the largest contour can then be found to decide the heading direction.

Based on the method used to find the location of the tape, *control* module has different methods to compute control action. For the first method described above, the location of both the points can be used to determine whether the line is horizontal or vertical and then check if the points are located in which quadrant of the image. The angle of heading can also be calculated from the *slope* of the line. For the second method, the location of the center can be used to approximately determine the quadrant in which the line lies. This method is not good since it can locate the tape approximately. Hence, the usage of the first method is suggested and is set as default. 

The *control* module first checks the reading from the ultrasonic sensor to determine whether any obstacle is present in front of the robot or not. If it finds an obstacle it issues the command to *go back*. If no obstacles are found then it detects the tape in the image. It then locates the points and based on the location of points it generates the control action.

## Output

The following table shows the output for the vertically detected line in the image.


| Input Image   | Pre-processed output | detected line |
| ------------- | ------------- | ------------- | 
| <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_caution_tape1.png" width="270">   | <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_preprocess_1.jpg" width="270"> | <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_final_1.jpg" width="270"> | 

The output generated by the controller for the image above is:
```
[INFO] Starting the controller...
[DEBUG] Debugging camera sensor.
Length of lines_: 246
Point 1: 553,957
Point 2: 553,2
[INFO] The computed control action is:
Go left laterally at angle: 89.999992
```

| Input Image   | Pre-processed output | detected line |
| ------------- | ------------- | ------------- | 
| <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_caution_tape2.png" width="270">   | <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_preprocess_2.jpg" width="270"> | <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_final_2.jpg" width="270"> | 

The output generated by the controller for the image above is:
```
[INFO] Starting the controller...
[DEBUG] Debugging camera sensor.
Length of lines_: 239
Point 1: 0,555
Point 2: 955,555
[INFO] The computed control action is:
Go forward at angle: 0.000000
```

| Input Image   | Pre-processed output | detected line |
| ------------- | ------------- | ------------- | 
| <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_caution_tape3.png" width="270">   | <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_preprocess_3.jpg" width="270"> | <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_final_3.jpg" width="270"> | 

The output generated by the controller for the image above is:
```
[INFO] Starting the controller...
[DEBUG] Debugging camera sensor.
Length of lines_: 251
Point 1: 83,957
Point 2: 83,0
[INFO] The computed control action is:
Go right laterally at angle: 89.999992
```

| Input Image   | Pre-processed output | detected line |
| ------------- | ------------- | ------------- | 
| <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_caution_tape4.png" width="270">   | <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_preprocess_4.jpg" width="270"> | <img src="https://github.com/nr-parikh/acme_robotics_perception_module/blob/master/data/test_final_4.jpg" width="270"> | 

The output generated by the controller for the image above is: 
```
[INFO] Starting the controller...
[DEBUG] Debugging camera sensor.
Length of lines_: 250
Point 1: 2,84
Point 2: 957,84
[INFO] The computed control action is:
Go back at angle: 0.000000
```

## Instructions to generate documentation
The documentation for this project can be found at the path `documentation/html/index.html`. The documentation for this project is created using *doxygen-gui*. To generate the documentation again, please execute the commands given below:
```
$ sudo apt-get install doxygen
$ sudo apt-get install doxygen-gui
$ doxywizard
```
The last command opens up the GUI window of *doxygen*. First select a dummy folder for doxygen to run from. After that, complete the details as required like name, synopsis, and version of the project. Select this repository as source directory and select a destination directory as well. Please make sure you check *scan recursively* option in order to generate the complete documentation. Once doxygen runs successfully, navigate to your destination directory, go to *html* folder and open *index.html* file. 
