#ifndef ESCENA_H
#define ESCENA_H

#include "ObjetoCompuesto3D.h"
#include "Autopista.h"
#include "Farola.h"
#include "Coche.h"
#include "SpotLight.h"
#include "Lamp.h"
#include "Esfera.h"
#include "Curva.h"

/*
Clase escena. Contiene una autopista con farolas a los lados y un coche.
*/
class Escena : public ObjetoCompuesto3D {
private:
	/*Número de farolas en la escena.*/
	const GLint NUM_FAROLAS = 6;
	/*Número de fragmentos de autopista en la escena.*/
	const GLint NUM_AUTOPISTA = 56;
	/*Factor que determina la velocidad del coche.*/
	const GLfloat MOV_COCHE = 2;
	/*Factor que determina la velocidad de giro de las ruedas.*/
	const GLfloat MOV_RUEDA = 48;
	
	/*Parámetros para que el coche vaya adelante, atras, gire o vuele.*/
	GLdouble giro, vuelo;
	GLboolean adelante;

	/*Luz de la farola y focos del coche.*/
	SpotLight* spot0, *spot1;
	Lamp* lamp0;

	/*Esfera para probar iluminación.*/
	Esfera* esfera;
	/*Coche.*/
	Coche* coche;
	/*Array de farolas.*/
	Farola** farola;
	/*Array de fragmentos de autopista.*/
	Autopista** autopista;
	/*Array de curvas de autopista.*/
	Curva**curva;
public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase escena.*/
	Escena(SpotLight ** spots, Lamp ** lamps, GLint textura) {
		//Inicializamos los objetos
		this->giro = 0;
		this->vuelo = 0;
		this->adelante = true;
		farola = new Farola*[NUM_FAROLAS];
		for (int i = 0; i < NUM_FAROLAS; i++)
			farola[i] = new Farola(7.0f, 0.2f, 1);
		coche = new Coche(new Color("purple"), textura);
		autopista = new Autopista*[NUM_AUTOPISTA];
		for (int i = 0; i < NUM_AUTOPISTA; i++)
			autopista[i] = new Autopista();
		esfera = new Esfera(4, 12, 12, new Color("white"));
		curva = new Curva*[2];
		for (int i = 0; i < 2; i++)
			curva[i] = new Curva(20);

		//Insertamos los objetos
		for (int i = 0; i < NUM_AUTOPISTA; i++)
			this->introduceObjeto(autopista[i]);
		for (int i = 0; i < NUM_FAROLAS; i++)
			this->introduceObjeto(farola[i]);
		this->introduceObjeto(coche);
		//this->introduceObjeto(esfera);
		for (int i = 0; i < 2; i++)
			this->introduceObjeto(curva[i]);

		//Colocamos el coche
		this->coche->getTAfin()->traslada(new PV3D(0.0, 0.0, -6.0, 1.0));
		this->coche->getTAfin()->gira(90, 'y');

		//this->esfera->getTAfin()->traslada(new PV3D(-8, 0.0, -6.0, 1.0));

		//Colocamos los centros
		for (int i = 0; i < 3; i++) {
			this->coche->getCentros()[i]->setZ(this->coche->getCentros()[i]->getZ() - 2);
		}

		//Colocamos cachos de autopista
		int cont = 0;
		for (int i = 0; i < NUM_AUTOPISTA/2; i++) {
			this->autopista[cont]->getTAfin()->traslada(new PV3D(-i*3.0, 0.0, -6.5, 1.0));
			cont++;
		}

		for (int i = 0; i < NUM_AUTOPISTA / 2; i++) {
			this->autopista[cont]->getTAfin()->traslada(new PV3D(-i*3.0, 0.0, 6.5, 1.0));
			cont++;
		}

		//Colocamos la curva
		this->curva[0]->getTAfin()->gira(180, 'y');
		this->curva[1]->getTAfin()->traslada(new PV3D(-80.0, 0.0, 0.0, 1.0));

		//Colocamos las farolas
		cont = 0;
		for (int i = 0; i < NUM_FAROLAS; i++) {
			this->farola[cont]->getTAfin()->traslada(new PV3D((-i - 1)*12.0, 0.0, 0.0, 1.0));
			cont++;
		}

		//Colocamos las luces de los faros		
		GLfloat dir[] = {10.0f, -0.2f, -6.0f};

		spots[0]->setDir(dir); spots[1]->setDir(dir);
		
		spots[0]->setAlpha(90); spots[1]->setAlpha(90);
		
		spots[0]->setPosition(this->coche->getCentros()[1]);
		spots[1]->setPosition(this->coche->getCentros()[2]);

		spot0 = spots[0]; spot1 = spots[1];

		//Colocamos la luz de una farola
		PV3D *farolaPosition = new PV3D(farola[0]->getCenterSphere()->getX()-12, farola[0]->getCenterSphere()->getY(), farola[0]->getCenterSphere()->getZ(), 1.0);
		lamps[0]->setPosition(farolaPosition);

		lamp0 = lamps[0];
		
	}

