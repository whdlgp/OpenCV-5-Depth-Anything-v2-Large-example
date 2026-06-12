# OpenCV 5.x Depth Anything v2 Large inference example.
An example inference of Depth Anything v2 with OpenCV 5 DNN module.

## Dependencies
To build and run this example, you need the following library and ONNX file.

1. OpenCV 5.x
   - Need to build yourself (Official pre-build version not tested).
   - To use ONNX Runtime backend('cv::dnn::ENGINE_ORT')
     - Enable 'WITH_ONNXRUNTIME' CMake flag.
     - Optionally, enable 'DOWNLOAD_ONNXRUNTIME_GPU' to use GPU (No need to install CUDA).
2. ONNX File
   - Download converted ONNX file from [Here](https://huggingface.co/onnx-community/depth-anything-v2-large).
     - 'onnx/model.onnx' in 'Files and versions'.
     - Quantized models (e.g., FP16/INT8) may not work properly.

## How to build
This project uses CMake for configuration. Follow the steps below.

### Directory Structure Setup
1. Use CMake. 
2. Ensure your project directory is structured as follows

```text
your-project-root/
├── CMakeLists.txt
├── opencv5_onnx_test.cpp
└── test/
    ├── aloeL.jpg         <-- Place your input image here
    └── model.onnx        <-- Place the downloaded ONNX model here
```

### Configure and Build

```bash
# Create a build directory
mkdir build
cd build

# Configure CMake project with OpenCV build path
cmake .. -DOpenCV_DIR="C:/path/to/opencv/build"

# Build the project (For Release mode)
cmake --build . --config Release
```

### Test sample
1. Input image
![](test/aloeL.jpg)
3. Sample output
![](example_output.jpg)
