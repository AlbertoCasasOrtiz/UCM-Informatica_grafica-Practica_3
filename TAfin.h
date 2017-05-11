#ifndef TAFIN_H
#define TAFIN_H

#include <gl/GL.h>

#include "PV3D.h"

/*Clase TAfin. Define una matriz de transformación afin.*/
class TAfin {
private:
	/*Matriz representada como un vector.*/
	GLfloat* m;
public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase TAfin.*/
	TAfin() {
		this->m = new GLfloat[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
	}

	/*Destructora de la clase TAfin.*/
	~TAfin(){
		delete m;
	}

	/**********
	 *Getters.*
	 **********/

	/*Devolvemos la matriz afin.*/
	GLfloat* getM() {
		return this->m;
	}


	/**********************
	 *Métodos de la clase.*
	 **********************/

	/*Postmultiplicamos la matriz por otra dada.*/
	void postmultiplica(GLfloat * m1) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();{
			//Cargar m como matriz actual de modelado-vista.
			glLoadMatrixf(this->m);
			//Post-multiplicar por m1.
			glMultMatrixf(m1);
			//Dejar el resultado en m.
			glGetFloatv(GL_MODELVIEW_MATRIX, m);
		} 
		glPopMatrix();
	}

	/*Multiplicamos la matriz por el punto al que vamos a trasladar..*/
	void traslada(PV3D* v) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glTranslatef(v->getX(), v->getY(), v->getZ());
			GLfloat m1[16];
			//Dejar la matriz actual de modelado vista en m1.
			//Los 16 datos están enumerados por columnas.
			glGetFloatv(GL_MODELVIEW_MATRIX, m1);
		
		glPopMatrix();
		postmultiplica(m1);
	}

	/*Multiplicamos la matriz por la matriz de rotación.*/
	void gira(GLfloat giro, char eje) {
		if (eje == 'x' || eje == 'y' || eje == 'z') {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glLoadIdentity();
				glRotatef(giro, eje == 'x', eje == 'y', eje == 'z');
				GLfloat m1[16];
				//Dejar la matriz actual de modelado vista en m1.
				//Los 16 datos están enumerados por columnas.
				glGetFloatv(GL_MODELVIEW_MATRIX, m1);
			glPopMatrix();
			postmultiplica(m1);
		}
		else {
			cout << "Eje inválido al girar en TAfin::gira(). Valor eje: = " << eje << "." << endl;
		}
	}

	/*Multiplicamos la matriz por la matriz de escalación.*/
	void escala(PV3D* escala) {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glScalef(escala->getX(), escala->getY(), escala->getZ());
			GLfloat m1[16];
			//Dejar la matriz actual de modelado vista en m1.
			//Los 16 datos están enumerados por columnas.
			glGetFloatv(GL_MODELVIEW_MATRIX, m1);
			glPopMatrix();
			postmultiplica(m1);
	}

};


#endif