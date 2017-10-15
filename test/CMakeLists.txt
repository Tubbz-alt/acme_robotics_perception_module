set(GTEST_SHUFFLE 1)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(
    cpp-test
    main.cpp
    test_camera.cpp
    test_ultrasonic_sensor.cpp
    test_perception_module.cpp
    test_control_module.cpp
    ../app/camera.cpp
    ../app/ultra_sensor.cpp
    ../app/perception_module.cpp
    ../app/control_module.cpp
)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(cpp-test PUBLIC gtest ${OpenCV_LIBS})
