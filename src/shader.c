#include "shader.h"

static void logfail(GLuint shader, const char *adverb, const char *path) {
    GLint loglen;
    GLchar logtext[1024];
    glGetShaderInfoLog(shader, 1024, &loglen, logtext);

    fprintf(stderr, "error %s shader at %s:\n%s", adverb, path, logtext);
    exit(1);
}

static GLuint compileShader(const char* shaderPath, GLenum shaderType) {
    FILE *shaderFile = fopen(shaderPath, "rb");
    char *shaderSource;
    long len;

    if (shaderFile == NULL) {
        fprintf(stderr, "error loading shader at %s\n", shaderPath);
        exit(1);
    }

    fseek(shaderFile, 0L, SEEK_END);
    len = ftell(shaderFile);
    assert(len > 0);
    rewind(shaderFile);
    shaderSource = calloc(1, len);
    assert(shaderSource != NULL);
    fread(shaderSource, len, 1, shaderFile);
    fclose(shaderFile);        

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar * const *) &shaderSource, (const GLint *) &len);
    glCompileShader(shader);


    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (compiled != GL_TRUE) {
    logfail(shader, "compiling", shaderPath);
    }

    free(shaderSource);
    return shader;
}

GLuint createShaderProgam(const char* vertPath, const char* fragPath) {
    GLuint shaderProgram = glCreateProgram();

    GLuint vertShader = compileShader(vertPath, GL_VERTEX_SHADER);
    GLuint fragShader = compileShader(fragPath, GL_FRAGMENT_SHADER);

    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    GLint linked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE)
    {
        GLint loglen;
        GLchar logtext[1024];
        glGetProgramInfoLog(shaderProgram, 1024, &loglen, logtext);

        fprintf(stderr, "error linking shaders :\n%s", logtext);
        exit(1);
    }
    return shaderProgram;
}

void useShaderProgram(GLuint shaderProgram) {
    glUseProgram(shaderProgram);    
}

