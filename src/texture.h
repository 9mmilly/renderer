#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdbool.h>
#include <stdlib.h>

#include "../lib/glad/glad.h"

struct Texture {
    GLuint handle;
};

struct Texture createTexture(const char *path);

void useTexture(struct Texture *self);
void deleteTexture(struct Texture *self);

#endif // TEXTURE_H
