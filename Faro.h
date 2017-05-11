#ifndef FARO_H
#define FARO_H

#include "ObjetoCompuesto3D.h"
#include "Cilindro.h"
#include "Disco.h"

using namespace std;

/*
Clase faro. Faro del coche.
*/
class Faro : public ObjetoCompuesto3D {
private:
	/*Cilindro que será el cuerpo del faro.*/
	Cilindro *cilindro;
	/*Disco que será la tapa del faro.*/
	Disco *disco;
	/*Centro del disco.*/
	PV3D* centroDisco;
public:
	/****************
	*Constructoras.*
	****************/

	/*Constructora de la clase faro.*/
	Faro(GLfloat baseRadius, GLfloat topRadius, GLfloat length, GLint slices, GLint stacks, Color* color) {
		cilindro = new Cilindro(baseRadius, topRadius, length, slices, stacks, color);
		disco = new Disco(0, topRadius, slices, 1, color);
		centroDisco = new PV3D(0.0, 0.0, 0.0, 1);

		this->introduceObjeto(cilindro);
		this->introduceObjeto(disco);
		this->disco->getTAfin()->traslada(new PV3D(0.0, length, 0.0, 1));
		this->centroDisco->setY(this->centroDisco->getY() + length);
	}

	/*Destructora de la clase faro.*/
	~Faro() {
		delete cilindro;
		delete disco;
		delete centroDisco;
	}

	/**********
	*Getters.*
	**********/

	/*Devuelve el centro de la tapa del faro.*/
	PV3D* getCentroDisco() {
		return this->centroDisco;
	}

	/**********
	*Setters*.
	**********/

	/*Pone un nuevo centro al disco de la tapa del faro.*/
	PV3D* setCentroDisco(PV3D* newCenter) {
		this->centroDisco = newCenter;
	}
};


#endif