cmake_minimum_required(VERSION 3.10)
project(opencv5_onnx_test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

# Target
set(TARGET_NAME opencv5_onnx_test)
add_executable(${TARGET_NAME} opencv5_onnx_test.cpp)

target_link_libraries(${TARGET_NAME} ${OpenCV_LIBS})

# Output Directory
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/test")

# Working directory
# - Debug file with "*_d"
# - All Debug and Release execution files in OUTPUT_DIR
# - Visual Studio will debug with OUTPUT_DIR
set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}")
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}")
set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${OUTPUT_DIR}")

# Copy OpenCV's DLL files to Working(*.exe file location) directory
file(GLOB_RECURSE OPENCV_DLLS "${OpenCV_DIR}/*.dll")
add_custom_command(TARGET opencv5_onnx_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${OPENCV_DLLS} $<TARGET_FILE_DIR:${TARGET_NAME}>
    COMMAND_EXPAND_LISTS)
