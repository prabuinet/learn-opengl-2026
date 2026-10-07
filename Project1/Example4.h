#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>
#include <utility>
#include <string>
#include "Shader.h"

class Example4
{
private:
	float vertices[32] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int ebo = 0;
	unsigned int texture1, texture2;

	std::unique_ptr<Shader> shader;

	std::tuple<unsigned int, unsigned int, unsigned int> CreateVertexBufferAndArrayObjects();

public:
	void Init();
	void Draw();
	void Destroy();
};

