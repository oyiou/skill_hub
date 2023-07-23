//
// Created by leever on 2023/5/10.
//
#include "opengl_programing_guide.h"

// 这是同步对象
GLsync s;

// 绑定一个顶点数组，然后绘制一组几何体
glBindVertexArray(vao);

glDrawArrays(GL_TRIANGLES, 0, 30000);

// 创建栅栏，当上面的绘制命令结束它就会变成有信号的状态
s = glFenceSync();

// 映射上述绘制命令时需要用到的 uniform 缓存
void * data = glMapBufferRange(GL_UNIFORM_BUFFER,
                               0, 256,
                               GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);

// 现在需要执行一些耗费时间的操作，比如，计算新的 uniform 值
do_something_time_consuming();

// 等待同步对象变成有信号的状态 1,000,000 ns = 1 ms
switch(glClientWaitSync(s, 0, 1000000));

// 现在删除同步对象，写入 uniform 缓存然后解除映射
glDeleteSync(s);

memcpy(data, source_data, source_data_size);

glUnmapBuffer(GL_UNIFORM_BUFFER);