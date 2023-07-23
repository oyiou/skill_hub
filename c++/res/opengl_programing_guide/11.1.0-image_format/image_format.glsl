// 一个 2D 图像，数据格式为四个分量的浮点数
layout (rgba32f) uniform image2D image1;

// 一个 2D 图像，数据格式为两个分量的整数
layout (rg32i) uniform iimage2D image2;

// 一个 1D 图像，数据格式为单个分量的无符号整数
layout (r32ui) uniform uimage1D image3;

// 一个 3D 图像，数据格式为单个分量的整数，并且初始化的时候绑定到图像单元 4
layout (binding = 4, r32) uniform iimage3D image4;