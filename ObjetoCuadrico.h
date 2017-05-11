#ifndef OBJETOCUADRICO_H
#define OBJETOCUADRICO_H

#include "Objeto3D.h"

/*
Clase objeto cuadrico. Define un objeto cuadrico.
*/
class ObjetoCuadrico : public Objeto3D {
public:
	/*Método virtual dibuja.*/
	virtual void dibuja() = 0;
};

#endif