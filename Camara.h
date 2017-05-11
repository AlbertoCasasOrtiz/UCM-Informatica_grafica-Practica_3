#ifndef CAMARA_H
#define CAMARA_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <Windows.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <math.h>

#include "PV3D.h"
#include "SquareMatrix.h"

using namespace std;

/*Clase c�mara. Define la c�mara con todos sus par�metros.*/
class Camara {
private:
	//Camera parammeters
	PV3D *eyeIni, *lookIni, *upIni;
	PV3D *eye, *look, *up, *u, *v, *n;

	/*Frustum parameters*/
	GLdouble left, right, top, bottom, fnear, ffar;
	GLboolean esPerspectiva;

	/*Camera rotation local parameters.*/
	GLfloat giroP, giroR, giroY;
	GLfloat gradoGiro = 2 * (GLfloat)M_PI / 10000;

	/*Camera rotation global parameters.*/
	GLfloat rotX, rotY, rotZ;
	GLfloat gradoOrbita = 0.1f;

	/*Camera translation parameters.*/
	GLfloat posEyeX, posEyeY, posEyeZ;
	GLfloat incDesp = 5;

	/*Recalcula el vector n.*/
	PV3D* nVector() {
		PV3D * res = new PV3D(eye->getX() - look->getX(), eye->getY() - look->getY(), eye->getZ() - look->getZ(), 0);
		res->normaliza();
		return res;
	}

	/*Recalcula el vector u.*/
	PV3D* uVector() {
		PV3D * res = up->productoVectorial(this->n);
		res->normaliza();
		return res;
	}

	/*Recalcula el vector v.*/
	PV3D* vVector() {
		PV3D * res = n->productoVectorial(this->u);
		return res;
	}

	/*Recalcula el vector n.*/
	GLfloat toRadian(GLfloat decimal) {
		return (GLfloat)(2* (GLfloat)M_PI*decimal / (GLfloat)360);
	}

public:


	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase c�mara.*/
	Camara(PV3D * eye, PV3D * look, PV3D * up, GLfloat xLeft, GLfloat xRight, GLfloat yBot, GLfloat yTop, GLfloat N, GLfloat F){
		//Inicializamos los �ngulos
		this->giroR = 0;
		this->giroP = 0;
		this->giroY = 0;

		//Inicializamos vectores de la c�mara
		this->eye = eye->clona();
		this->look = look->clona();
		this->up = up->clona(); 
		this->eyeIni = eye->clona();
		this->lookIni = look->clona();
		this->upIni = up->clona();

		/*Inicializamos las posiciones.*/
		this->posEyeX = eye->getX();
		this->posEyeY = eye->getY();
		this->posEyeZ = eye->getZ();

		this->rotX = (GLfloat)M_PI / 100;
		this->rotY = (GLfloat)M_PI / 100;
		this->rotZ = (GLfloat)M_PI / 100;

		//Inicializamos vectores locales de la c�mara
		this->n = nVector();
		this->u = uVector();
		this->v = vVector();

		// Inicializaci�nes
		this->esPerspectiva = false;
		this->left = xLeft;
		this->right = xRight;
		this->top = yTop;
		this->bottom = yBot;
		this->fnear = N;
		this->ffar = F;

		setUpCamera();

		setUpFrustum();

	}

	/*Destructora de la clase c�mara.*/
	~Camara(){
		delete eyeIni, lookIni, upIni ,eye, look, up, u, v, n;
	}

	/**********
	*Getters.*
	**********/

	/*Get eye values.*/
	PV3D* getEye() {
		return this->eye;
	}


	/**********
	 *Setters.*
	 **********/

