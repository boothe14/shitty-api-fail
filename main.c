#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <hmath/HandmadeMath.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "shader.h"

bool running = true;

#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "texture.h"
#include "shader.h"
#include <stb/stb_image.h>

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("larn opengl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    glViewport(0, 0, 800, 800);

    shader_t *shader = shader_new("../shaders/default.vert", "../shaders/default.frag");
    shader_use(shader);

    vao_t* vao = vao_new();
    vao_bind(vao);

    vbo_t* vbo = vbo_new(vertices, sizeof(vertices));
    ebo_t* ebo = ebo_new(indices, sizeof(indices));

    vao_link_attrib(vbo, 0, 3, GL_FLOAT, 8*sizeof(float), (void*)0);
    vao_link_attrib(vbo, 1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float)));
    vao_link_attrib(vbo, 2, 2, GL_FLOAT, 8*sizeof(float), (void*)(6*sizeof(float)));

    vao_unbind(vao);
    vbo_unbind(vbo);
    ebo_unbind(ebo);

    texture_t* tex = texture_new("../res/image.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texture_assign(tex, shader, "tex0", 0);

    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        shader_use(shader);
        texture_bind(tex);
        vao_bind(vao);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        SDL_GL_SwapWindow(window);
    }

    return 0;
}