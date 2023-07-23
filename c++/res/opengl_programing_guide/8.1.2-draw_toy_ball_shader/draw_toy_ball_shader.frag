#version 330 core

uniform vec4 HalfSpace[5];  // 用于定义星形的半空间
uniform float StripeWidth;
uniform float InOrOutInit;  // -3.0
uniform float FWidth;   // = 0.005

uniform vec4 StarColor;
uniform vec4 StripeColor;
uniform vec4 BaseColor;

uniform vec4 LightDir;  // 光照方向，必须经过归一化
uniform vec4 HVector;   // 无限远处光照的反射向量
uniform vec4 SpecularColor;
uniform float SpecularExponent;

uniform float Ka;
uniform float Kd;
uniform float Ks;

in vec4 ECPosition; // 人眼坐标下的表面位置
in vec3 OCPosition; // 物体坐标下的表面位置
flat in vec4 ECBallCenter;  // 人眼坐标下的球体中心

out vec4 FragColor;

void main() {
    vec3 normal;    // 计算得到的法线
    vec4 pShade;    // 着色器空间的点
    vec4 surfColor; // 计算得到的表面颜色
    float intensity;    // 计算得到的光照强度
    vec4 distence;  // 计算得到的距离值
    float inorout;  // 计算得到的星形位置计数器

    pShade.xyz = normalize(OCPosition.xyz);
    pShade.w = 1.0;

    inorout = InOrOutInit;  // 将 inorout 初始化为 -3.0

    distence[0] = dot(pShade, HalfSpace[0]);
    distence[1] = dot(pShade, HalfSpace[1]);
    distence[2] = dot(pShade, HalfSpace[2]);
    distence[3] = dot(pShade, HalfSpace[3]);

    // float FWidth = fwidth(pShade);
    distence = smoothstep(-FWidth, FWidth, distence);

    inorout += dot(distence, vec4(1.0));

    distence.x = dot(pShade, HalfSpace[4]);
    distence.y = StripeWidth - abs(pShade.z);
    distence.xy = smoothstep(-FWidth, FWidth, distence.xy);
    inorout += distence.x;

    inorout = clamp(inorout, 0.0, 1.0);

    surfColor = mix(BaseColor, StarColor, inorout);
    surfColor = mix(surfColor, StripeColor, distence.xy);

    // 计算球体上的法线值
    normal = normalize(ECPosition.xyz - ECBallCenter.xyz);

    // 逐片元的漫反射光照计算
    intensity = Ka; // 环境光
    intensity += Kd * clamp(dot(LightDir.xyz, normal), 0.0, 1.0);
    surfColor *= intensity;

    // 逐片元的镜面反射光照计算
    intensity = clamp(dot(HVector.xyz, normal), 0.0, 1.0);
    intensity = Ks * pow(intensity, SpecularExponent);
    surfColor.rgb += SpecularColor.rgb * intensity;
    FragColor = surfColor;
}
