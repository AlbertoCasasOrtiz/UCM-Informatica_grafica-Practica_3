#ifndef FOCO_H
#define FOCO_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include <iostream>

/*
Clase spotlight. Define un foco.
*/
class SpotLight {
private:
	/*Número de luz.*/
	GLenum param;
	/*Dirección a la que apunta el foco.*/
	GLfloat *dir;
	/*Posición del foco.*/
	GLfloat *p;
	/*Parámetros del foco.*/
	GLfloat epsilon, alpha;
public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase spotlight.*/
	SpotLight(GLint param, GLfloat epsilon, GLfloat alpha, GLfloat dir[], GLfloat d[], GLfloat a[], GLfloat e[], GLfloat p[]) {
		if (param == GL_LIGHT0 || param == GL_LIGHT1 || param == GL_LIGHT2 || param == GL_LIGHT3 || param == GL_LIGHT4
			|| param == GL_LIGHT5 || param == GL_LIGHT6 || param == GL_LIGHT7) {
			/*Inicializamos parametros.*/
			this->dir = new GLfloat[4];
			this->p = new GLfloat[4];
			for (int i = 0; i < 4; i++) {
				if(i < 3)
					this->dir[i] = dir[i];
				this->p[i] = p[i];
			}
			this->param = param;
			this->alpha = alpha;
			this->epsilon = epsilon;

			/*Activamos la luz.*/
			glLightfv(param, GL_DIFFUSE, d);
			glLightfv(GL_LIGHT0, GL_SPECULAR, e);
			glLightfv(param, GL_SPOT_DIRECTION, dir);
			glLightf(param, GL_SPOT_CUTOFF, alpha);
			glLightf(param, GL_SPOT_EXPONENT, epsilon);
			glLightfv(param, GL_POSITION, p);
			glEnable(param);
		}
	}

	/*Destructora de la clase Spotlight.*/
	~SpotLight() {
		delete dir, p;
	}

	/**********
	 *Getters.*
	 **********/

	/*Devuelve la posición del foco.*/
	PV3D* getPosition() {
		return new PV3D(p[0], p[1], p[2], (GLint)p[3]);
	}



	/**********
	*Setters.*
	**********/

	/*Establece una nueva posición para el foco.*/
	void setPosition(PV3D* p) {
		this->p[0] = p->getX();
		this->p[1] = p->getY();
		this->p[2] = p->getZ();
		this->p[3] = p->isVectorOrNormal();
	}

	/*Establece una nueva dirección para el foco.*/
	void setDir(GLfloat *dir) {
		this->dir[0] = dir[0];
		this->dir[1] = dir[1];
		this->dir[2] = dir[2];
	}

	/*Establece un nuevo valor alpha para el foco.*/
	void setAlpha(GLfloat alpha) {
		this->alpha = alpha;
		glLightf(param, GL_SPOT_CUTOFF, alpha);
	}



	/**********************
	 *Métodos de la clase,*
	 **********************/

	/*Apaga un foco.*/
	void disable() {
		glDisable(param);
	}

	/*Enciende un foco.*/
	void enable() {
		glEnable(param);
	}

	/*Reestablece la información de un foco.*/
	void reponeLight() {
		glLightfv(param, GL_POSITION, p);
		glLightfv(param, GL_SPOT_DIRECTION, dir);
		glLightf(param, GL_SPOT_CUTOFF, alpha);
	}


};


#endif