#include "ebo.h"

#include <stdlib.h>

ebo_t* ebo_new(GLuint* indices, GLsizeiptr size)
{
    ebo_t* ebo = malloc(sizeof(ebo_t));

    glGenBuffers(1, &ebo->id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ebo_bind(ebo_t* ebo)
{
    glBindBuffer(1, ebo->id);
}

void ebo_unbind(ebo_t* ebo)
{
    glBindBuffer(1, 0);
}

void ebo_delete(ebo_t* ebo)
{
    glDeleteBuffers(1, &ebo->id);
}