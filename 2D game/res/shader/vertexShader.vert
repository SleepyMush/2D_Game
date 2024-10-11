#version 460 core
layout (location = 0)in vec3 position;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Transforms;

//Bool
uniform bool SwitchState;

layout(std430, binding = 0) buffer ModelMatrices 
{
     mat4 modelMatrices[];
};

void main()
{
    if (SwitchState)
    {
        mat4 ModelMatrix = modelMatrices[gl_InstanceID];
        gl_Position = Projection * View * ModelMatrix * vec4(position.x, position.y, position.z, 1.0);
    }
    else
    {
        gl_Position = Projection * View * Transforms * vec4(position.x, position.y, position.z, 1.0);
    }
}