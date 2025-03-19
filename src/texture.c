#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb/stb_image.h"

#include "texture.h"

GLuint createTexture(const char *path) {

    // creating and binding texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); 

    // setting texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // setting texture filtering (the minifying filter uses the mipmaps)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // image data is loaded into memory
    int width, height, numChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &numChannels, 0);

    // image data gets applied to texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return texture;
}

