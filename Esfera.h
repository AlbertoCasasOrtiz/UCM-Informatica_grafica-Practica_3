#ifndef ESFERA_H
#define ESFERA_H

#include "ObjetoCuadrico.h"
#include "Color.h"

/*
Clase esfera. Crea una esfera.
*/
class Esfera : public ObjetoCuadrico {
private:
	/*Objeto cuadratico generado para la esfera.*/
	GLUquadricObj *quadratic;

	/*Radio de la esfera.*/
	GLfloat radius;

	/*Partes que forman la esfera.*/
	GLint slices, stacks;

	/*Color de la esfera.*/
	Color * color;
public:

	/****************/
	/*Constructoras.*/
	/****************/

	/*Constructora de la clase esfera.*/
	Esfera(GLfloat radius, GLint slices, GLint stacks, Color *color) {
		this->radius = radius;
		this->slices = slices;
		this->stacks = stacks;
		this->color = color;
		this->quadratic = gluNewQuadric();
	}

	/*Destructora de la clase Esfera.*/
	~Esfera() {
		gluDeleteQuadric(quadratic);
		delete this->color;
	}


	/**********************
	 *Métodos de la clase.*
	 **********************/

	/*Método que dibuja la esfera.*/
	void dibuja() {
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glColor3f(color->getR(), color->getG(), color->getB());
		gluSphere(quadratic, radius, slices, stacks);
	}


};

#endif
