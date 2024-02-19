#version 330 core

in vec4 fragPosition;

out vec4 fragColor;

void main()
{
    vec3 color = normalize(vec3(fragPosition));

    fragColor = vec4(color, 1.0);
}