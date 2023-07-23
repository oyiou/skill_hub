//
// Created by leever on 2023/4/13.
//
#include "opengl_programing_guide.h"
static const char *varyings2[] = {
        "world_space_position"
};
glTransformFeedbackVaryings(render_prog, 1, varyings2, GL_INTERLEAVED_ATTRIBS);
glLinkProgram(render_prog);