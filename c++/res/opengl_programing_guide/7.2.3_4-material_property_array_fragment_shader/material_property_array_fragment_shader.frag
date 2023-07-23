// 用于选择多光源对应材质的片元着色器片段
#version 330 core

struct MaterialProperties {
    vec3 emission;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// 每个着色器请求对应的一系列可选材质
const int NumMaterials = 14;
uniform  MaterialProperties Material[NumMaterials];

flat in int MatIndex;   // 从顶点着色器输入材质索引
// ...

void main() {
    // ...
    {
    // 累加所有光照的效果
    scatteredLight +=
        Lights[light].ambient * Material[MatIndex].ambient * attenuation +
        Lights[light].color * Material[MatIndex].diffuse * diffuse * attenuation;
    reflectedLight +=
        Lights[light].color * Material[MatIndex].specular * specular * attenuation;
    }

    vec3 rgb = min(Material[MatIndex].emission + Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
    FragColor = vec4(rgb, Color.a);
}
