//
// Created by leever on 2023/4/6.
//
#include "opengl_programing_guide.h"

count = 1000;   // 使用计数器来避免陷入无限循环

while (!queryReady && count-) {
glGetQueryObjectiv(Query, GL_QUERY_RESULT_AVAILABLE, &queryReady);
}

if (queryReady) {
glGetQueryObjectiv(Query, GL_QUERY_RESULT, &samples);
std::cerr << "Samples rendered: " << samples << std::endl;
} else {
std::cerr << "Result not ready ... rendering anyways" << std::endl;
samples = 1;    // 确保进行一次渲染
}
if (samples > 0) {
glDrawArrays(GL_TRIANGLE_FAN, 0, NumVertices);
}