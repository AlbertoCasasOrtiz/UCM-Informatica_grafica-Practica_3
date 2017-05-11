#ifndef LAMP_H
#define LAMP_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include <iostream>

/*
Clase l�mpara. Define una luz normal.
*/
class Lamp {
private:
	/*N�mero de luz.*/
	GLenum param;
	/*Componente difusa.*/
	GLfloat *d;
	/*Componente ambiente.*/
	GLfloat *a;
	/*Posici�n.*/
	GLfloat *p;
public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase l�mpara.*/
	Lamp(GLint param, GLfloat d[], GLfloat a[], GLfloat e[], GLfloat p[]){
		if (param == GL_LIGHT0 || param == GL_LIGHT1 || param == GL_LIGHT2 || param == GL_LIGHT3 || param == GL_LIGHT4
			|| param == GL_LIGHT5 || param == GL_LIGHT6 || param == GL_LIGHT7){
			/*Inicializamos parametros.*/
			this->d = new GLfloat[4];
			this->a = new GLfloat[4];
			this->p = new GLfloat[4];
			for (int i = 0; i < 4; i++) {
				this->d[i] = d[i];
				this->a[i] = a[i];
				this->p[i] = p[i];
			}
			this->param = param;
			/*Activamos la luz.*/
			glEnable(param);
			glLightfv(param, GL_DIFFUSE, d);
			glLightfv(param, GL_AMBIENT, a);
			glLightfv(GL_LIGHT0, GL_SPECULAR, e);
			glLightfv(param, GL_POSITION, p);
		}
	}

	/*Destructora de la clase Lamp.*/
	~Lamp() {
		delete d, a, p;
	}

	/**********
	 *Getters.*
	 **********/

	/*Devuelve la posici�n de la l�mpara.*/
	PV3D* getPosition() {
		return new PV3D(p[0], p[1], p[2], (GLint)p[3]);
	}



	/**********
	 *Setters.*
	 **********/

	/*Establece una posici�n para la l�mpara.*/
	void setPosition(PV3D* p) {
		this->p[0] = p->getX();
		this->p[1] = p->getY();
		this->p[2] = p->getZ();
		this->p[3] = (GLfloat)p->isVectorOrNormal();
	}



	/**********************
	 *M�todos de la clase,*
	 **********************/

	/*Apaga una l�mpara.*/
	void disable() {
		glDisable(param);
	}

	/*Activa una l�mpara.*/
	void enable() {
		glEnable(param);
	}

	/*Reposiciona una luz.*/
	void reponeLight() {
		glLightfv(param, GL_POSITION, p);
	}


};


#endif