#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

typedef struct {
    GLuint id;
} vbo_t;

vbo_t* vbo_new(GLfloat* vertices, GLsizeiptr size);
void vbo_bind(vbo_t* vbo);
void vbo_unbind(vbo_t* vbo);
void vbo_delete(vbo_t* vbo);

typedef vbo_t VBO;

#endif