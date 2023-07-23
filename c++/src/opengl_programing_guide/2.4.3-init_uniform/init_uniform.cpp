
#include "opengl_programing_guide.h"

// 顶点着色器和片元着色器共享同一个名为 Uniforms 的 uniform 块
// named "Uniforms
const char* vShader = {
    "#version 330 core\n"
    "uniform Uniforms {"
    "   vec3 translation;"
    "   float scale;"
    "   bool enabled;"
    "};"
    "in vec2 vPos;"
    "in vec3 vColor;"
    "out vec4 fColor;"
    "void main()"
    "{"
    "   vec3 pos = vec3(vPos, 0.0);"
    "   float angle = radians(rotation[0]);"
    "   vec3 axis = normalize(rotation.yzw);"
    "   mat3 I = mat3(1,0);"
    "   mat3 S = mat3(0, -axis.z, axis.y,"
    "               axis.z, 0, -axis.x,"
    "               -axis.y, axis.x, 0);"
    "   mat3 uuT = outerProduct(axis, axis);"
    "   mat3 rot = uuT + cons(angle)*(I - uuT) + sin(angle)*S;"
    "   pos *= scale;"
    "   pos *= rot;"
    "   pos += translation;"
    "   fColor = vec4(scale, scale, scale, 1);"
    "   gl_Position = vec4(pos, 1);"
    "}"
};
const char* fShader = {
        "#version 330 core\n"
        "uniform Uniforms {"
        "   vec3 translation;"
        "   float scale;"
        "   vec4 rotation;"
        "   bool enabled;"
        "};"
        "in vec4 fColor;"
        "out vec4 color;"
        "void main()"
        "{"
        "   color = fColor;"
        "}"
};
// 用于将 GLSL 类型转换为存储大小的辅助函数
size_t TypeSize(GLenum type)
{
    size_t size;
#define  CASE(Enum, Count, Type) case Enum: size = Count * sizeof(Type); break
    switch (type) {
        CASE(GL_FLOAT,              1,      GLfloat);
        CASE(GL_FLOAT_VEC2,         2,      GLfloat);
        CASE(GL_FLOAT_VEC3,         3,      GLfloat);
        CASE(GL_FLOAT_VEC4,         4,      GLfloat);
        CASE(GL_INT,                1,      GLint);
        CASE(GL_INT_VEC2,           2,      GLint);
        CASE(GL_INT_VEC3,           3,      GLint);
        CASE(GL_INT_VEC4,           4,      GLint);
        CASE(GL_UNSIGNED_INT,       1,      GLuint);
        CASE(GL_UNSIGNED_INT_VEC2,  2,      GLuint);
        CASE(GL_UNSIGNED_INT_VEC3,  3,      GLuint);
        CASE(GL_UNSIGNED_INT_VEC4,  4,      GLuint);
        CASE(GL_BOOL,               1,      GLboolean);
        CASE(GL_BOOL_VEC2,          2,      GLboolean);
        CASE(GL_BOOL_VEC3,          3,      GLboolean);
        CASE(GL_BOOL_VEC4,          4,      GLboolean);
        CASE(GL_FLOAT_MAT2,         4,      GLfloat);
        CASE(GL_FLOAT_MAT2x3,       6,      GLfloat);
        CASE(GL_FLOAT_MAT2x4,       8,      GLfloat);
        CASE(GL_FLOAT_MAT3,         9,      GLfloat);
        CASE(GL_FLOAT_MAT3x2,       6,      GLfloat);
        CASE(GL_FLOAT_MAT3x4,       12,     GLfloat);
        CASE(GL_FLOAT_MAT4,         16,     GLfloat);
        CASE(GL_FLOAT_MAT4x2,       8,      GLfloat);
        CASE(GL_FLOAT_MAT4x3,       12,     GLfloat);
#undef CASE
        default:
            fprintf(stderr, "Unknown type: 0x%x\n", type);
            exit(EXIT_FAILURE);
            //break;
    }
    return size;
}
void init()
{
    GLuint program;
    glClearColor(1, 0, 0, 1);
    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, vShader},
            {GL_FRAGMENT_SHADER, fShader},
            {GL_NONE, nullptr}
    };
    program = LoadShaders(shaders);
    glUseProgram(program);
    // 初始化 uniform 块 Uniforms 中的变量
    GLuint  uboIndex;
    GLint   uboSize;
    GLuint  ubo;
    GLvoid  *buffer;
    // 查找 Uniforms 的 uniform 缓存索引，并判断整个块的大小
    uboIndex = gl3wGetUniformBlockIndex(program, "Uniforms");
    gl3wGetActiveUniformBlockiv(program, uboIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
    buffer = malloc(uboSize);
    if (buffer == nullptr) {
        fprintf(stderr, "Unable to allocate buffer\n");
        exit(EXIT_FAILURE);
    } else {
        enum {Translation, Scale, Rotation, Enabled, NumUniforms};
        // 准备存储在缓存对象中的值
        GLfloat     scale           = 0.5;
        GLfloat     translation[]   = {0.1, 0.1, 0.0};
        GLfloat     rotation[]      = {90, 0.0, 0.0, 1.0};
        GLboolean   enabled         = GL_TRUE;
        // 可以创建一个变量名称数组，对应块中已知的 uniform 变量
        const char* names[NumUniforms] = {
                "translation",
                "scale",
                "rotation",
                "enabled"
        };
        // 查询对应的属性，以判断向数据缓存中写入数值的位置
        GLuint  indices[NumUniforms];
        GLint   size[NumUniforms];
        GLint   offset[NumUniforms];
        GLint   type[NumUniforms];

        gl3wGetUniformIndices(program, NumUniforms, names, indices);
        gl3wGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_OFFSET, offset);
        gl3wGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_SIZE, size);
        gl3wGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_TYPE, type);
        // 将 uniform 变量拷贝到缓存中
        memcpy((GLint *)buffer + offset[Scale], &scale, size[Scale] * TypeSize(type[Scale]));
        memcpy((GLint *)buffer + offset[Translation], &translation, size[Translation] * TypeSize(type[Translation]));
        memcpy((GLint *)buffer + offset[Rotation], &rotation, size[Rotation] * TypeSize(type[Rotation]));
        memcpy((GLint *)buffer + offset[Enabled], &enabled, size[Enabled] * TypeSize(type[Enabled]));
        // 建立 uniform 缓存对象，初始化存储内容，并且与着色器程序建立关联
        glGenBuffers(1, &ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo);
        glBufferData(GL_UNIFORM_BUFFER, uboSize, buffer, GL_STATIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex, ubo);
    }
    // ...
}