#ifndef CARA_H
#define CARA_H

#include "VerticeNormal.h"

/*
Clase cara. Define una cara con un n�mero de v�rtices.
*/
class Cara {
private:
	/*N�mero de v�rtices en la cara.*/
	GLint numVertices;
	
	/*N�mero de v�rtices ya insertados en la cara.*/
	GLint verticesDentro;

	/*Array de v�rtices en la cara.*/
	VerticeNormal** arrayVN;

	/*Suma en 1 el n�mero de v�rtices dentro de la cara.*/
	void aumentaVerticesDentro() {
		this->verticesDentro++;
	}

public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de una cara con un n�mero de v�rtices.*/
	Cara(GLint numVertices) {
		this->numVertices = numVertices;
		arrayVN = new VerticeNormal*[this->numVertices];
		this->verticesDentro = 0;
	}

	/*Destructora de la cara.*/
	~Cara() {
		/*Destruimos contenido del array arrayVN y el arrayVN.*/
		for (GLint i = 0; i < this->numVertices; i++)
			delete arrayVN[i];
		if (arrayVN != NULL)
			delete arrayVN;
	}


	/**********
	 *Getters.* 
	 **********/

	/*Devuelve el n�mero de v�rtices de la cara.*/
	GLint getNumVertices() {
		return this->numVertices;
	}

	/*Devuelve el �ndice de la normal de la cara.*/
	GLint getIndiceNormal(GLint i){
		return this->arrayVN[i]->getIndiceNormal();
	}

	/*Devuelve el �ndice del v�rtice de la cara.*/
	GLint getIndiceVertice(GLint i){
		return this->arrayVN[i]->getIndiceVertice();
	}

	/*Devuelve el n�mero de v�rtices que hay dentro de la cara.*/
	GLint getVerticesDentro() {
		return this->verticesDentro;
	}


	/**********
	 *Setters.*
	 **********/

	/*Pone un n�mero de v�rtices a la cara.*/
	void setNumVertice(GLint i) {
		this->numVertices = i;
	}

	/*Establece los �ndices de un v�rtice y su noral para la cara.*/
	void setIndiceVerticeNormal(GLint i, GLint v, GLint n) {
		this->arrayVN[i] = new VerticeNormal(v, n);
		this->aumentaVerticesDentro();
	}

};

#endif