	/*Destructora de la clase escena.*/
	~Escena(){
		for (int i = 0; i < NUM_FAROLAS; i++)
			delete farola[i];
		for (int i = 0; i < NUM_AUTOPISTA; i++)
			delete autopista[i];
		for (int i = 0; i < 2; i++)
			delete curva[i];

		delete coche, farola, autopista, curva, esfera, spot0, spot1, lamp0;
	}


	/**********
	 *Getters.*
	 **********/

	/*Devolvemos el centro del coche.*/
	PV3D* getLook() {
		return this->coche->getCentros()[0];
	}

	/*Devolvemos el eye del coche.*/
	PV3D* getEye() {
		return new PV3D(this->getLook()->getX(), this->getLook()->getY(), this->getLook()->getZ(), 1.0);
	}


	/**********************/
	/*Métodos de la clase.*/
	/**********************/

	/*Método que mueve el coche a lo largo de la autopista.*/
	void mueveCoche(bool adelante) {
		//Trasladamos el coche, su centro, y giramos las ruedas.
			if (adelante) {
				this->coche->getTAfin()->gira(this->giro * 20, 'y');
				this->coche->getTAfin()->traslada(new PV3D(this->giro, 0.0, -MOV_COCHE, 1.0));
				//Ponemos el centro del objeto en los centros correspondientes.
				for (int i = 0; i < 3; i++) {
					this->coche->getCentros()[i]->setX(this->coche->getTAfin()->getM()[12]);
					this->coche->getCentros()[i]->setY(this->coche->getTAfin()->getM()[13]);
					this->coche->getCentros()[i]->setZ(this->coche->getTAfin()->getM()[14]);
				}
				this->coche->giraRuedas(MOV_RUEDA, true);
			}
			else {
				this->coche->getTAfin()->gira(-this->giro * 10, 'y');
				this->coche->getTAfin()->traslada(new PV3D(this->giro, 0.0, MOV_COCHE, 1.0));
				//Ponemos el centro del objeto en los centros correspondientes.
				for (int i = 0; i < 3; i++) {
					this->coche->getCentros()[i]->setX(this->coche->getTAfin()->getM()[12]);
					this->coche->getCentros()[i]->setY(this->coche->getTAfin()->getM()[13]);
					this->coche->getCentros()[i]->setZ(this->coche->getTAfin()->getM()[14]);
				}
				this->coche->giraRuedas(MOV_RUEDA, false);
			}


			this->spot0->setPosition(this->coche->getCentros()[1]);
			this->spot1->setPosition(this->coche->getCentros()[2]);
		
	}

	/*Método que apaga la luz de la farola.*/
	void apagaFarola() {
		this->lamp0->disable();
	}

	/*Método que enciende la luz de la farola.*/
	void enciendeFarola() {
		this->lamp0->enable();
	}

	/*Método que apaga el coche.*/
	void apagaCoche() {
		this->spot0->disable();
		this->spot1->disable();
	}

	/*Método que enciende el coche.*/
	void enciendeCoche() {
		this->spot0->enable();
		this->spot1->enable();
	}

	/*Abre la puerta del coche o la cierra.*/
	void abrePuertaCoche(GLboolean open) {
		this->coche->abrePuertas(open);
	}

	/*Gira el coche.*/
	void giraCoche(GLfloat quant) {
		this->coche->giraVolante(quant);
		if (this->giro < 2.1 && quant > 0)
			this->giro += 0.3;
		else if (this->giro > -2.1 && quant < 0)
			this->giro -= 0.3;
		cout << this->giro << endl;
	}

	/*Permite al coche volar.*/
	void vuela(GLboolean volar) {
		if (volar) {
			vuelo += 0.2;
			this->coche->getTAfin()->traslada(new PV3D(0.0, 0.2, 0.0, 1.0));
		}
		else if (!volar && vuelo > 0.2) {
			vuelo -= 0.2;
			this->coche->getTAfin()->traslada(new PV3D(0.0, -0.2, 0.0, 1.0));
		}
		for (int i = 0; i < 3; i++) {
			this->coche->getCentros()[i]->setX(this->coche->getTAfin()->getM()[12]);
			this->coche->getCentros()[i]->setY(this->coche->getTAfin()->getM()[13]);
			this->coche->getCentros()[i]->setZ(this->coche->getTAfin()->getM()[14]);
		}

	}

	/*Hace que el volante no esté girado.*/
	void noGiro() {
		this->giro = 0;
	}
};


#endif