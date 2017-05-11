#ifndef VERTICENORMAL_H
#define VERTICENORMAL_H

/*
Clase v�rtice/Normal. Establece una relacci�n entre un v�rtice y su normal.
*/
class VerticeNormal {
private:
	/*Indice del vertice y su normal asociada.*/
	GLint indiceVertice, indiceNormal;

public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase verticeNormal.*/
	VerticeNormal(GLint v, GLint n) {
		this->indiceVertice = v;
		this->indiceNormal = n;
	}
	
	/*********
	 *Getters*
	 *********/

	/*Devuelve el indice del punto del v�rtice.*/
	GLint getIndiceVertice(){
		return this->indiceVertice;
	}

	/*Devuelve el indice de la normal del v�rtice.*/
	GLint getIndiceNormal(){
		return this->indiceNormal;
	}

};

#endif