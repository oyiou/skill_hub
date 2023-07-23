// 矩阵和投影在绘制过程中都是常数
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
// 设置 TBO 来保存逐实例的颜色数据和模型矩阵数据
uniform samplerBuffer color_tbo;
uniform samplerBuffer model_matrix_tbo;
// 顶点着色器的输出（对应于片元着色器的输入）
out VERTEX {
    vec3 normal;
    vec4 color;
} vertex;
// 现在开始
void main(void) {
    // 使用 gl_InstanceID 从颜色值的 TBO 当中获取数据
    vec4 color = texelFetch(color_tbo, gl_InstanceID);

    // 模型矩阵的生成更为复杂一些，因为不能直接在 TBO 中存储 mat4 数据
    // 需要就将每个矩阵都保存为四个 vec4 的变量，然后在着色器中重新装配为矩阵的形式
    // 首先，获取矩阵的四列数据（注意，矩阵在内存中的存储采用了列主序的方式）
    vec4 col1 = texelFetch(model_matrix_tbo, gl_InstanceID * 4);
    vec4 col2 = texelFetch(model_matrix_tbo, gl_InstanceID * 4 + 1);
    vec4 col3 = texelFetch(model_matrix_tbo, gl_InstanceID * 4 + 2);
    vec4 col4 = texelFetch(model_matrix_tbo, gl_InstanceID * 4 + 3);

    // 现在将四列装配为一个矩阵
    mat4 model_matrix = mat4(col1, col2, col3, col4);

    // 根据 uniform 观察矩阵和逐实例的模型矩阵构建完整的模型——视点矩阵

    mat4 model_view_matrix = view_matrix * model_matrix;

    // 首先用模型——视点矩阵变换位置，然后是投影矩阵

    gl_Position = projection_matrix * (model_view_matrix * position);
    // 使用模型——视点矩阵的左上 3x3 子矩阵变换法线
    vertex.normal = mat3(model_view_matrix) * normal;
    // 将逐实例的颜色值直接传入片元着色器
    vertex.color = color;
}
