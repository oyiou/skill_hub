#version 330 core

uniform vec3 Color0;
uniform vec3 Color1;
uniform vec3 AvgColor;
uniform float Frequency;

in vec2 TexCoord;

out vec4 FragColor;

void main() {
    vec3 color;
    // 判断一个像素投影到 S-T 空间的宽度
    vec2 fw = fwidth(TexCoord);

    // 判断模糊的总量
    vec2 fuzz = fw * Frequency * 2.0;

    float fuzzMax = max(fuzz.s, fuzz.t);

    // 判断棋盘格花纹的位置
    vec2 checkPos = fract(TexCoord * Frequency);

    if (fuzzMax < 0.5) {
        // 如果滤波宽度足够小，则计算花纹的颜色
        vec2 p = smoothstep(vec2(0.5), fuzz + vec2(0.5), checkPos) + (1.0 - smoothstep(vec2(0.0), fuzz, checkPos));

        color = mix(Color0, Color1, p.x * p.y + (1.0 - p.x) * (1.0 - p.y));

        // 如果已经接近极限值，则渐入到平均颜色
        color = mix(color, AvgColor, smoothstep(0.125, 0.5, fuzzMax));
    } else {
        // 否则的话，直接使用平均颜色值
        color = AvgColor;
    }

    FragColor = vec4(color, 1.0);
}
