#pragma once

#include <string>
#include <filesystem>
#include <iostream>

#include <glm/glm.hpp> 
#include <glm/ext.hpp>
#include <GL/glew.h> 

class Shader {
public:
	// you can add more constructors for pipeline with GS, TS etc.
	Shader(void) = default; //does nothing
	Shader(const std::filesystem::path& VS_file, const std::filesystem::path& FS_file);

	void activate(void) { glUseProgram(ID); };
	void deactivate(void) { glUseProgram(0); };
	void clear(void) {
		deactivate();
		glDeleteProgram(ID);
		ID = 0;
	}

	// set uniform according to name 
	// https://docs.gl/gl4/glUniform
	void setUniform(const std::string& name, const float val);
	void setUniform(const std::string& name, const int val);   
	void setUniform(const std::string& name, const glm::vec3 val);
	void setUniform(const std::string& name, const glm::vec4 val);
	void setUniform(const std::string& name, const glm::mat3 val);
	void setUniform(const std::string& name, const glm::mat4 val);

	//...

	GLuint ID{ 0 }; // default = 0, empty shader
private:
	std::string getShaderInfoLog(const GLuint obj); 
	std::string getProgramInfoLog(const GLuint obj);

	GLuint compile_shader(const std::filesystem::path& source_file, const GLenum type);
	GLuint link_shader(const std::vector<GLuint> shader_ids);
	std::string textFileRead(const std::filesystem::path& filename);
};

