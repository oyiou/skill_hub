// 映射缓存
mat4 *matrices = (mat4 *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

// 设置每个实例的模型矩阵
for (n = 0; n < INSTANCE_COUNT; n++) {
    float a = 50.0f * float(n) / 4.0f;
    float b = 50.0f * float(n) / 5.0f;
    float c = 50.0f * float(n) / 6.0f;

    matrices[n] = rotation(a + t * 360.0f, 1.0f, 0.0f, 0.0f) *
    rotation(b + t * 360.0f, 0.0f, 1.0f, 0.0f) *
    rotation(b + t * 360.0f, 0.0f, 1.0f, 0.0f) *
    translation(10.0f + a, 40.0f + b, 50.0f + c);
}

// 完成后解除映射
glUnmapBuffer(GL_ARRAY_BUFFER);

// 启用多实例的程序
glUseProgram(render_prog);

// 设置观察矩阵和投影矩阵
mat4 view_matrix(translation(0.0f, 0.0f, -1500.0f) * rotation(t * 360.0f * 2.0f, 0.0f, 1.0f, 0.0f));
mat4 projection_matrix(frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 5000.0f));

glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, view_matrix);
glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, projection_matrix);

// 渲染 INSTANCE_COUNT 个模型
glDrawArraysInstanced(GL_TRIANGLES, 0, object_size, INSTANCE_COUNT);