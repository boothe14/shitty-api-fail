#include "shader.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

shader_t* shader_new(const char* vertex_shader_path, const char* fragment_file_path)
{
    	/* Load Vertex Shader File */
    shader_t* shader = malloc(sizeof(shader_t));

    char* vertexcode;
    char* fragmentcode;
    GLuint vertex;
    GLuint fragment;
    GLuint program;

	FILE* VertexShaderStream;
	if( (VertexShaderStream = fopen(vertex_shader_path, "r")) == NULL ){
		printf("Shaders: Unable to open %s\n", vertex_shader_path);
		printf("Shaders: Terminating...\n");
	}

	FILE *VertexErrorLog;
	if( (VertexErrorLog = fopen("shader.log", "w")) == NULL ){
		printf("Shaders: Unable to open %s\n", "shader.log");
		printf("Shaders: Terminating...\n");
	}
	
	fseek(VertexShaderStream, 0, SEEK_END); /* set pointer at the end of file */
	long fsize = ftell(VertexShaderStream); /* get file size */
	rewind(VertexShaderStream); /* set pointer and the beginning of a file */

	int vlength = fsize;

	vertexcode = malloc(fsize + 1);
	vertexcode[fsize] = 0;

	int i = 0;
	while(true){
		if( (vertexcode[i] = fgetc(VertexShaderStream)) == EOF ){
			break;
		}

		i++;
	}

	vertexcode[i] = 0;
	fclose(VertexShaderStream);

	/* Same thing for Fragment Shader */
	FILE *FragmentShaderStream;
	if( (FragmentShaderStream = fopen(fragment_file_path, "r")) == NULL ){
		printf("Shaders: Cannot open %s. \n Terminating...\n", fragment_file_path);
		fclose(FragmentShaderStream);
	}

	fseek(FragmentShaderStream, 0, SEEK_END);
	fsize = ftell(FragmentShaderStream);
	rewind(FragmentShaderStream);

	int flength = fsize;

	fragmentcode = malloc(fsize + 1);
	i = 0;
	while(true){
		if( (fragmentcode[i] = fgetc(FragmentShaderStream)) == EOF ){
			break;
		}

		i++;
	}

	fragmentcode[i] = 0;
	fclose(FragmentShaderStream);

	/* Creating shader objects */
	if( (vertex = glCreateShader(GL_VERTEX_SHADER)) == 0 ){
		printf("Shaders: Error creating vertex shader object!\n");
	}

	if( (fragment = glCreateShader(GL_FRAGMENT_SHADER)) == 0 ){
		printf("Shaders: Error creating fragment shader object!\n");
	}

	const char *VertexShaderPointer = vertexcode;
	const char *FragmentShaderPointer = fragmentcode;

	/* Attaching Shaders */
	glShaderSource(vertex, 1, &VertexShaderPointer, &vlength);
	glShaderSource(fragment, 1, &FragmentShaderPointer, &flength);

	/* Compiling Shaders */
	glCompileShader(vertex);
	glCompileShader(fragment);

	/* Error checking for compilation */
	GLint VertexShaderLogLength, vlen, FragmentShaderLogLength, flen;
	
	glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &VertexShaderLogLength);
	glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &FragmentShaderLogLength);

	if( VertexShaderLogLength > 1 ){
		GLchar *VertexCompilerLog = (GLchar*)malloc(VertexShaderLogLength * 2);
		glGetShaderInfoLog(vertex, VertexShaderLogLength, &vlen, VertexCompilerLog);
		printf("Shaders: Vertex shader error! Check shader.log for more info.\n");
		fprintf(VertexErrorLog, "%s", VertexCompilerLog);
		free(VertexCompilerLog);
	}

	if( FragmentShaderLogLength > 1){
		GLchar *FragmentCompilerLog = (GLchar*)malloc(FragmentShaderLogLength * 2);
		glGetShaderInfoLog(fragment, FragmentShaderLogLength, &flen, FragmentCompilerLog);
		printf("Shaders: Fragment shader error! Check shader.log for more info. \n");
		fprintf(VertexErrorLog, "%s", FragmentCompilerLog);
		free(FragmentCompilerLog);
	}

	/* Link the program */
	if( (program = glCreateProgram()) == 0 ){
		printf("Shaders: Creating program object failed.\n");
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);

	/* Error checking for linking */
	GLint linked, ProgramLogLength, plen;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(linked == GL_TRUE){
		/* ok */
	}else{
		printf("Shaders: Shader program linking error.\n");
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &ProgramLogLength);

		GLchar *ProgramCompilerLog = (GLchar*)malloc(sizeof(ProgramLogLength));
		glGetProgramInfoLog(program, ProgramLogLength, &plen, ProgramCompilerLog);
		fprintf(VertexErrorLog, "%s", ProgramCompilerLog);
		free(ProgramCompilerLog);
	}

    shader->id = program;

	free(vertexcode);
	free(fragmentcode);
	fclose(VertexErrorLog);
    return shader;
}

void shader_delete(shader_t* shader)
{
    glDeleteProgram(shader->id);
}

void shader_use(shader_t* shader)
{
    glUseProgram(shader->id);
}