//
// Created by leever on 2023/5/10.
//
#include "opengl_programing_guide.h"

// 这里设置了最大能支持的帧缓存宽度和高度。
// 也可以支持更高的分辨率，不过对于这个程序来说已经足够了
#define MAX_FRAMEBUFFER_WIDTH 2048
#define MAX_FRAMEBUFFER_HEIGHT 2048

// 局部变量
GLuint *data;
size_t total_pixels = MAX_FRAMEBUFFER_WIDTH * MAX_FRAMEBUFFER_HEIGHT;

// 创建一个 2D 图像，用来存储逐像素链表中的 head 指针信息
GLuint head_pointer_texture;
glGenTextures(1, &head_pointer_texture);
glBindTexture(GL_TEXTURE_2D, head_pointer_texture);
glTexImage2D(GL_TEXTURE_2D, 0,          // 2D texture，0 级
             GL_R32UI,                  // 每个纹素都是 23-bit GLuint
             MAX_FRAMEBUFFER_WIDTH,     // 宽度
             MAX_FRAMEBUFFER_HEIGHT,    // 高度
             0,                         // 无边界
             GL_RED_INTEGER,            // 单通道
             GL_UNSIGNED_INT,           // 无符号整数
             NULL);                     // 目前尚无数据

// 每帧开始的时候都需要重新初始化 head 指针。
// 最简单的方法就算从 PBO 拷贝过来。
// 这里采取自行创建的方法
GLuint head_pointer_initializer;
glGenBuffers(1, &head_pointer_initializer);
glBindBuffer(GL_PIXEL_UNPACK_BUFFER, head_pointer_initializer);
glBufferData(GL_PIXEL_UNPACK_BUFFER,
             total_pixels * sizeof(GLuint),     // 每像素一个 uint 无数据，
             NULL,                              // 数据将采取映射的方式
             GL_STATIC_DRAW);                   // 不要主动改变
data = (GLuint)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
// 0xFF 相当于“链表结束”的标识
memset(data, 0xFF, total_pixels * sizeof(GLuint));
glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

// 下面，要创建原子计数缓存来记录原子计数器。
// 只需要一个计数器，因此最小的缓存就已经够了
GLuint atomic_counter_buffer;
glGenBuffers(1, &atomic_counter_buffer);
glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, atomic_counter_buffer);
glBufferData(GL_ATOMIC_COUNTER_BUFFER,  // 分配缓存
            sizeof(GLuint), NULL,       // 只需要一个 GLuint
            GL_DYNAMIC_COPY);           // 通过 GPU 写入

// 最后，创建一个较大的一维缓存来存储片元数据。为屏幕上的每个像素都分配一个可以存储两个片元的空间。
// 再次注意，这只是绘制的平均值，应该足够使用了，只要平均值较低，那么某几个像素包含大量的片元数据也是没问题的
GLuint fragment_storage_buffer;
glGenBuffers(1, &fragment_storage_buffer);
glBindBuffer(GL_TEXTURE_BUFFER, fragment_storage_buffer);
glBufferData(GL_TEXTURE_BUFFER,
             2 * total_pixels *                 // 像素最大值的两倍
             sizeof(vec4),                      // 乘以 vec4 的大小
             NULL,                              // 无数据
             GL_DYNAMIC_COPY);                  // 通常由 GPU 更新