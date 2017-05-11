#ifndef COCHE_H
#define COCHE_H

#include "ObjetoCompuesto3D.h"
#include "Ficha.h"
#include "Cubo.h"
#include "Faro.h"
#include "Puerta.h"
#include "Volante.h"

/*Clase coche. Construye un coche a partir de 4 fichas (ruedas) y un cubo (cuerpo).*/
class Coche :public ObjetoCompuesto3D {
private:
	/*Array de fichas (ruedas).*/
	Ficha** fichas;
	/*Cuerpo del coche,*/
	Cubo* cuerpo;
	/*Faros del coche.*/
	Faro** faro;
	/*Centro del coche.*/
	PV3D* centro;
	/*Puertas del coche.*/
	Puerta ** puerta;
	/*Volante del coche.*/
	Volante *volante;
	
public:

	/**************** 
	 *Constructoras.* 
	 ****************/

	/*Constructora de la clase coche.*/
	Coche(Color * color, GLint textura) {
		//Definimos el centro.
		centro = new PV3D(0.0, 0.0, 0.0, 1);

		//Declaramos las ruedas y el cuerpo.
		cuerpo = new Cubo(color, textura, true);
		volante = new Volante(textura);
		fichas = new Ficha*[4];
		faro = new Faro*[2];
		puerta = new Puerta*[2];
		for (int i = 0; i < 4; i++)
			fichas[i] = new Ficha(2, 0.4f, 0.2f, new Color("blue"), textura);
		for (int i = 0; i < 2; i++)
			faro[i] = new Faro(0.25f, 0.1f, 0.1f, 20, 1, new Color("yellow"));
		for (int i = 0; i < 2; i++)
			puerta[i] = new Puerta(new Color("purple"));

		//Introducimos los objetos como parte del objeto compuesto.

		this->introduceObjeto(cuerpo);
		for (int i = 0; i < 4; i++)
			this->introduceObjeto(fichas[i]);
		for (int i = 0; i < 2; i++)
			this->introduceObjeto(faro[i]);
		for (int i = 0; i < 2; i++)
			this->introduceObjeto(puerta[i]);
		this->introduceObjeto(volante);

		//Trasladamos todos los hijos y el centro.
		this->centro->setY(this->centro->getY() + 0.9f);
		for (int i = 0; i < 10; i++)
			this->getHijos(i)->getTAfin()->traslada(new PV3D(0.0f, 0.9f, 0.0f, 1));

		//Colocamos las ruedas.
		this->fichas[0]->getTAfin()->traslada(new PV3D(-0.5f, -0.5f, 0.5f, 1));
		this->fichas[0]->getTAfin()->gira(90, 'z');

		this->fichas[1]->getTAfin()->traslada(new PV3D(-0.5f, -0.5f, -0.5f, 1));
		this->fichas[1]->getTAfin()->gira(90, 'z');


		this->fichas[2]->getTAfin()->traslada(new PV3D(0.5f, -0.5f, 0.5f, 1));
		this->fichas[2]->getTAfin()->gira(-90, 'z');

		this->fichas[3]->getTAfin()->traslada(new PV3D(0.5f, -0.5f, -0.5f, 1));
		this->fichas[3]->getTAfin()->gira(-90, 'z');

		//Colocamos las puertas.
		this->puerta[0]->getTAfin()->gira(90, 'y');
		this->puerta[1]->getTAfin()->gira(90, 'y');
		this->puerta[1]->getTAfin()->traslada(new PV3D(-0.5, -0.5, -0.5, 1.0));

		this->puerta[0]->getTAfin()->traslada(new PV3D(-0.5, -0.5, 0.5, 1.0));
		this->puerta[0]->getTAfin()->gira(180, 'x');
		this->puerta[0]->getTAfin()->traslada(new PV3D(0.0, -1.0, 0.0, 1.0));

		//Colocamos el volante.
		this->volante->getTAfin()->gira(180, 'x');
		this->volante->getTAfin()->traslada(new PV3D(0.0, -1.0, 0.0, 1.0));

		//Colocamos los faros.
		this->faro[0]->getTAfin()->traslada(new PV3D(-0.25f, -0.2f, 0.5f, 1.0f));
		this->faro[1]->getTAfin()->traslada(new PV3D(0.25f, -0.2f, 0.5f, 1.0f));
		for (int i = 0; i < 2; i++) {
			this->faro[i]->getTAfin()->escala(new PV3D(0.25f, 0.25f, 0.25f, 1.0f));
			this->faro[i]->getTAfin()->gira(90, 'x');
		}
	}

	/*Destructora de la clase coche.*/
	~Coche(){
		for (int i = 0; i < 4; i++)
			delete fichas[i];
		for (int i = 0; i < 2; i++)
			delete faro[i];
		for (int i = 0; i < 2; i++)
			delete puerta[i];
		delete fichas, cuerpo, centro, faro, volante, puerta;
	}

	/**********
	 *Getters.*
	 **********/

	/*Método que devuelve el centro del coche.*/
	PV3D** getCentros() {
		PV3D **centros = new PV3D*[3];
		centros[0] = this->centro;
		centros[1] = faro[0]->getCentroDisco();
		centros[2] = faro[1]->getCentroDisco();
		return centros;
	}

	/**********************
	 *Métodos de la clase.*
	 **********************/

	/*Método que gira las ruedas.*/
	void giraRuedas(GLfloat movRueda, boolean mov) {
		if (!mov)
			movRueda = -movRueda;
		for (int i = 0; i < 2; i++)
			fichas[i]->getTAfin()->gira(movRueda, 'y');
		for(int i = 2; i < 4; i++)
			fichas[i]->getTAfin()->gira(-movRueda, 'y');
	}

	/*Método que abre las puertas del coche.*/
	void abrePuertas(GLboolean open) {
		if (!open) {
			for (int i = 0; i < 2; i++)
				puerta[i]->openDoor();
		}
		else
			for (int i = 0; i < 2; i++)
				puerta[i]->closeDoor();
	}

	/*Método que gira el volante del coche.*/
	void giraVolante(GLfloat quantity) {
		this->volante->getTAfin()->gira(quantity, 'y');

	}


};

#endif