#ifndef VOLANTE_H
#define VOLANTE_H

#include "Cilindro.h"
#include "Ficha.h"

/*
Clase volante. Es el volante del coche.
*/
class Volante : public ObjetoCompuesto3D {
private:
	/*Cilindro que forma el cuerpo del volante.*/
	Cilindro * cilindro;
	/*Ficha que forma la parte superior del volante.*/
	Ficha *ficha;
public:

	/****************
	*Constructoras.*
	****************/

	/*Constructora de la clase volante con textura.*/
	Volante(GLuint texture) {
		this->cilindro = new Cilindro(0.1, 0.1, 1, 20, 2, new Color("red"));
		this->ficha = new Ficha(5, 0.5, 0.2, new Color("red"), texture);

		this->introduceObjeto(this->cilindro);
		this->introduceObjeto(this->ficha);

		this->ficha->getTAfin()->gira(180, 'x');
		this->ficha->getTAfin()->traslada(new PV3D(0.0, -0.2, 0.0, 1.0));
	}

	/*Constructora de la clase volante.*/
	Volante() {
		this->cilindro = new Cilindro(0.1, 0.1, 1, 20, 2, new Color("yellow"));
		this->ficha = new Ficha(5, 0.5, 0.2);

		this->introduceObjeto(this->cilindro);
		this->introduceObjeto(this->ficha);

		this->ficha->getTAfin()->gira(180, 'x');
		this->ficha->getTAfin()->traslada(new PV3D(0.0, -0.2, 0.0, 1.0));
	}

	/*Destructora de la clase volante.*/
	~Volante() {
		delete cilindro, ficha;
	}
};


#endif // !VOLANTE_H
