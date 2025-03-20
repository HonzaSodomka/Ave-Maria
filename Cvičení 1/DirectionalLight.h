#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"


#include "Camera.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "Shader.h"

class DirectionalLight
{
public:
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 ambient{ 0.2f };
	glm::vec3 diffusion{ 0.8f };
	glm::vec3 specular{ 1.0f };
	float intensity;

	DirectionalLight(glm::vec3 position, glm::vec3 direction, float intensity);
	void render(Camera& camera);

private:
	Shader shader{ "./assets/shaders/light.vert", "./assets/shaders/light.frag" };
	Mesh mesh = OBJLoader{ "./assets/obj/cube_triangles" }.getMesh();
};

