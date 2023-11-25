/*******************************************
    Written by Robert Parry [RJP] - 2023    
*******************************************/

#version 330 core

in vec3 fragColor; // Receive color from the vertex shader

out vec4 finalColor;

void main() {
    finalColor = vec4(fragColor, 1.0); // Simple color pass-through
}
