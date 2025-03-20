#pragma once
#include <string>
#include "Model.h"
#include "Logger.h"
#include "OBJLoader.h"

Model::Model(const std::filesystem::path& filename)
{
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	meshes = std::vector<Mesh>{};

	auto suffix = filename.extension().string();
	Logger::debug(suffix);

	if (suffix == ".obj") {
		auto loader = OBJLoader(filename);

		for (Mesh mesh : loader.submeshes) {
			meshes.push_back(mesh);
		}
	}
	else {
		Logger::error("Unrecognized file extension: " + suffix);
	};
}

void Model::render(Shader& shader)
{
	for (Mesh mesh : meshes)
	{
		shader.activate();
		shader.setUniform("material.ambient", mesh.material.ambient);
		shader.setUniform("material.diffuse", mesh.material.diffuse);
		shader.setUniform("material.specular", mesh.material.specular);
		shader.setUniform("material.shininess", mesh.material.shininess);
		mesh.draw(shader);

		//Logger::warning(mesh.material.name + " (" + std::to_string(mesh.material.diffuse[0]) + ", " + std::to_string(mesh.material.diffuse[1]) + ", " + std::to_string(mesh.material.diffuse[2]) + ")");
	}
}
