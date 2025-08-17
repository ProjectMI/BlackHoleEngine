#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 vColor;

float hash(vec3 p, vec3 seed)
{
    return fract(sin(dot(p, seed)) * 43758.5453);
}

// Преобразование температуры в цвет (очень упрощённая аппроксимация)
vec3 temperatureToRGB(float T)
{
    vec3 color;

    if (T < 4000.0)          // красные
        color = mix(vec3(1.0, 0.4, 0.2), vec3(1.0, 0.6, 0.4), (T - 3000.0) / 1000.0);
    else if (T < 6000.0)     // жёлто-белые
        color = mix(vec3(1.0, 0.7, 0.5), vec3(1.0, 1.0, 0.9), (T - 4000.0) / 2000.0);
    else                      // голубые
        color = mix(vec3(0.7, 0.8, 1.0), vec3(0.5, 0.7, 1.0), (T - 6000.0) / 4000.0);

    return color;
}

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    // Размер звезды
    float h = hash(aPos, vec3(12.9898, 78.233, 37.719));
    gl_PointSize = 1.5 + h * 2.0;

    // Температура: 3000K – 10000K
    float temp = 3000.0 + hash(aPos, vec3(93.9898, 18.233, 12.345)) * 7000.0;
    vColor = temperatureToRGB(temp);
}
