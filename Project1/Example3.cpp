#include <imgui.h>

#include "Example3.h"

std::pair<unsigned int, unsigned int> Example3::CreateVertexBufferAndArrayObjects() {
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

    // define buffer structure, define the structure/layout of vertex attribute 0 (Positions)
    glVertexAttribPointer(
        0,                  // attribute location
        3,                  // number of components
        GL_FLOAT,           // component type
        GL_FALSE,           // don't normalize
        6 * sizeof(float),  // stride (how many bytes it should move forward in the buffer to find the next vertex)
        (void*)0            // offset
    );
    // Enable position attribute 0
    glEnableVertexAttribArray(0);

    // define buffer structure, define the structure/layout of vertex attribute 1 (Colors)
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    // Enable color attribute
    glEnableVertexAttribArray(1);

    // the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object 
    // so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    return { VBO, VAO };
}

void Example3::Init()
{
    shader = std::make_unique<Shader>("shaders/example3.shader");
    auto [VBO, VAO] = CreateVertexBufferAndArrayObjects();
    vbo = VBO;
    vao = VAO;
}

void Example3::Draw()
{
    static float offset = 0.0f;
    ImGui::SliderFloat("Offset", &offset, -1.0, 1.0);

    //glUseProgram(shaderProgram);
    shader->use();
    shader->setFloat("offset", offset);
    glBindVertexArray(vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Example3::Destroy()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);    
}
