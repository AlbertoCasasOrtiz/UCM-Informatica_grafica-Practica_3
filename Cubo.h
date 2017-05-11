#ifndef CUBO_H
#define CUBO_H

#include "Malla.h"
#include "Color.h"

/*
Clase cubo. Genera un cubo de lado 1 centrado en el origen.
*/
class Cubo: public Malla {
public:

	/****************/
	/*Constructoras.*/
	/****************/
	/*Constructora de la clase cubo.*/
	Cubo(Color * color, GLint texture, GLboolean material) {
		this->material = true;
		this->texture = texture;

		this->insertaVertice(-0.5, -0.5, -0.5);
		this->insertaVertice(-0.5, -0.5, 0.5);
		this->insertaVertice(0.5, -0.5, 0.5);
		this->insertaVertice(0.5, -0.5, -0.5);

		this->insertaVertice(-0.5, 0.5, -0.5);
		this->insertaVertice(-0.5, 0.5, 0.5);
		this->insertaVertice(0.5, 0.5, 0.5);
		this->insertaVertice(0.5, 0.5, -0.5);

		/*Cara inferior.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(0, 3, 0);
		this->insertaVerticeEnCara(0, 2, 0);
		this->insertaVerticeEnCara(0, 1, 0);
		this->insertaVerticeEnCara(0, 0, 0);

		PV3D* v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);


		/*Cara superior.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(1, 4, 1);
		this->insertaVerticeEnCara(1, 5, 1);
		this->insertaVerticeEnCara(1, 6, 1);
		this->insertaVerticeEnCara(1, 7, 1);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);



		/*Cara trasera.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(2, 5, 2);
		this->insertaVerticeEnCara(2, 4, 2);
		this->insertaVerticeEnCara(2, 0, 2);
		this->insertaVerticeEnCara(2, 1, 2);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

		/*Cara frontal.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(3, 7, 3);
		this->insertaVerticeEnCara(3, 6, 3);
		this->insertaVerticeEnCara(3, 2, 3);
		this->insertaVerticeEnCara(3, 3, 3);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

		/*Cara derecha.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(4, 4, 4);
		this->insertaVerticeEnCara(4, 7, 4);
		this->insertaVerticeEnCara(4, 3, 4);
		this->insertaVerticeEnCara(4, 0, 4);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

		/*Cara izquierda.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(5, 6, 5);
		this->insertaVerticeEnCara(5, 5, 5);
		this->insertaVerticeEnCara(5, 1, 5);
		this->insertaVerticeEnCara(5, 2, 5);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

	}
		/*Constructora de la clase cubo.*/
	Cubo(Color * color, GLint texture) {
		this->texture = texture;
		this->insertaVertice(-0.5, -0.5, -0.5);
		this->insertaVertice(-0.5, -0.5, 0.5);
		this->insertaVertice(0.5, -0.5, 0.5);
		this->insertaVertice(0.5, -0.5, -0.5);

		this->insertaVertice(-0.5, 0.5, -0.5);
		this->insertaVertice(-0.5, 0.5, 0.5);
		this->insertaVertice(0.5, 0.5, 0.5);
		this->insertaVertice(0.5, 0.5, -0.5);

		/*Cara inferior.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(0, 3, 0);
		this->insertaVerticeEnCara(0, 2, 0);
		this->insertaVerticeEnCara(0, 1, 0);
		this->insertaVerticeEnCara(0, 0, 0);

		PV3D* v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);


		/*Cara superior.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(1, 4, 1);
		this->insertaVerticeEnCara(1, 5, 1);
		this->insertaVerticeEnCara(1, 6, 1);
		this->insertaVerticeEnCara(1, 7, 1);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);



		/*Cara trasera.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(2, 5, 2);
		this->insertaVerticeEnCara(2, 4, 2);
		this->insertaVerticeEnCara(2, 0, 2);
		this->insertaVerticeEnCara(2, 1, 2);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

		/*Cara frontal.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(3, 7, 3);
		this->insertaVerticeEnCara(3, 6, 3);
		this->insertaVerticeEnCara(3, 2, 3);
		this->insertaVerticeEnCara(3, 3, 3);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

		/*Cara derecha.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(4, 4, 4);
		this->insertaVerticeEnCara(4, 7, 4);
		this->insertaVerticeEnCara(4, 3, 4);
		this->insertaVerticeEnCara(4, 0, 4);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

		/*Cara izquierda.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(5, 6, 5);
		this->insertaVerticeEnCara(5, 5, 5);
		this->insertaVerticeEnCara(5, 1, 5);
		this->insertaVerticeEnCara(5, 2, 5);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

	}
	/*Constructora de la clase cubo.*/
	Cubo(Color * color) {
		this->insertaVertice(-0.5, -0.5, -0.5);
		this->insertaVertice(-0.5, -0.5, 0.5);
		this->insertaVertice(0.5, -0.5, 0.5);
		this->insertaVertice(0.5, -0.5, -0.5);

		this->insertaVertice(-0.5, 0.5, -0.5);
		this->insertaVertice(-0.5, 0.5, 0.5);
		this->insertaVertice(0.5, 0.5, 0.5);
		this->insertaVertice(0.5, 0.5, -0.5);

		/*Cara inferior.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(0, 3, 0);
		this->insertaVerticeEnCara(0, 2, 0);
		this->insertaVerticeEnCara(0, 1, 0);
		this->insertaVerticeEnCara(0, 0, 0);

		PV3D* v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);


		/*Cara superior.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(1, 4, 1);
		this->insertaVerticeEnCara(1, 5, 1);
		this->insertaVerticeEnCara(1, 6, 1);
		this->insertaVerticeEnCara(1, 7, 1);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);



		/*Cara trasera.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(2, 5, 2);
		this->insertaVerticeEnCara(2, 4, 2);
		this->insertaVerticeEnCara(2, 0, 2);
		this->insertaVerticeEnCara(2, 1, 2);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

		/*Cara frontal.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(3, 7, 3);
		this->insertaVerticeEnCara(3, 6, 3);
		this->insertaVerticeEnCara(3, 2, 3);
		this->insertaVerticeEnCara(3, 3, 3);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

		/*Cara derecha.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(4, 4, 4);
		this->insertaVerticeEnCara(4, 7, 4);
		this->insertaVerticeEnCara(4, 3, 4);
		this->insertaVerticeEnCara(4, 0, 4);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);

		/*Cara izquierda.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(5, 6, 5);
		this->insertaVerticeEnCara(5, 5, 5);
		this->insertaVerticeEnCara(5, 1, 5);
		this->insertaVerticeEnCara(5, 2, 5);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);
	}
};

#endif