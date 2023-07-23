static const char *varyings[] = {
        // 这两个变量属于数据流 0
        "rf_position", "rf_normal",
        // 移动到下一个绑定点（不能把不同数据流的变量写入同一个缓存绑定点）
        "gl_NextBuffer",
        // 这两个变量属于数据流 1
        "lf_position", "lf_normal"
};
glTransformFeedbackVaryings(sort_prog, 5, varyings, GL_INTERLEAVED_ATTRIBS);