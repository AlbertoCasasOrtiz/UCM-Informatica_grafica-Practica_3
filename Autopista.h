#ifndef AUTOPISTA_H
#define AUTOPISTA_H

#include "ObjetoCompuesto3D.h"
#include "Color.h"
#include "Tablero.h"

/*
Clase Autopista.
Contiene una carretera formada por Tableros.
*/
class Autopista : public ObjetoCompuesto3D {
public:

	/****************
	 *Constructoras.*
	 ****************/

	/*Constructora de la clase autopista. A la derecha de x.*/
	Autopista(GLint a) {
		for (int i = 0; i < 2; i++)
			introduceObjeto(new Tablero(3, 1, 3, new Color(0.3f, 0.3f, 0.3f)));

		//Insertamos línea de separación
		introduceObjeto(new Tablero(3, 1, 1, new Color("white")));

		//Insertamos acera
		for (int i = 0; i < 2; i++)
			introduceObjeto(new Tablero(3, 1, 3, new Color(0.6f, 0.6f, 0.6f)));

		//Aumentamos tamaño acera
		for (int i = 3; i < 5; i++)
			this->getHijos(i)->getTAfin()->escala(new PV3D(1.0f, 1.2f, 1.0f, 1.0f));

		//Cetramos
		this->getHijos(0)->getTAfin()->traslada(new PV3D(-1, 0, -2.5, 1));
		this->getHijos(1)->getTAfin()->traslada(new PV3D(-1, 0, 0.5, 1));
		this->getHijos(2)->getTAfin()->traslada(new PV3D(-1, 0, 0, 1));
		this->getHijos(3)->getTAfin()->traslada(new PV3D(-1, 0, 0, 1));
		this->getHijos(4)->getTAfin()->traslada(new PV3D(-1, 0, 0, 1));

		//Lo ponemos bajo XZ
		for (int i = 0; i < 5; i++)
			this->getHijos(i)->getTAfin()->traslada(new PV3D(0, -0.5, 0, 1));

		//Colocamos la acera
		for (int i = 3; i < 5; i++)
			this->getHijos(i)->getTAfin()->traslada(new PV3D(0.0f, 0.15f, 0.0f, 1));

		//Separamos ambos sentidos a ambos lados de la línea de separación
		this->getHijos(0)->getTAfin()->traslada(new PV3D(0.0f, 0.0f, -0.5f, 1));
		this->getHijos(1)->getTAfin()->traslada(new PV3D(0.0f, 0.0f, 0.5f, 1));

		//Separamos acera
		this->getHijos(3)->getTAfin()->traslada(new PV3D(0.0f, 0.0f, -6.0f, 1));
		this->getHijos(4)->getTAfin()->traslada(new PV3D(0.0f, 0.0f, 4.0f, 1));

		//Los movemos a la derecha de x.
		for (int i = 0; i < 5; i++)
			this->getHijos(i)->getTAfin()->traslada(new PV3D(0, 0.0, -6.5, 1));
	}

	/*Constructora de la clase autopista.*/
	Autopista() {
		for (int i = 0; i < 2; i++)
			introduceObjeto(new Tablero(3, 1, 3, new Color(0.3f, 0.3f, 0.3f)));

		//Insertamos línea de separación
		introduceObjeto(new Tablero(3, 1, 1, new Color("white")));

		//Insertamos acera
		for (int i = 0; i < 2; i++)
			introduceObjeto(new Tablero(3, 1, 3, new Color(0.6f, 0.6f, 0.6f)));

		//Aumentamos tamaño acera
		for (int i = 3; i < 5; i++)
			this->getHijos(i)->getTAfin()->escala(new PV3D(1.0f, 1.2f, 1.0f, 1.0f));

		//Cetramos
		this->getHijos(0)->getTAfin()->traslada(new PV3D(-1, 0, -2.5, 1));
		this->getHijos(1)->getTAfin()->traslada(new PV3D(-1, 0, 0.5, 1));
		this->getHijos(2)->getTAfin()->traslada(new PV3D(-1, 0, 0, 1));
		this->getHijos(3)->getTAfin()->traslada(new PV3D(-1, 0, 0, 1));
		this->getHijos(4)->getTAfin()->traslada(new PV3D(-1, 0, 0, 1));

		//Lo ponemos bajo XZ
		for (int i = 0; i < 5; i++)
			this->getHijos(i)->getTAfin()->traslada(new PV3D(0, -0.5, 0, 1));

		//Colocamos la acera
		for (int i = 3; i < 5; i++)
			this->getHijos(i)->getTAfin()->traslada(new PV3D(0.0f, 0.15f, 0.0f, 1));

		//Separamos ambos sentidos a ambos lados de la línea de separación
		this->getHijos(0)->getTAfin()->traslada(new PV3D(0.0f, 0.0f, -0.5f, 1));
		this->getHijos(1)->getTAfin()->traslada(new PV3D(0.0f, 0.0f, 0.5f, 1));

		//Separamos acera
		this->getHijos(3)->getTAfin()->traslada(new PV3D(0.0f, 0.0f, -6.0f, 1));
		this->getHijos(4)->getTAfin()->traslada(new PV3D(0.0f, 0.0f, 4.0f, 1));
	}
};


#endif