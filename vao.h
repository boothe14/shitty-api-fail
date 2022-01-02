#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include <vbo.h>

typedef struct {
    GLuint id;
} vao_t;

vao_t* vao_new();
void vao_bind(vao_t* vao);
void vao_unbind(vao_t* vao);
void vao_link_attrib(vbo_t* vbo, int layout, int size, GLenum type, GLsizei stride, const void* pointer);
void vao_delete(vao_t* vao);

typedef vao_t VAO;

#endif