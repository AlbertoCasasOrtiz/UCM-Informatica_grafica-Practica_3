#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "TAfin.h"
#include <iostream>

using namespace std;

/*
Clase objeto3D. Define un objeto 3D con su matriz T af�n.
*/
class Objeto3D {
private:
	/*Matriz de transformaci�n af�n del objeto.*/
	TAfin *mT;

public:

	/****************
	 *Constructoras.*
	 ****************/
	
	/*Constructora de la clase Objeto 3D.*/
	Objeto3D() {
		this->mT = new TAfin();
	}

	/*Destructora de la clase Objeto3D.*/
	~Objeto3D(){
		delete mT;
	}

	/**********
	 *Getters.*
	 **********/

	/*Devuelve la matriz de transformaci�n af�n.*/
	TAfin* getTAfin() {
		return this->mT;
	}


	/**********************/
	/*M�todos de la clase.*/
	/**********************/

	/*M�todo que dibuja el objeto. Virtual por que lo implementan clases hijas.*/
	virtual void dibuja() = 0;
};


#endif