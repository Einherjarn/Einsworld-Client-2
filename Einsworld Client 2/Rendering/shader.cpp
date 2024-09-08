#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <glfw3.h>
#include <SOIL2.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class Shader {
private:
	unsigned int id;
	const int vermajor;
	const int verminor;
public:
	Shader(const int vermajor, const int verminor, std::string vertexfile, std::string fragmentfile)
		: vermajor(vermajor), verminor(verminor) {
		GLuint vertexShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexfile);
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentfile);
		this->linkProgram(vertexShader, fragmentShader);

		// delete the shader objects once we've linked them into the program object; we no longer need them anymore
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	~Shader() {

	}

	void use() {
		glUseProgram(this->id);
	}

	void unuse() {
		glUseProgram(0);
	}
private:
	std::string loadShaderSource(std::string filename) {
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;

		in_file.open(filename);
		if (in_file.is_open()) {
			while (std::getline(in_file, temp)) {
				src += temp + "\n";
			}
		}
		else {
			std::string exception = "shader.cpp loadShaderSource() failed: " + filename;
			throw std::runtime_error(exception);
		}
		in_file.close();
		std::string version = std::to_string(this->vermajor) + std::to_string(this->verminor) + "0";
		src.replace(src.find("#version"), 12, "#version " + version);
		return src;
	}

	GLuint loadShader(GLenum type, std::string filename) {
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadShaderSource(filename);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cerr << "shader.cpp loadshader() failed: " << filename << std::endl;
			std::cout << infoLog << "\n";
			throw "Shader compilation failed";
		}
		return shader;
	}

	void linkProgram(GLuint vertexShader, GLuint fragmentShader) {
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();
		glAttachShader(this->id, vertexShader);
		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cerr << "shader.cpp linkprogram() failed" << std::endl;
			std::cout << infoLog << "\n";
			throw "Shader linking failed";
		}
		glUseProgram(this->id);
	}
};
