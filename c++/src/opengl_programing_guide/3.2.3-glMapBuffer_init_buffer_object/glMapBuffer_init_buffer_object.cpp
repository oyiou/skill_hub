//
// Created by leever on 2023/3/28.
//
#include "opengl_programing_guide.h"

GLuint buffer;
FILE *f;
size_t file_size;

// 打开文件并确定它的大小
f = fopen("data.dat", "rb");
fseek(f, 0, SEEK_END);
file_size = ftell(f);
fseek(f, 0, SEEK_SET);

// 生成缓存名字并将它绑定到缓存绑定点上——这里是
// GL_COPY_WRITE_BUFFER（在这里这个绑定点并没有实际意义）
// 这样就可以创建缓存了
glGenBuffers(1, &buffer);
glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);

// 分配缓存中存储的数据空间，向 data 参数传入 NULL 即可
glBufferData(GL_COPY_WRITE_BUFFER, (GLsizei)file_size, NULL, GL_STATIC_DRAW);
// 映射缓存...
void *data = glMapBuffer(GL_COPY_WRITE_BUFFER, GL_WRITE_ONLY);

// 将文件读入缓存
fread(data, 1, file_size, f);

// 已经完成了实验，可以解除缓存映射并关闭文件了
glUnmapBuffer(GL_COPY_WRITE_BUFFER);
fclose(f);