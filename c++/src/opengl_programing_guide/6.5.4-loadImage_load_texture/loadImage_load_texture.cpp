//
// Created by leever on 2023/4/17.
//
#include "LoadImage.h"
#include "opengl_programing_guide.h"

GLuint LoadTexture(const char *filename, GLuint texture, GLboolean generateMips) {
    vglImageData image;
    int level;
    vglLoadImage(filename, &image);
    if (texture == 0) {
        glGenTextures(1, &texture);
    }
    glBindTexture(image.target, texture);
    switch (image.target) {
        case GL_TEXTURE_2D:
            glTexStorage2D(image.target, image.mipLevels, image.internalFormat, image.mip[0].width, image.mip[0].height);
            // 处理其他纹理目标
        default:
            break;
    }
    // 假设是 2D 纹理
    for (level = 0; level < image.mipLevels; ++level) {
        glTexSubImage2D(GL_TEXTURE_2D, level, 0, 0, image.mip[level].width, image.mip[level].height, image.format, image.type, image.mip[level].data);
    }
    // 卸载图像，因为 glTexSubImage2D 已经有数据，所以已不再需要图像
    vglUnloadImage(&image);
    return texture;
}