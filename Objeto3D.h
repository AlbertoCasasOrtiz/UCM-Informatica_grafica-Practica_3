#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "TAfin.h"
#include <iostream>

using namespace std;

/*
Clase objeto3D. Define un objeto 3D con su matriz T afín.
*/
class Objeto3D {
private:
	/*Matriz de transformación afín del objeto.*/
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

	/*Devuelve la matriz de transformación afín.*/
	TAfin* getTAfin() {
		return this->mT;
	}


	/**********************/
	/*Métodos de la clase.*/
	/**********************/

	/*Método que dibuja el objeto. Virtual por que lo implementan clases hijas.*/
	virtual void dibuja() = 0;
};


#endif