#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>

typedef struct {
    GLuint id;
} shader_t;

shader_t* shader_new(const char* vertex_shader_path, const char* fragment_file_path);
void shader_delete(shader_t* shader);
void shader_use(shader_t* shader);

typedef shader_t Shader;

#endif