#ifndef QUESITO_H
#define QUESITO_H

#include <gl/GL.h>

#include "Malla.h"

/*
Clase quesito. Define un quesito de un color determinado.
*/
class Quesito : public Malla{
private:
	/*N�mero de v�rtces en el perfil.*/
	const GLint numVerticesPerfil = 3;

	/*Perfil que generar� el tubo.*/
	PV3D** perfil;

	/*Crea el perfil.*/
	void creaPerfil(GLfloat radio, GLfloat altura) {
		this->perfil[0] = new PV3D(radio, 0.0, 0.0, 1);
		this->perfil[1] = new PV3D(radio, altura, 0.0, 1);
		this->perfil[2] = new PV3D(0.0, altura, 0.0, 1);
	}

public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Generamos un quesito con cierta rotaci�n roty sobre el eje y.*/
	Quesito(GLint nQ, GLfloat radio, GLfloat altura, GLfloat rotY, Color* color) {
		/*Inicializamos malla y perfil.*/
		this->perfil = new PV3D*[this->numVerticesPerfil];

		/*Creamos el perfil.*/
		this->creaPerfil(radio, altura);

		/*Llamamos al m�todo revoluci�n, que generar� los v�rtices y las caras.*/
		this->revoluci�n(this->perfil, this->numVerticesPerfil, nQ, radio, altura, rotY, (GLfloat)M_PI/3-0.03, color);

		/*Guardamos los �ltimos v�rtices generados.*/
		GLint verticeUltimaArriba = this->getNumVertices() - 3;
		GLint verticeUltimaAbajo = this->getNumVertices() - 2;

		
		/*Ahora creamos las caras laterales.*/
		
		/*Generamos los v�rtices centraes.*/
		this->insertaVertice(0.0, altura, 0.0);
		this->insertaVertice(0.0, 0.0, 0.0);

		/*Cara lateral izquierda.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(this->getNumCaras() - 1, 1, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, this->getNumVertices() - 2, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, this->getNumVertices() - 1, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras()-1, 0, this->getNumNormales());

		PV3D* v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras()-1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color->getR(), color->getG(), color->getB());

		/*Cara lateral derecha.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(this->getNumCaras() - 1, verticeUltimaAbajo, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, verticeUltimaArriba, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, this->getNumVertices() - 1, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, this->getNumVertices() - 2, this->getNumNormales());

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color->getR(), color->getG(), color->getB());

		
	}

	/*Generamos un quesito.*/
	Quesito(GLint nQ, GLfloat radio, GLfloat altura, Color* color) {
		/*Inicializamos malla y perfil.*/
		Malla();
		this->perfil = new PV3D*[this->numVerticesPerfil];

		/*Creamos el perfil.*/
		this->creaPerfil(radio, altura);

		/*Llamamos al m�todo revoluci�n, que generar� los v�rtices y las caras.*/
		this->revoluci�n(this->perfil, this->numVerticesPerfil, nQ, radio, altura, 0, M_PI / 3 - 0.03, color);

		/*Guardamos los �ltimos v�rtices generados.*/
		GLint verticeUltimaArriba = this->getNumVertices() - 3;
		GLint verticeUltimaAbajo = this->getNumVertices() - 2;

		/*Ahora creamos las caras laterales.*/
		
		/*Generamos los v�rtices centraes.*/
		this->insertaVertice(0.0, altura, 0.0);
		this->insertaVertice(0.0, 0.0, 0.0);

		/*Cara lateral izquierda.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(this->getNumCaras() - 1, 1, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, this->getNumVertices() - 2, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, this->getNumVertices() - 1, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, 0, this->getNumNormales());

		PV3D* v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color->getR(), color->getG(), color->getB());

		/*Cara lateral derecha.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(this->getNumCaras() - 1, verticeUltimaAbajo, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, verticeUltimaArriba, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, this->getNumVertices() - 1, this->getNumNormales());
		this->insertaVerticeEnCara(this->getNumCaras() - 1, this->getNumVertices() - 2, this->getNumNormales());

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color->getR(), color->getG(), color->getB());


	}
	
	/*Destructora de la clase quesito.*/
	~Quesito() {
		for (int i = 0; i < numVerticesPerfil; i++) {
			delete this->perfil[i];
		}
		delete this->perfil;
	}
};

#endif