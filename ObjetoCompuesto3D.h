#ifndef OBJETOCOMPUESTO3D_H
#define OBJETOCOMPUESTO3D_H

#include <gl/GL.h>

#include "Objeto3D.h"

/*
Clase Objeto Compuesto3D. Genera un objeto compuesto a partir de objetos simples 3D.
*/
class ObjetoCompuesto3D :public Objeto3D {
private:
	/*Número de hijos del objeto compuesto.*/
	int numHijos;

	/*Array que contiene los hijos del objeto 3D.*/
	Objeto3D** hijo;

	/*Tamaño del array de hijos.*/
	int tamHijos;

	/*Redimensiona el array de hijos.*/
	void resizeHijos() {
		Objeto3D** objetos = new Objeto3D*[this->tamHijos + 5];
		for (GLint i = 0; i < this->numHijos; i++)
			objetos[i] = hijo[i];
		this->tamHijos += 5;
		delete hijo;
		hijo = objetos;
	}

public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase objeto compuesto 3D.*/
	ObjetoCompuesto3D() {
		this->numHijos = 0;
		this->tamHijos = 5;
		this->hijo = new Objeto3D*[this->tamHijos];
	}

	/*Destructora de la clase objeto compuesto 3D.*/
	~ObjetoCompuesto3D(){
		for (int i = 0; i < numHijos; i++)
			delete hijo[i];
		delete hijo;
	}

	/**********
	 *Getters.*
	 **********/

	/*Método que devuelve el hijo i.*/
	Objeto3D* getHijos(GLint i) {
		return this->hijo[i];
	}



	/**********************
	 *Métodos de la clase.*
	 **********************/

	/*Método que introduce un objeto 3D en el array de hijos.*/
	void introduceObjeto(Objeto3D * objeto) {
		if (numHijos >= tamHijos)
			this->resizeHijos();
		hijo[numHijos] = objeto;
		numHijos++;
	}

	/*Método que dibuja los hijos.*/
	void dibuja() {
		for (int i = 0; i < numHijos; i++) {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glMultMatrixf(hijo[i]->getTAfin()->getM());
				hijo[i]->dibuja();
			glPopMatrix();
		}
	}
};

#endif