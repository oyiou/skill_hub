//
// Created by leever on 2023/4/13.
//
#include "opengl_programing_guide.h"
static const char *varyings[] = {
        "position_out", "velocity_out"
};
glTransformFeedbackVaryings(update_prog, 2, varyings, GL_INTERLEAVED_ATTRIBS);
glLinkProgram(update_prog);