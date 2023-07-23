//
// Created by leever on 2023/4/14.
//

#ifndef C_LOADIMAGE_H
#define C_LOADIMAGE_H

#include "opengl_programing_guide.h"
// 对于 16k x 16k 的足够 mipmaps，这是 OpenGL 4.x 和更高版本的最小级数要求
#define MAX_TEXTURE_MIPS 14
// 每个纹理图像数据结构包括这些 mipmap 结构的 MAX_TEXTURE_MIPS 数组
// 结构表示这个级所有切片的 mipmap 数据
struct vglImageMipData {
    GLsizei width;  // mipmap 级的宽度
    GLsizei height; // mipmap 级的高度
    GLsizei depth;  // mipmap 级的深度
    GLsizeiptr mipStride;   // 内存中 mipmap 级之间的距离
    GLvoid *data;   // 数据的指针
};
// 这是主图像数据结构。它包括使用 OpenGL 将纹理数据放进纹理对象所需要的所有参数
struct vglImageData {
    GLenum target;  // 纹理目标（2D、立方体映射等）
    GLenum internalFormat;  // 推荐的内部格式
    GLenum format;  // 内存中的格式
    GLenum swizzle[4];  // RGBA 的 swizzle 特性
    GLsizei mipLevels;  // mipmap 级的数目
    GLsizei slices;    // 切片的数目（对于数组）
    GLsizeiptr sliceStride; // 数组纹理中切片之间的距离
    GLsizeiptr totalDAtaSize;   // 为纹理分配的所有数据
    vglImageMipData mip[MAX_TEXTURE_MIPS];  // 实际的 mipmap 数据
};

#endif //C_LOADIMAGE_H
