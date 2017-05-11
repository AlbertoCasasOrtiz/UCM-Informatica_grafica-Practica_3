#ifndef CURVA_H
#define CURVA_H

#include "Autopista.h"

/*
Clase curva. Añade una curva de 180 grados.
*/
static class Curva : public ObjetoCompuesto3D {
private:
	/*Fragmentos que formarán la curva.*/
	GLint frags;
public:

	/****************
	*Constructoras.*
	****************/

	/*Constructora de la clase curva.*/
	Curva(GLint frags) {
		this->frags = frags;
		/*Cogemos fragmentos de autopista.*/
		Autopista** autopista = new Autopista*[frags+1];
		for (int i = 0; i < frags+1; i++) {
			autopista[i] = new Autopista(1);
			this->introduceObjeto(autopista[i]);
		}
		/*Giramos fragmentos de autopista.*/
		GLfloat cont = 0;
		for (int i = 0; i < frags+1; i++) {
			autopista[i]->getTAfin()->gira(cont, 'y');
			cont += 180 / (frags-1);
		}

	}

};


#endif