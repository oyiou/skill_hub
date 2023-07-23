#version 330 core

struct MaterialProperties {
    vec3 emission;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// 每个着色器请求对应的一系列可选材质，偶数索引为正面，奇数为被面
const int NumMaterials = 14;
uniform MaterialProperties Material[2 * NumMaterials];

flat  in int MatIndex;  // 从顶点着色器输入材质索引
// ...

void main() {
    int mat;
    if (gl_FrontFacing)
        mat = MatIndex;
    else
        mat = MatIndex + 1;

    // ...
    {
    // 累加所有光照的效果
    scatteredLight += Lights[light].ambient * Material[mat].ambient * attenuation + Lights[light].color * Material[mat].diffuse * diffuse * attenuation;
    reflectedLight += Lights[light].color * Material[mat].specular * specular * attenuation;
    }

    vec3 rgb = min(Material[mat].emission + Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
    FragColor = vec4(rgb, Color.a);
}
