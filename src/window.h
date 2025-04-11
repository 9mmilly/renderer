#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdlib.h>

struct Window {
    GLFWwindow* window;
};

struct Window windowInit(const unsigned int screenWidth, const unsigned screenHeight);
