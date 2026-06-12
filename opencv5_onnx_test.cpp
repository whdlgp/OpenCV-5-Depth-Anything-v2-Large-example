#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

// ============================================================================
// [Example] Depth Anything V2 Large Inference using OpenCV 5.0 DNN
// - Model       : Depth Anything V2 Large (FP32, ONNX converted)
//   - Model Source: https://huggingface.co/onnx-community/depth-anything-v2-large
//   - Download File: 'onnx/model.onnx' (From Files and Versions)
//
// [Author Info]
// - Name        : ChoYG (whdlgp)
// - Contact     : choyg.dev@gmail.com
//
// [Tested Environment]
// - OS          : Windows 11
// - GPU         : NVIDIA GeForce MX150 (2GB VRAM)
// - Compiler    : Visual Studio 2026
// ============================================================================

int main() 
{
    // Load Test image
    cv::Mat img = cv::imread("aloeL.jpg");
    if (img.empty()) 
    {
        std::cerr << "Can't load image" << std::endl;
        return -1;
    }
    std::cout << "Input image Loaded" << std::endl;
    std::cout << img.cols << "x" << img.rows << std::endl;

    // Load ONNX
    std::string model_file = "model.onnx";
    // Select Backend Engine
    // cv::dnn::ENGINE_AUTO
    // cv::dnn::ENGINE_CLASSIC (May have compatibility issues)
    // cv::dnn::ENGINE_NEW
    // cv::dnn::ENGINE_ORT (Need 'WITH_ONNXRUNTIME' flag in CMake)  
    cv::dnn::Net net = cv::dnn::readNetFromONNX(model_file, cv::dnn::ENGINE_NEW);

    // Pre-process input blob
    int img_h = img.rows;
    int img_w = img.cols;
    float scale = std::min(518.0f / img_h, 518.0f / img_w);
    int new_h = static_cast<int>(img_h * scale);
    int new_w = static_cast<int>(img_w * scale);
    new_h = (new_h / 14) * 14;
    new_w = (new_w / 14) * 14;

    cv::Mat blob;
    cv::dnn::blobFromImage(
        img, blob,
        1.0 / 255.0,
        cv::Size(new_w, new_h),
        cv::Scalar(0.485, 0.456, 0.406), //mean
        true,
        false
    );
    // std
    cv::divide(blob, cv::Scalar(0.229, 0.224, 0.225), blob);

    // Inference
    net.setInput(blob);
    auto output = net.forward();

    // Output
    int out_dims = output.dims;
    int out_h = output.size[1];
    int out_w = output.size[2];
    std::cout << "Output info" << std::endl;
    std::cout << "Dim: " << out_dims << std::endl;
    std::cout << "Height: " << out_h << std::endl;
    std::cout << "Width: " << out_w << std::endl;

    cv::Mat depth_out(out_h, out_w, CV_32F, output.ptr<float>());

    double min_val, max_val;
    cv::minMaxLoc(depth_out, &min_val, &max_val);
    std::cout << "Depth Raw Range: " << min_val << " ~ " << max_val << std::endl;

    // Show
    cv::Mat depth_norm;
    double alpha = 255.0 / (max_val - min_val);
    double beta = -min_val * 255.0 / (max_val - min_val);
    depth_out.convertTo(depth_norm, CV_8U, alpha, beta);

    cv::Mat depth_show;
    cv::resize(depth_norm, depth_show, cv::Size(img_w, img_h), 0, 0, cv::INTER_CUBIC);

    cv::imshow("Image", img);
    cv::imshow("Depth", depth_show);
    cv::waitKey(0);

    return 0;
}