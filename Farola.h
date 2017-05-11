#ifndef FAROLA_H
#define FAROLA_H

#include "ObjetoCompuesto3D.h"
#include "Cilindro.h"
#include "Esfera.h"


/*
Clase farola. Genera una farola a partir de un cilindro y una esfera.
*/
class Farola : public ObjetoCompuesto3D {
private:
	GLfloat height;
public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase farola.*/
	Farola(GLfloat height, GLfloat boddyradius, GLfloat lampRadius) {
		this->height = height;

		//Insertamos los elementos
		this->introduceObjeto(new Cilindro(boddyradius, boddyradius, height, 20, 1, new Color("orange")));
		this->introduceObjeto(new Esfera(lampRadius, 20, 20, new Color("yellow")));

		//Colocamos la esfera
		this->getHijos(1)->getTAfin()->traslada(new PV3D(0.0, height, 0.0, 1));
	}

	/*Devuelve el centro de la esfera de la lámpara.*/
	PV3D *getCenterSphere() {
		return new PV3D(0.0, height, 0.0, 1);
	}
};


#endif