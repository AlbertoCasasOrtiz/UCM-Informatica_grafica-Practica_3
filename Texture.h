#ifndef TEXTURE_H
#define TEXTURE_H


#include "TextureLoader.h"

/*
Clase texture. Define texturas y sus parámetros.
*/
class Texture {
private:
	/*Array de texturas.*/
	GLuint texturas[6];
	/*Buffer con imagen.*/
	unsigned char* texture;

public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase textura.*/
	Texture() {
		//Leer en la variable texture, el archivo que contiene la imagen
		//usando la clase lectora

		GLuint width = 1, height = 1;
		glGenTextures(6, texturas);
		texture = loadBMPRaw("image.bmp", width, height, false);
		glBindTexture(GL_TEXTURE_2D, texturas[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	/*Destructora de la clase textura.*/
	~Texture() {
		glDeleteTextures(5, &texturas[1]);
		delete texture;
	}


	/**********
	 *Getters.*
	 **********/

	/*Devuelve la textura t.*/
	GLuint getTexture(GLint t) {
		return texturas[t];
	}
};



#endif