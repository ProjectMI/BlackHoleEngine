#version 330 core

in vec3 vColor;
out vec4 FragColor;

void main()
{
    vec2 uv = gl_PointCoord - vec2(0.5);
    float dist = dot(uv, uv);
    float alpha = smoothstep(0.25, 0.20, dist); // м€гкий край

    if (alpha < 0.01)
        discard;

    FragColor = vec4(vColor, alpha);
}
