#ifndef COLOR_H
#define COLOR_H

#include <GL/GL.h>
#include<string>

using namespace std;

/*
Clase color. Define un color en RGB en decimal.
*/
class Color {
private:
	/*Valores rgb para los colores.*/
	GLfloat r, g, b;

public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase color, dado un string con el nombre de un color, devuelve ese color.*/
	Color(string color) {
		if (color.compare("red") == 0) {
			this->r = 1.0f;
			this->g = 0.0f;
			this->b = 0.0f;
		}
		else if (color.compare("green") == 0) {
			this->r = 0.0f;
			this->g = 1.0f;
			this->b = 0.0f;
		}
		else if (color.compare("blue") == 0) {
			this->r = 0.0f;
			this->g = 0.0f;
			this->b = 1.0f;
		}
		else if (color.compare("cyan") == 0) {
			this->r = 0.0f;
			this->g = 1.0f;
			this->b = 1.0f;
		}
		else if (color.compare("yellow") == 0) {
			this->r = 1.0f;
			this->g = 1.0f;
			this->b = 0.0f;
		}
		else if (color.compare("magenta") == 0) {
			this->r = 1.0f;
			this->g = 0.0f;
			this->b = 1.0f;
		}
		else if (color.compare("white") == 0) {
			this->r = 1.0f;
			this->g = 1.0f;
			this->b = 1.0f;
		}
		else if (color.compare("purple") == 0) {
			this->r = 0.5f;
			this->g = 0.0f;
			this->b = 1.0f;
		}
		else if (color.compare("orange") == 0) {
			this->r = 0.9019f;
			this->g = 0.3725f;
			this->b = 0.0f;
		}
		else if (color.compare("brown") == 0) {
			this->r = 0.5529f;
			this->g = 0.2862f;
			this->b = 0.1451f;
		}
		else if (color.compare("bondiBlue") == 0) {
			this->r = 0.0f;
			this->g = 0.5843f;
			this->b = 0.7137f;
		}
		else {
			this->r = 0.0f;
			this->g = 0.0f;
			this->b = 0.0f;
		}
	}

	/*Constructora de la clase color, dado un número del 0 al 11, devuelve un color diferente.*/
	Color(int color) {
		if (color == 0) {
			this->r = 1.0f;
			this->g = 0.0f;
			this->b = 0.0f;
		}
		else if (color == 1) {
			this->r = 0.0f;
			this->g = 1.0f;
			this->b = 0.0f;
		}
		else if (color == 2) {
			this->r = 0.0f;
			this->g = 0.0f;
			this->b = 1.0f;
		}
		else if (color == 3) {
			this->r = 0.0f;
			this->g = 1.0f;
			this->b = 1.0f;
		}
		else if (color == 4) {
			this->r = 1.0f;
			this->g = 1.0f;
			this->b = 0.0f;
		}
		else if (color == 5) {
			this->r = 1.0f;
			this->g = 0.0f;
			this->b = 1.0f;
		}
		else if (color == 6) {
			this->r = 1.0f;
			this->g = 1.0f;
			this->b = 1.0f;
		}
		else if (color == 7) {
			this->r = 0.5f;
			this->g = 0.0f;
			this->b = 1.0f;
		}
		else if (color == 8) {
			this->r = 0.9019f;
			this->g = 0.3725f;
			this->b = 0.0f;
		}
		else if (color == 9) {
			this->r = 0.5529f;
			this->g = 0.2862f;
			this->b = 0.1451f;
		}
		else if (color == 10) {
			this->r = 0.0f;
			this->g = 0.5843f;
			this->b = 0.7137f;
		}
		else {
			this->r = 0.0f;
			this->g = 0.0f;
			this->b = 0.0f;
		}
	}

	/*Constructora de la clase color.*/
	Color(GLfloat r, GLfloat g, GLfloat b){
		this->r = r;
		this->g = g;
		this->b = b;
	}

	/**********
	 *Getters.*
	 **********/

	/*Devuelve el valor r de color.*/
	GLfloat getR() {
		return this->r;
	}

	/*Devuelve el valor g de color.*/
	GLfloat getG() {
		return this->g;
	}

	/*Devuelve el valor b de color.*/
	GLfloat getB() {
		return this->b;
	}

};

#endif