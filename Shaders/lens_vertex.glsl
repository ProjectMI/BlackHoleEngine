#version 330 core
layout(location = 0) in vec3 aPos;   // круг в плоскости XY
layout(location = 1) in vec2 aTex;   // не обязательно; оставим на будущее

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float uDiskRadiusWS;         // реальный радиус диска в мировых

out vec2 vLocal; // локальные координаты в пределах диска [-1..1] по XY

void main()
{
    // нормируем локальные XY в доли радиуса (так r=1 на кромке)
    vLocal = aPos.xy / max(uDiskRadiusWS, 1e-6);

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