	/*Set up camera.*/
	void setUpCamera() {
		// Camera set up
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eye->getX(), eye->getY(), eye->getZ(), look->getX(), look->getY(), look->getZ(), up->getX(), up->getY(), up->getZ());
	}

	/*Set up frustum perspective.*/
	void setUpFrustum() {
		// Frustum set up
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(left, right, bottom, top, fnear, ffar);
	}

	/*Set up ortho view.*/
	void setUpOrtho() {
		// Frustum set up
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(left, right, bottom, top, fnear, ffar);
	}
	
	/*Set look values.*/
	void setLook(PV3D* newLook) {
		this->look = newLook;
	}

	/*Set eye values.*/
	void setEye(PV3D* newEye) {
		this->eye = newEye;
	}


	/**********************
	 *M�todos de la clase.*
	 **********************/

	/*Local rotations.*/

	/*Pitch movement.*/
	void pitch(string dir) {
		if (dir == "neg") {
			giroP = gradoGiro;
		}
		else if (dir == "pos") {
			giroP = -gradoGiro;
		}
		else {
			cout << "Error: Direcci�n de giro inv�lida." << endl;
		}
		GLfloat coseno = cos(giroP);
		GLfloat seno = sin(giroP);

		/*Sacamos los nuevos u, v y n.*/
		PV3D* newU = new PV3D(u->getX(), u->getY(), u->getZ(), 0);
		PV3D* newV = new PV3D(coseno * v->getX() + n->getX()*seno, v->getY()*coseno + n->getY()*seno, v->getZ()*coseno + n->getZ()*seno, 0);
		PV3D* newN = new PV3D(-seno * v->getX() + coseno * n->getX(), -seno * v->getY() + coseno * n->getY(), -seno * v->getZ() + coseno * n->getZ(), 0);
		PV3D* newE = new PV3D(eye->getX(), eye->getY(), eye->getZ(), 1);

		/*Recalculamos n u y v.*/
		this->u = newU->clona();
		this->v = newV->clona();
		this->n = newN->clona();

		/*Actualizamos up.*/
		//this->up = new PV3D(v->getX(), v->getY(), v->getZ(), v->isVectorOrNormal());

		/*Invertimos la matriz.*/
		SquareMatrix *sm = new SquareMatrix(newU, newV, newN, newE);
		sm = sm->inversa();

		/*Cargamos la matriz.*/
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixf(sm->getVector());
	}

	/*Yaw movement.*/
	void yaw(string dir) {
		if (dir == "neg") {
			giroY = gradoGiro;
		}
		else if (dir == "pos") {
			giroY = -gradoGiro;
		}
		else {
			cout << "Error: Direcci�n de giro inv�lida." << endl;
		}
		GLfloat coseno = cos(giroY);
		GLfloat seno = sin(giroY);

		/*Sacamos los nuevos u, v y n.*/
		PV3D* newU = new PV3D(coseno * u->getX() - seno * n->getX(), coseno * u->getY() - seno * n->getY(), coseno * u->getZ() - seno * n->getZ(), 0);
		PV3D* newV = new PV3D(v->getX(), v->getY(), v->getZ(), 0);
		PV3D* newN = new PV3D(seno * u->getX() + coseno * n->getX(), seno * u->getY() + coseno * n->getY(), seno * u->getZ() + coseno * n->getZ(), 0);
		PV3D* newE = new PV3D(eye->getX(), eye->getY(), eye->getZ(), 1);

		/*Recalculamos n u y v.*/
		this->u = newU->clona();
		this->v = newV->clona();
		this->n = newN->clona();

		/*Actualizamos up.*/
		//this->up = new PV3D(v->getX(), v->getY(), v->getZ(), v->isVectorOrNormal());

		/*Invertimos la matriz.*/
		SquareMatrix *sm = new SquareMatrix(newU, newV, newN, newE);
		sm = sm->inversa();

		/*Cargamos la matriz.*/
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixf(sm->getVector());
	}

	/*Roll movement.*/
	void roll(string dir) {
		if (dir == "neg") {
			giroR = gradoGiro;
		}
		else if (dir == "pos") {
			giroR = -gradoGiro;
		}
		else {
			cout << "Error: Direcci�n de giro inv�lida." << endl;
		}
		GLfloat coseno = cos(giroR);
		GLfloat seno = sin(giroR);

		/*Sacamos los nuevos u, v y n.*/
		PV3D* newU = new PV3D(coseno * u->getX() + seno * v->getX(), coseno * u->getY() + seno * v->getY(), coseno * u->getZ() + seno * v->getZ(), 0);
		PV3D* newV = new PV3D(-seno * u->getX() + coseno * v->getX(), -seno * u->getY() + coseno * v->getY(), -seno * u->getZ() + coseno * v->getZ(), 0);
		PV3D* newN = new PV3D(n->getX(), n->getY(), n->getZ(), 0);
		PV3D* newE = new PV3D(eye->getX(), eye->getY(), eye->getZ(), 1);

		/*Recalculamos n u y v.*/
		this->u = newU->clona();
		this->v = newV->clona();
		this->n = newN->clona();

		/*Actualizamos up.*/
		//this->up = new PV3D(v->getX(), v->getY(), v->getZ(), v->isVectorOrNormal());

		/*Invertimos la matriz.*/
		SquareMatrix *sm = new SquareMatrix(newU, newV, newN, newE);
		sm = sm->inversa();

		/*Cargamos la matriz.*/
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glLoadMatrixf(sm->getVector());
	}


	/*Views.*/

	/*Frontal view.*/
	void vistaFrontal() {
		giroY = giroP = giroR = 0;

		/*Recumeramos look up y eye iniciales.*/
		this->look = lookIni->clona();
		this->up = upIni->clona();
		this->eye = eyeIni->clona();

		/*Modificamos eye.*/
		this->eye->setX(0);
		this->eye->setY(0);

		/*Reseteamos posEye.*/
		this->posEyeX = eye->getX();
		this->posEyeY = eye->getY();
		this->posEyeZ = eye->getZ();

		/*Recalculamos n u y v.*/
		this->n = nVector();
		this->u = uVector();
		this->v = vVector();

		/*Actualizamos camara.*/
		setUpCamera();
	}

	/*Lateral view.*/
	void vistaLateral() {
		giroY = giroP = giroR = 0;

		/*Recumeramos look up y eye iniciales.*/
		this->look = lookIni->clona();
		this->up = upIni->clona();
		this->eye = eyeIni->clona();

		/*Modificamos eye.*/
		this->eye->setY(0);
		this->eye->setZ(0);

		/*Reseteamos posEye.*/
		this->posEyeX = eye->getX();
		this->posEyeY = eye->getY();
		this->posEyeZ = eye->getZ();

		/*Recalculamos n u y v.*/
		this->n = nVector();
		this->u = uVector();
		this->v = vVector();

		/*Actualizamos camara.*/
		setUpCamera();
	}

	/*Cenital view.*/
	void vistaCenital() {
		giroY = giroP = giroR = 0;

		/*Recumeramos look up y eye iniciales.*/
		this->look = lookIni->clona();
		this->up = upIni->clona();
		this->eye = eyeIni->clona();

		/*Modificamos eye.*/
		this->eye->setX(0);
		this->eye->setZ(0);

		this->up->setX(1);
		this->up->setY(0);
		this->up->setZ(0);

		/*Recalculamos n u y v.*/
		this->n = nVector();
		this->u = uVector();
		this->v = vVector();

		/*Actualizamos camara.*/
		setUpCamera();
	}

	/*Corner view.*/
	void vistaEsquina() {
		giroY = giroP = giroR = 0;

		/*Recumeramos look up y eye iniciales.*/
		this->look = lookIni->clona();
		this->up = upIni->clona();
		this->eye = eyeIni->clona();

		/*Reseteamos posEye.*/
		this->posEyeX = eye->getX();
		this->posEyeY = eye->getY();
		this->posEyeZ = eye->getZ();

		/*Recalculamos n u y v.*/
		this->n = nVector();
		this->u = uVector();
		this->v = vVector();

		setUpCamera();
	}


	/*Camera translations.*/

	/*Translate in X.*/
	void translateX(string dir) {
		giroY = giroP = giroR = 0;
		this->up = upIni;
		if (dir == "neg") {
			posEyeX -= incDesp;
		}
		else if (dir == "pos"){
			posEyeX += incDesp;
		}
		else
			cout << "Error: Direcci�n no reconocida." << endl;

		/*Actualizamos eye.*/
		eye->setX(posEyeX);

		setUpCamera();

		this->n = nVector();
		this->u = uVector();
		this->v = vVector();
	}

	/*Translate in Y.*/
	void translateY(string dir) {
		giroY = giroP = giroR = 0;
		this->up = upIni;
		if (dir == "neg") {
			posEyeY -= incDesp;
		}
		else if (dir == "pos") {
			posEyeY += incDesp;
		}
		else
			cout << "Error: Direcci�n no reconocida." << endl;

		/*Actualizamos eye.*/
		eye->setY(posEyeY);

		setUpCamera();

		this->n = nVector();
		this->u = uVector();
		this->v = vVector();
	}

	/*Translate in Z.*/
	void translateZ(string dir) {
		giroY = giroP = giroR = 0;
		this->up = upIni;
		if (dir == "neg") {
			posEyeZ -= incDesp;
		}
		else if (dir == "pos") {
			posEyeZ += incDesp;
		}
		else
			cout << "Error: Direcci�n no reconocida." << endl;

		/*Actualizamos eye.*/
		eye->setZ(posEyeZ);

		setUpCamera();

		this->n = nVector();
		this->u = uVector();
		this->v = vVector();

	}


	/*Global rotations.*/

	/*Gira alrededor del eje y.*/
	void giraY(string dir) {
		giroY = giroP = giroR = 0;

		if (dir == "neg")
			rotY = -gradoOrbita;
		else if (dir == "pos")
			rotY = gradoOrbita;
		else
			cout << "Error: Direcci�n no reconocida." << endl;

		/*Usamos la matriz de transformaci�n.*/
		GLfloat eyeXAux = cos(rotY)*this->eye->getX() + sin(rotY)*this->eye->getZ();
		GLfloat eyeYAux = eye->getY();
		GLfloat eyeZAux = -sin(rotY)*this->eye->getX() + cos(rotY)*this->eye->getZ();

		/*Actualiza eye.*/
		this->eye->setX(eyeXAux);
		this->eye->setY(eyeYAux);
		this->eye->setZ(eyeZAux);

		/*Actualiza n u y v.*/
		this->n = nVector();
		this->u = uVector();
		this->v = vVector();

		setUpCamera();
	}

	/*Gira alrededor del eje x-.*/
	void giraX(string dir) {
		giroY = giroP = giroR = 0;

		this->up = upIni;

		if (dir == "neg")
			rotX = -gradoOrbita;
		else if (dir == "pos")
			rotX = gradoOrbita;
		else
			cout << "Error: Direcci�n no reconocida." << endl;

		/*Usamos la matriz de transformaci�n.*/
		GLfloat eyeXAux = eye->getX();
		GLfloat eyeYAux = cos(rotX)*this->eye->getY() - sin(rotX)*this->eye->getZ();
		GLfloat eyeZAux = sin(rotX)*this->eye->getY() + cos(rotX)*this->eye->getZ();

		/*Actualiza eye.*/
		eye->setX(eyeXAux);
		eye->setY(eyeYAux);
		eye->setZ(eyeZAux);

		/*Actualiza n u y v.*/
		this->n = nVector();
		this->u = uVector();
		this->v = vVector();

		setUpCamera();
	}

	/*Gira alrededor del eje z.*/
	void giraZ(string dir) {
		giroY = giroP = giroR = 0;

		this->up = upIni;

		if (dir == "neg")
			rotZ = -gradoOrbita;
		else if (dir == "pos")
			rotZ = gradoOrbita;
		else
			cout << "Error: Direcci�n no reconocida." << endl;

		/*Usamos la matriz de transformaci�n.*/
		GLfloat eyeXAux = cos(rotZ)*this->eye->getX() - sin(rotZ)*this->eye->getY();
		GLfloat eyeYAux = sin(rotZ)*this->eye->getX() + cos(rotZ)*this->eye->getY();
		GLfloat eyeZAux = this->eye->getZ();

		/*Actualiza eye.*/
		eye->setX(eyeXAux);
		eye->setY(eyeYAux);
		eye->setZ(eyeZAux);

		/*Actualiza n u y v.*/
		this->n = nVector();
		this->u = uVector();
		this->v = vVector();

		setUpCamera();
	}


	/*Other methods.*/

	/*Cambiamos de modo de proyecci�n.*/
	void cambioProyeccion() {
		esPerspectiva = !esPerspectiva;
		if (!esPerspectiva)
			setUpOrtho();
		else
			setUpFrustum();
	}

	/*Nos dice si est� en modo perspectiva.*/
	GLboolean isPerspectiva() {
		return esPerspectiva;
	}

	/*Reseteamos la c�mara a su posici�n original.*/
	void resetCamara() {
		this->eye = eyeIni->clona();
		this->look = lookIni->clona();
		this->up = upIni->clona();
	}

	/*Actualizamos el frustum.*/
	void updateFrustumValues(GLfloat xLeft, GLfloat xRight, GLfloat yBot, GLfloat yTop, GLfloat N, GLfloat F) {
		this->left = xLeft;
		this->right = xRight;
		this->top = yTop;
		this->bottom = yBot;
		this->fnear = N;
		this->ffar = F;
	}

};

#endif