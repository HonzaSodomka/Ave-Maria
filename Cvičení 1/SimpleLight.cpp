#include "SimpleLight.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"


#include "Camera.h"
#include "Mesh.h"
#include "OBJLoader.h"
#include "Shader.h"

SimpleLight::SimpleLight(glm::vec3 position, float intensity) : position(position), intensity(intensity)
{
}

void SimpleLight::render(Camera& camera)
{
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(0.3f));

	shader.activate();
	shader.setUniform("transform", model);
	shader.setUniform("projection", camera.getProjectionMatrix());
	shader.setUniform("view", camera.getViewMatrix());
	mesh.draw(shader);
}
