#ifndef TABLERO_H
#define TABLERO_H

#include "ObjetoCompuesto3D.h"
#include "Cubo.h"
#include "Color.h"

/*
Clase tablero. Crea un tablero tridimensional a partir de una serie de cubos de lado 1.
*/
class Tablero :public ObjetoCompuesto3D {
public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase tablero.*/
	Tablero(GLint x, GLint y, GLint z, Color *color) {
		/*Introducimos los cubos necesarios*/
		for (int i = 0; i < x*y*z; i++)
			this->introduceObjeto(new Cubo(color));

		GLint incX, incY, incZ, cont;
		incX = incY = incZ = -1, cont = 0;
		/*Creamos un cubo trasladado por cada cubo introducido.*/
		//Creamos primero las columnas de una fila, así hasta completar todas
		//las filas hasta pasar al final a la siguiente capa.
		for (int i = 0; i < x; i++) {
			incX++;
			for (int j = 0; j < y; j++) {
				incY++;
				for (int k = 0; k < z; k++) {
					incZ++;
					getHijos(cont)->getTAfin()->traslada(new PV3D((GLfloat)incX, (GLfloat)incY, (GLfloat)incZ, 1.0f));
					cont++;
				}
				incZ = -1;
			}
			incY = -1;
		}
		incX = -1;
	}

};

#endif