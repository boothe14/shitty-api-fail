#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

typedef struct {
    GLuint id;
} ebo_t;

ebo_t* ebo_new(GLuint* indices, GLsizeiptr size);
void ebo_bind(ebo_t* ebo);
void ebo_unbind(ebo_t* ebo);
void ebo_delete(ebo_t* ebo);

typedef ebo_t EBO;

#endif