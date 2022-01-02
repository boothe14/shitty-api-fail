#include "texture.h"
#include <stb/stb_image.h>
#include <stdbool.h>

texture_t *texture_new(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	texture_t *texture = malloc(sizeof(texture_t));
	// Assigns the type of the texture ot the texture object
	texture->type = texType;

	// Stores the width, height, and the number of color channels of the image
	GLsizei widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	if (bytes)
	{
		GLuint tx;
		glGenTextures(1, &tx);
		// Assigns the texture to a Texture Unit
		glActiveTexture(slot);
		glBindTexture(texType, tx);

		// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
		// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
		// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

		// Assigns the image to the OpenGL Texture object
		glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
		// Generates MipMaps
		glGenerateMipmap(texType);

		// Deletes the image data as it is already in the OpenGL Texture object
		stbi_image_free(bytes);

		// Unbinds the OpenGL Texture object so that it can't accidentally be modified
		glBindTexture(texType, 0);

		texture->id = tx;
	}
	return texture;
}

void texture_assign(texture_t *texture, shader_t *shader, const char *uniform, GLuint unit)
{
	GLuint tex_unit = glGetUniformLocation(shader->id, uniform);
	shader_use(shader);
	glUniform1i(tex_unit, unit);
}

void texture_bind(texture_t *texture)
{
	glBindTexture(texture->type, texture->id);
}

void texture_unbind(texture_t *texture)
{
	glBindTexture(texture->type, 0);
}

void texture_delete(texture_t *texture)
{
	glDeleteTextures(1, &texture->id);
}