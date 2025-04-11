#include "../lib/glad/glad.h"
#include "../lib/cglm/cglm.h"

#include "shader.h"
#include "texture.h"
#include "window.h"
#include <GLFW/glfw3.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const float FOV = 45.0f;

int main(void)
{
    struct Window window = windowInit(SCR_WIDTH, SCR_HEIGHT);
    
    float positions[] = {
         0.5f,  0.0f,  0.5f,    5.0f, 0.0f, // 0
         0.5f,  0.0f, -0.5f,    0.0f, 0.0f, // 1
        -0.5f,  0.0f,  0.5f,    0.0f, 0.0f, // 2
        -0.5f,  0.0f, -0.5f,    5.0f, 0.0f, // 3
         0.0f,  0.7f,  0.0f,    2.5f, 5.0f  // 4
    };

    GLuint indices[] = {
        0, 1, 2,
        1, 2, 3,
        0, 1, 4,
        0, 2, 4,
        1, 3, 4,
        2, 3, 4
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
    struct Texture texture = createTexture("res/texture/glup.png");

    float rotation = 0.0f;
    double previousTime = glfwGetTime();
    
    glEnable(GL_DEPTH_TEST);

    //main loop
    while (!glfwWindowShouldClose(window.window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        useShader(&shader);

        mat4 model, view, proj;
        glm_mat4_identity(model);
        glm_mat4_identity(view);
        glm_mat4_identity(proj);

        double currentTime = glfwGetTime();
        if (currentTime - previousTime >= 1 / 60) {
            rotation += 0.01f;
            previousTime = currentTime; 
        }

        glm_spin(model, rotation, (vec3) {0.0f, 1.0f, 0.0f});
        glm_translate(view, (vec3) {0.0f, -0.40f, -2.0f});
        glm_perspective(45.0f, (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f, proj);

        int modelLocation = glGetUniformLocation(shader.program, "model"); 
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, model[0]);
        int viewLocation = glGetUniformLocation(shader.program, "view"); 
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, view[0]);
        int projLocation = glGetUniformLocation(shader.program, "proj"); 
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, proj[0]);
        
        useTexture(&texture);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, NULL);

        glfwSwapBuffers(window.window);

        glfwPollEvents();
    }

    // cleanup
    deleteShader(&shader);
    deleteTexture(&texture);
    
    glfwTerminate();
    return 0;
}
