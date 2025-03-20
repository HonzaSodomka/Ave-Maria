#version 430 core

// Input from vertex shader
in vec2 TexCoords;        // Texture coordinates

// Uniforms
//uniform vec3 ambient;
uniform vec3 diffuse;
//uniform vec3 specular;

// Texture (if applicable)
uniform sampler2D texture_diffuse;

// Output
out vec4 FragColor;

void main()
{
    vec3 result = diffuse;
    FragColor = vec4(result, 1.0);
}