/*******************************************
    Written by Robert Parry [RJP] - 2023    
    Refer to red_main.cpp for the license
*******************************************/

#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 fragColor; // Pass color to the fragment shader

uniform mat4 model; // Model matrix
uniform mat4 view;  // View matrix
uniform mat4 projection; // Projection matrix

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    fragColor = color; // Pass color to the fragment shader
}
