#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include "shader.h"

typedef struct {
    GLuint id;
    GLenum type;
} texture_t;

texture_t* texture_new(const char* image_path, GLenum texture_type, GLenum slot, GLenum format, GLenum pixel_type);
void texture_assign(texture_t* texture, shader_t* shader, const char* uniform, GLuint unit);
void texture_bind(texture_t* texture);
void texture_unbind(texture_t* texture);
void texture_delete(texture_t* texture);

typedef texture_t Texture;

#endif