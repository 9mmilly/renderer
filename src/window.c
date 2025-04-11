#include "window.h"

struct Window windowInit(const unsigned int screenWidth, const unsigned screenHeight) {

    struct Window self;
    
    if (!glfwInit())
        exit(EXIT_FAILURE);

    self.window = glfwCreateWindow(screenHeight, screenHeight, "renderer", NULL, NULL);
    if (!self.window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(self.window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    return self;
}
