#version 430 core

// input vertex attributes

in vec3 aPos;   // position: MUST exist
in vec3 aColor; // any additional attributes are optional, any data type, etc.

out vec3 color; // optional output attribute

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    // Outputs the positions/coordinates of all vertices, MUST WRITE
    gl_Position = projection * view * transform * vec4(aPos, 1.0f);
    
    color = aColor; // copy color to output
}
