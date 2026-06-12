cmake_minimum_required(VERSION 3.10)
project(opencv5_onnx_test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(opencv5_onnx_test opencv5_onnx_test.cpp)

target_link_libraries(opencv5_onnx_test ${OpenCV_LIBS})

# Working Directory set
set_target_properties(opencv5_onnx_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test
)
set_target_properties(opencv5_onnx_test PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/test
)