#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "shader.h"
#include "texture.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "opengl moment", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    //vertex buffer object creation
    float positions[] = {
         0.5f,  0.5f, 0.0f,     1.0f, 1.0f, // 0
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f, // 1
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, // 2
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f  // 3
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    struct Shader shader = createShader("res/shader/vert.glsl", "res/shader/frag.glsl");
    GLuint texture = createTexture("res/texture/beetle.png");

    //main loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);
        useShader(shader);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
