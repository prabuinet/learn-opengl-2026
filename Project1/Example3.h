#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>
#include <string>
#include <memory>

#include "Shader.h"

class Example3
{
private:
	float vertices[18] = {
		// position          // color
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
	};

	unsigned int vao = 0;
	unsigned int vbo = 0;

	std::unique_ptr<Shader> shader;

	std::pair<unsigned int, unsigned int> CreateVertexBufferAndArrayObjects();

public:
	void Init();
	void Draw();
	void Destroy();
};

