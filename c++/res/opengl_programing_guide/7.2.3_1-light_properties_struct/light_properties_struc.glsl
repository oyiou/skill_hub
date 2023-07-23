//
// Created by leever on 2023/4/27.
//

// 保存光照属性的结构体
struct LightProperties {
    bool isEnabled; // true to apply this light in this invocation
    bool isLocal;   // true for a point light or a spotlight, false for a positional light
    bool isSpot;    // true if the light is a spotlight
    vec3 ambient;   // light's contribution to ambient light
    vec3 color; // color of light
    vec3 position;  // location of light, if is Local is true, otherwise the direction toward the light
    vec3 halfVector;    // direction of highlights for directional light
    vec3 coneDirection; // spotlight attributes
    float spotCosCutoff;
    float spotExponent;
    float constantAttenuation;  // local light attenuation coefficients
    float linearAttenuation;
    float quadraticAttenuation;
    // other properties you may desire
};