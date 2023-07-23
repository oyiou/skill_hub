#version 410 core

// 位置和法线都是规则的顶点属性
layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;

// 颜色是一个逐实例的属性
layout (location = 2) in vec4 color;

// model_matrix 是一个逐实例的变换矩阵。注意一个 mat4 会占据四个连续的位置，因此它实际上占据了 3、4、5、6 四个所谓位
layout (location = 3) in mat4 model_matrix;