#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

// glm stuff..
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "shader.cpp"

class Material {
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffusetex, GLint speculartex) {
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->diffusetex = diffusetex;
		this->speculartex = speculartex;
	}

	~Material() {

	}

	void sendtoshader(Shader& program) {
		/*
		program.setVec3f(this->ambient, "material.ambient");
		program.setVec3f(this->diffuse, "material.diffuse");
		program.setVec3f(this->specular, "material.specular");
		program.set1i(this->diffusetex, "material.diffusetex");
		program.set1i(this->speculartex, "material.speculartex");
		*/
	}

private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffusetex;
	GLint speculartex;
};