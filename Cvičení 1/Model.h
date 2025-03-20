#pragma once
#include <filesystem>
#include <vector>

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include "Mesh.h";

class Model
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	std::vector<Mesh> meshes;
	Model(const std::filesystem::path& filename);

	void render(Shader& shader);
};

