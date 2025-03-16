#ifndef SHADER_H
#define SHADER_H

#include "../lib/glad/glad.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Shader {
    GLuint program, vertex, fragment; 
};

struct Shader createShader(const char* fragPath, const char* vertpath); 

void useShader(struct Shader self);

#endif // SHADER_H
