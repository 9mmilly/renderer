#ifndef SHADER_H
#define SHADER_H

#include "../lib/glad/glad.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

GLuint createShaderProgam(const char* fragPath, const char* vertpath); 

#endif // SHADER_H
