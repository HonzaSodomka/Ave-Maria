#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 position, glm::vec3 direction, float intensity) : position(position), direction(direction), intensity(intensity)
{
}

void DirectionalLight::render(Camera& camera)
{
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(0.3f));

	shader.activate();
	shader.setUniform("projection", camera.getProjectionMatrix());
	shader.setUniform("view", camera.getViewMatrix());
	shader.setUniform("transform", model);
	mesh.draw(shader);
}