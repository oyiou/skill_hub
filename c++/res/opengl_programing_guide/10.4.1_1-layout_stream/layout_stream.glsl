// 这里的设置其实是多余的，因为默认流就是 0
layout (stream = 0) out;
// foo 和 bar 均为数据流 0 的成员
out vec4 foo;
out vec4 bar;

// 将输出流切换到 1
layout (stream = 1) out;
// proton 和 electron 均为数据流 1 的成员
out vec4 proton;