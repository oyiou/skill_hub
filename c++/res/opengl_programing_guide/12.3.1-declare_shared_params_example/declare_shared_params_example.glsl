// 一个共享的无符号整型变量
shared uint foo;

// 一个共享的向量数组
shared vec4 bar[128];

// 一个共享的数据块
shared struct baz_struct {
    vec4 a_vector;
    int an_integer;
    ivec2 an_array_of_integers[27];
} baz[42];