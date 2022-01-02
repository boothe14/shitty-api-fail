#include "vbo.h"

#include <stdlib.h>

vbo_t* vbo_new(GLfloat* vertices, GLsizeiptr size)
{
    vbo_t* vbo = malloc(sizeof(vbo_t));
    glGenBuffers(1, &vbo->id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

void vbo_bind(vbo_t* vbo)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
}

void vbo_unbind(vbo_t* vbo)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo_delete(vbo_t* vbo)
{
    glDeleteBuffers(1, &vbo->id);
}