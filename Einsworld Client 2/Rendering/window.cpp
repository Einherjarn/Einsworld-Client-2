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

#include "shader.cpp"
#include "texture.cpp"
#include "vertex.cpp"


static void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

}

class Window {
private:
	Shader* shader = NULL;
public:
	GLFWwindow* window = NULL;
	Window() {
		if (!glfwInit()) {
			throw "ERROR: could not start GLFW3";
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		this->window = glfwCreateWindow(640, 480, "Einsworld", NULL, NULL);
		if (!this->window) {
			glfwTerminate();
			throw "ERROR: could not open window with GLFW3";
		}
		glfwMakeContextCurrent(this->window);
		std::cout << "Window created " << this->window << std::endl;

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw "Failed to initialize GLAD";
		}

		Shader shader = Shader(4, 1, "Rendering/Shaders/vertex_core.glsl", "Rendering/Shaders/fragment_core.glsl");
		Shader* shader_ptr = &shader;
		this->shader = shader_ptr;
		this->shader->use();
	}

	virtual ~Window() {
		glfwTerminate();
	}

	void update() {
		// setup drawables
		const unsigned int nverts = 3;
		Vertex verts[nverts];

		Vertex a = Vertex();
		a.position = glm::vec3(0.0f, 0.5f, 0.0f);
		verts[0] = a;

		Vertex b = Vertex();
		b.position = glm::vec3(0.5f, -0.5f, 0.0f);
		verts[1] = b;

		Vertex c = Vertex();
		c.position = glm::vec3(-0.5f, -0.5f, 0.0f);
		verts[2] = c;
		
		// the VBO is the data were sending to the gpu
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, nverts * sizeof(Vertex), verts, GL_DYNAMIC_DRAW);
		
		// the VAO describes the structure of the data were sending to the gpu
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		// color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);

		// wipe the drawing surface clear 
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		// draw points 0-3 from the currently bound VAO with current in-use shader 
		glDrawArrays(GL_TRIANGLES, 0, nverts);
		
		// update other events like input handling 
		glfwPollEvents();
		
		// put the stuff we've been drawing onto the display 
		glfwSwapBuffers(this->window);

		// clean up
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	int shouldClose() {
		return glfwWindowShouldClose(this->window);
	}
private:
};