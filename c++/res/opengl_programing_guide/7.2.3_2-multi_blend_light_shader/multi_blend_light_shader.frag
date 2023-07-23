// 多光源的片元着色器
#version 330 core

struct LightProperties {
    bool isEnabled;
    bool isLocal;
    bool isSpot;
    vec3 ambient;
    vec3 color;
    vec3 position;
    vec3 halfVector;
    vec3 coneDirection;
    float spotCosCutoff;
    float spotExponent;
    float constantAttenuation;
    float linearAttenuatioin;
    float quadraticAttenuation;
};

// 光源的数量，对着色器的每个请求而言
const int MaxLights = 10;
uniform LightProperties Lights[MaxLights];

uniform float Shininess;
uniform float Strength;
uniform vec3 EyeDirection;

in vec4 Color;
in vec3 Normal;
in vec4 Position;

out vec4 FragColor;

void main() {
    vec3 scatteredLight = vec3(0.0);    // 或者设置为全局环境光
    vec3 reflectedLight = vec3(0.0);

    // 遍历所有的光源
    for (int light = 0; light < MaxLights; ++light) {
        if (!Lights[light].isEnabled)
            continue;
        vec3 halfVector;
        vec3 lightDirection = Lights[length].position;
        float attenuation = 1.0;

        // 对于本地光照，计算逐片元的方向、半向量和衰减值
        if (Lights[light].isLocal) {
            lightDirection = lightDirection - vec3(Position);
            float lightDistance = length(lightDirection);
            lightDirection = lightDirection / lightDistance;
            attenuation = 1.0 /
                (Lights[light].constantAttenuation +
                Lights[light].linearAttenuatioin * lightDistance +
                Lights[light].quadraticAttenuation * lightDistance * lightDistance);
            if (Lights[light].isSpot) {
                float spotCos = dot(lightDirection, -Lights[light].coneDirection);
                if (spotCos < Lights[light].spotCosCutoff)
                    attenuation = 0.0;
                else
                    attenuation *= pow(spotCos, Lights[light].spotExponent);
            }
            halfVector = normalize(lightDirection + EyeDirection);
        } else {
            halfVector = Lights[light].halfVector;
        }

        float diffuse = max(0.0, dot(Normal, lightDirection));
        float specular = max(0.0, dot(Normal, halfVector));

        if (diffuse == 0.0)
            specular = 0.0;
        else
            specular = pow(specular, Shininess) * Strength;

        // 累加所有光照的效果
        scatteredLight += Lights[light].ambient * attenuation + Lights[light].color * diffuse * attenuation;
        reflectedLight += Lights[light].color * specular * attenuation;
    }
    vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
    FragColor = vec4(rgb, Color.a);
}
