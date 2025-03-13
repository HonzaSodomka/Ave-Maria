#pragma once

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Camera
{
public:

	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Right;
	glm::vec3 Up; // camera local UP vector

	GLfloat Yaw = -90.0f;
	GLfloat Pitch = 30.0f;
	GLfloat Roll = 30.0f;

	GLfloat FOV = 60.0f;

	// Camera options
	GLfloat MovementSpeed;
	GLfloat SprintFactor;
	GLfloat MouseSensitivity;

	// Constructor
	Camera(glm::vec3 position);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void onKeyboardEvent(GLFWwindow* window, GLfloat deltaTime);
	void onMouseEvent(GLfloat xoffset, GLfloat yoffset, GLboolean constraintPitch);

private:
	void updateCameraVectors();
};
