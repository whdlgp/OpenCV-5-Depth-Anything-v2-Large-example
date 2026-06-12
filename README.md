# OpenCV-5-Depth-Anything-v2-Large-example
An example inference of Depth Anything v2 with OpenCV 5

## Dependencies
To build and run this example, you need the following libraries:

1. **OpenCV 5.x**
   - Need to build yourself (Official pre-build version not tested)
   - To use ONNX Runtime backend('cv::dnn::ENGINE_ORT')
     - Enable 'WITH_ONNXRUNTIME' CMake flag
     - Optionally, enable 'DOWNLOAD_ONNXRUNTIME_GPU' to use GPU (No need to install CUDA)

## How to build

## 🛠️ Build and Usage Instructions

This project uses CMake for configuration. Follow the steps below to generate the Visual Studio solution and run the application.

### 1. Directory Structure Setup
1. Use CMake. 
2. Ensure your project directory is structured as follows

```text
your-project-root/
├── CMakeLists.txt
├── opencv5_onnx_test.cpp
└── test/
    ├── test.jpg          <-- Place your input image here
    └── model.onnx        <-- Place the downloaded ONNX model here
```

### 2. Configure and Build

```bash
# Create a build directory
mkdir build
cd build

# Configure CMake project with OpenCV build path
cmake .. -DOpenCV_DIR="C:/path/to/opencv/build"

# Build the project (For Release mode)
cmake --build . --config Release
```
