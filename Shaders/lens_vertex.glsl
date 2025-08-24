#version 330 core
layout(location = 0) in vec3 aPos;   // ���� � ��������� XY
layout(location = 1) in vec2 aTex;   // �� �����������; ������� �� �������

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float uDiskRadiusWS;         // �������� ������ ����� � �������

out vec2 vLocal; // ��������� ���������� � �������� ����� [-1..1] �� XY

void main()
{
    // ��������� ��������� XY � ���� ������� (��� r=1 �� ������)
    vLocal = aPos.xy / max(uDiskRadiusWS, 1e-6);

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
