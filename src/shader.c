#include "shader.h"

static void logfail(GLuint shaderObject, const char *adverb, const char *path) {
    GLint loglen;
    GLchar logtext[1024];
    glGetShaderInfoLog(shaderObject, 1024, &loglen, logtext);

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

    GLuint shaderObject = glCreateShader(shaderType);
    glShaderSource(shaderObject, 1, (const GLchar * const *) &shaderSource, (const GLint *) &len);
    glCompileShader(shaderObject);


    GLint compiled;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compiled);

    if (compiled != GL_TRUE) {
    logfail(shaderObject, "compiling", shaderPath);
    }

    free(shaderSource);
    return shaderObject;
}

struct Shader createShader(const char* vertPath, const char* fragPath) {
    struct Shader self;
     self.program = glCreateProgram();

    self.vertex = compileShader(vertPath, GL_VERTEX_SHADER);
    self.fragment = compileShader(fragPath, GL_FRAGMENT_SHADER);

    glAttachShader(self.program, self.vertex);
    glAttachShader(self.program, self.fragment);
    glLinkProgram(self.program);

    GLint linked;
    glGetProgramiv(self.program, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE)
    {
        GLint loglen;
        GLchar logtext[1024];
        glGetProgramInfoLog(self.program, 1024, &loglen, logtext);

        fprintf(stderr, "error linking shaders :\n%s", logtext);
        exit(1);
    }
    return self;
}

void useShader(struct Shader *self) {
    glUseProgram(self->program);    
}

void deleteShader(struct Shader *self) {
    glDeleteShader(self->vertex);
    glDeleteShader(self->fragment);
    glDeleteShader(self->program);
}
