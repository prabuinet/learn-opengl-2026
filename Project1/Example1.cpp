#include "Example1.h"
#include <imgui.h>


unsigned int Example1::CompileVertexShader() {
    int  success;
    char infoLog[512];

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return vertexShader;
}

unsigned int Example1::CompileFragmentShader() {
    int  success;
    char infoLog[512];

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return fragmentShader;
}

unsigned int Example1::CreateShaderProgram() {
    int  success;
    char infoLog[512];

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    auto vertexShader = CompileVertexShader();
    auto fragmentShader = CompileFragmentShader();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::pair<unsigned int, unsigned int> Example1::CreateVertexBufferAndArrayObjects() {
    unsigned int VBO, VAO;
    // create buffer 
    glGenBuffers(1, &VBO);

    // create vertex array
    glGenVertexArrays(1, &VAO);

    // use vertex array
    glBindVertexArray(VAO);

    // use buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // copy data to gpu-ram (internally it might just be copying (lazily) data into opengl managed buffer, not necessarily gpu ram)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // define buffer structure, define the structure/layout of vertex attribute 0
    glVertexAttribPointer(
        0,                  // attribute location
        3,                  // number of components
        GL_FLOAT,           // component type
        GL_FALSE,           // don't normalize
        3 * sizeof(float),  // stride (how many bytes it should move forward in the buffer to find the next vertex)
        (void*)0            // offset
    );

    // Enable vertex attribute 0
    glEnableVertexAttribArray(0);

    // the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object 
    // so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    return { VBO, VAO };
}

void Example1::Init()
{
    shaderProgram = CreateShaderProgram();
    auto [VBO, VAO] = CreateVertexBufferAndArrayObjects();
    vbo = VBO;
    vao = VAO;
    vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
}

void Example1::Draw()
{
    glUseProgram(shaderProgram);

    static ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;
    static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);

    ImGui::ColorEdit3("MyColor##1", (float*)&color, base_flags);
    
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    float redValue = (cos(timeValue) / 2.0f) + 0.5f;
    glUniform4f(vertexColorLocation, color.x, color.y, color.z, 1.0f);

    glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Example1::Destroy()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);    
    glDeleteProgram(shaderProgram);
}
