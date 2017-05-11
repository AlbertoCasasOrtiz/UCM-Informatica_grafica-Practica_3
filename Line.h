#ifndef LINE_H
#define LINE_H

#include "PV3D.h"
#include "Color.h"

/*
Esta clase define una línea entre dos puntos.
*/
class Line {
private:
	/*Inicio de la linea.*/
	PV3D* begin;
	/*Final de la linea.*/
	PV3D* end;
	/*Color de la linea.*/
	Color* color;
public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase linea.*/
	Line(PV3D* begin, PV3D* end, Color* color) {
		this->begin = begin;
		this->end = end;
		this->color = color;
	}

	/*Destructora de la clase Line.*/
	~Line(){
		delete begin, end, color;
	}


	/**********************
	 *Métodos de la clase.*
	 **********************/

	/*Método para dibujar la linea.*/
	void dibuja() {
		glBegin(GL_LINES);
			glColor3f(this->color->getR(), this->color->getG(), this->color->getB());
			glVertex3f(this->begin->getX(), this->begin->getY(), this->begin->getZ());
			glVertex3f(this->end->getX(), this->end->getY(), this->end->getZ());
		glEnd();
	}
};

#endif