#include "vao.h"
#include "vbo.h"

#include <stdlib.h>

vao_t* vao_new()
{
    vao_t* vao = malloc(sizeof(vao_t));
    glGenVertexArrays(1, &vao->id);
    return vao;
}

void vao_bind(vao_t* vao)
{
    glBindVertexArray(vao->id);
}

void vao_unbind(vao_t* vao)
{
    glBindVertexArray(0);
}

void vao_link_attrib(vbo_t* vbo, int layout, int size, GLenum type, GLsizei stride, const void* pointer)
{
    vbo_bind(vbo);

    glVertexAttribPointer(layout, size, type, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(layout);

    vbo_unbind(vbo);
}

void vao_delete(vao_t* vao)
{
    glDeleteVertexArrays(1, &vao->id);
}