#ifndef CILINDRO_H
#define CILINDRO_H

#include "ObjetoCompuesto3D.h"
#include "Color.h"


/*
Clase cilindro. Genera un cilindro.
*/
class Cilindro : public ObjetoCompuesto3D{
private:
	/*Objeto cuadratico generado para el cilindro.*/
	GLUquadricObj *quadratic;

	/*Parámetros del cilindro.*/
	GLfloat baseRadius, topRadius, height;

	/*Partes que forman el cilindro.*/
	GLint slices, stacks;

	/*Color del cilindro.*/
	Color * color;
public:

	/****************/
	/*Constructoras.*/
	/****************/

	/*Constructora de la clase cilindro.*/
	Cilindro(GLfloat baseRadius, GLfloat topRadius, GLfloat height, GLint slices, GLint stacks, Color *color) {
		this->baseRadius = baseRadius;
		this->topRadius = topRadius;
		this->height = height;
		this->slices = slices;
		this->stacks = stacks;
		this->color = color;
		this->quadratic = gluNewQuadric();
	}

	/*Destructora de la clase cilindro.*/
	~Cilindro() {
		gluDeleteQuadric(quadratic);
		delete this->color;
	}

	/**********************
	 *Métodos de la clase.*
	 **********************/

	/*Método que dibuja el cilindro.*/
	void dibuja() {
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glColor3f(color->getR(), color->getG(), color->getB());
		gluCylinder(quadratic, baseRadius, topRadius, height, slices, stacks);
	}

};

#endif
