
struct MaterialProperties {
    vec3 emission;  // 材质产生的照明
    vec3 ambient;   // 反射环境光照的部分
    vec3 diffuse;   // 反射漫反射光照的部分
    vec3 specular;  // 反射镜面光照的部分
    float shininess;    // 镜面反射高光的指数
    // 其他需要的属性
};