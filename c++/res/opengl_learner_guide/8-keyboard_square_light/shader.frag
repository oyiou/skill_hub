#version 330 core
in vec3 ourColor;
in vec3 FragNormal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 LightPos;
uniform vec3 CameraPos;

void main()
{
    vec3 std_norm = normalize(FragNormal);

    // 环境光照
    float ambientStrength = 0.1;					// 常量(光照)颜色因子
    vec3 ambient = ambientStrength  * ourColor;		// 环境光照

    // 漫反射光照
    vec3 SendLight = normalize(LightPos - FragPos);
    float diff = 0.6 * max(dot(FragNormal, SendLight), 0.0f);
    vec3 diffuse = diff * ourColor;

    // 镜面反射光照
    vec3 ReflectLight = reflect(-SendLight, FragNormal);
    float specularStrength = 0.8;
    vec3 CameraDir = normalize(CameraPos - FragPos);
    vec3 specular = specularStrength * pow(max(dot(CameraDir, ReflectLight), 0.0), 32) * ourColor;

    FragColor = vec4(ambient + diffuse + specular, 1.0f);
}