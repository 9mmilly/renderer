#ifndef SHADER_H
#define SHADER_H

#include "../lib/glad/glad.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Shader {
    GLuint program;
    GLuint vertex;
    GLuint fragment;
};

struct Shader createShader(const char* vertPath, const char* fragPath);

void useShader(struct Shader *self);
void deleteShader(struct Shader *self);

#endif // SHADER_H
