#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>
#include <string>

class Example1
{
private: 
	float vertices[9] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int shaderProgram = 0;

	const char* vertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vectorColor;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vectorColor = vec4(0.5, 0.0, 0.0, 1.0);
}
	)glsl";

	const char* fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;
in vec4 vectorColor;
uniform vec4 ourColor;
void main()
{
	// FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	// FragColor = vectorColor;
	FragColor = ourColor;
}
)glsl";

	unsigned int CompileVertexShader();
	unsigned int CompileFragmentShader();
	unsigned int CreateShaderProgram();

	std::pair<unsigned int, unsigned int> CreateVertexBufferAndArrayObjects();
	int vertexColorLocation;

public:
	void Init();
	void Draw();
	void Destroy();
};

