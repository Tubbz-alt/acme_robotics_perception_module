add_executable(perception_module main.cpp camera.cpp ultra_sensor.cpp perception_module.cpp control_module.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries( perception_module ${OpenCV_LIBS} )
