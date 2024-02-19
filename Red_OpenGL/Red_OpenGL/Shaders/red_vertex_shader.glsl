#version 330 core

layout(location = 0) in vec3 inPosition;

uniform mat4 projectionMatrix;  
uniform mat4 viewMatrix;        
uniform mat4 modelMatrix;       

out vec4 fragPosition;

void main()
{
    mat4 pvmMatrix = projectionMatrix * viewMatrix * modelMatrix;

    gl_Position = pvmMatrix * vec4(inPosition, 1.0);

    fragPosition = modelMatrix * vec4(inPosition, 1.0);
}
