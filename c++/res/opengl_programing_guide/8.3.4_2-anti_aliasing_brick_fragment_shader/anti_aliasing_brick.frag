#version 330 core

uniform vec3 BrickColor, MortarColor;
uniform vec2 BrickSize;
uniform vec2 BrickPct;
uniform vec2 MortarPct;

in vec2 MCPosition;
in float LightIntensity;

out vec4 FragColor;

#define Integral(x, p, notp) ((floor(x)*(p)) + max(fract(x)-(notp), 0.0))

void main() {
    vec2 position, fw, useBrick;
    vec3 color;
    // 判断砖块花纹的位置
    position = MCPosition / BrickSize;
    // 修改每一行砖块，添加半个砖块的偏移值
    if (fract(position.y * 0.5) > 0.5)
        position.x += 0.5;
    // 计算滤波大小
    fw = twidth(position);
    // 通过 2D 脉冲的积分来进行滤波，来自于滤波宽度和高度上的砖块花纹
    useBrick = (Integral(position + fw, BrickPct, MortarPct) - Integral(position, BrickPct, MortarPct)) / fw;
    // 判断最后的颜色
    color = mix(MortarColor, BrickColor, useBrick.x * useBrick.y);
    color *= LightIntensity;
    FragColor = vec4(color, 1.0);
}
