//
// Created by leever on 2023/4/21.
//
#include "opengl_programing_guide.h"

// 数据是 ABGR 格式的纹理名称
GLuint abgr_texture;
// 数据是 RGBx 格式的纹理名称
GLuint rgbx_texture;
// 在一次函数调用中设置 ABGR swizzle 的 token 数组
static const GLenum abgr_swizzle[] = {
        GL_ALPHA, GL_RED, GL_GREEN, GL_BLUE
};
// 绑定 ABGR 纹理
glBindTexture(GL_TEXTURE_2D, abgr_texture);
// 在 glTexParameteriv() 的一次调用中设置所有四个 swizzle 参数
glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, abgr_swizzle);
// 现在绑定 RGBx 纹理
glBindTexture(GL_TEXTURE_2D, rgbx_texture);
// 在这里只设置 GL_TEXTURE_SWZZLE_A 参数，因为 R、G、B swizzle 可以是它们的默认值
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ONE);