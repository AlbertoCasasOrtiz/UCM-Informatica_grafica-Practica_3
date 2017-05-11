#ifndef DISCO_H
#define DISCO_H

#include "ObjetoCompuesto3D.h"
#include "Color.h"


/*
Clase cilindro. Genera un cilindro.
*/
class Disco : public ObjetoCompuesto3D{
private:
	/*Objeto cuadratico generado para el cilindro.*/
	GLUquadricObj *quadratic;

	/*Parámetros del cilindro.*/
	GLfloat innerRadius, outerRadius;

	/*Partes que forman el cilindro.*/
	GLint slices, rings;

	/*Color del cilindro.*/
	Color * color;
public:

	/****************/
	/*Constructoras.*/
	/****************/

	/*Constructora de la clase cilindro.*/
	Disco(GLfloat innerRadius, GLfloat outerRadius, GLint slices, GLint rings, Color *color) {
		this->innerRadius = innerRadius;
		this->outerRadius = outerRadius;
		this->slices = slices;
		this->rings = rings;
		this->color = color;
		this->quadratic = gluNewQuadric();
	}

	/*Destructora de la clase cilindro.*/
	~Disco() {
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
		gluDisk(quadratic, innerRadius, outerRadius, slices, rings);
	}

};

#endif
