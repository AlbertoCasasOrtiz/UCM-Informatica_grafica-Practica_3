#ifndef FICHA_H
#define FICHA_H

#include "PV3D.h"
#include "ObjetoCompuesto3D.h"
#include "Quesito.h"

/*Clase ficha. Es un objeto compuesto formado por 6 quesitos rotados.*/
class Ficha :public ObjetoCompuesto3D{
private:
	/*Array de quesitos.*/
	Quesito **ques;
public:

	/****************
	 *Constructoras.*
	 ****************/

	 /*Constructora de la clase ficha con textura y color.*/
	Ficha(GLint nP, GLfloat a, GLfloat h, Color *color, GLuint texture) {
		this->ques = new Quesito*[6];
		//Se añaden los 6 quesitos al objeto compuesto ficha.
		for (int i = 0; i < 6; i++) {
			this->ques[i] = new Quesito(nP, a, h, color);
			this->introduceObjeto(ques[i]);
			this->ques[i]->setTexture(texture);
		}

		//Se sitúan los quesitos dentro de la ficha.
		GLfloat inc = (GLfloat)M_PI / 6.0f;
		for (int i = 0; i < 6; i++) {
			getHijos(i)->getTAfin()->gira((GLfloat)(i * 60), 'y');
		}
	}

	/*Constructora de la clase ficha.*/
	Ficha(GLint nP, GLfloat a, GLfloat h) {
		//Se añaden los 6 quesitos al objeto compuesto ficha.
		for (int i = 0; i < 6; i++)
			this->introduceObjeto(new Quesito(nP, a, h, new Color(i)));

		//Se sitúan los quesitos dentro de la ficha.
		GLfloat inc = (GLfloat)M_PI / 6.0f;
		for (int i = 0; i < 6; i++) {
			getHijos(i)->getTAfin()->gira((GLfloat)(i * 60), 'y');
		}
	}

	/*Destructora de la clase Ficha.*/
	~Ficha(){
		for (int i = 0; i < 6; i++)
			delete ques[i];
		delete ques;
	}
};


#endif