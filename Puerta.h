#ifndef PUERTA_H
#define PUERTA_H

#include "Malla.h"
#include "Color.h"

class Puerta : public Malla {
private:
	/*Número de vértces en el perfil.*/
	const GLint numVerticesPerfil = 4;

	/*Perfil que generará el tubo.*/
	PV3D** perfil;

	/*Indica que frame de la puerta está dibujado.*/
	GLint door;

	/*Perfil de la puerta.*/
	void creaPerfil() {
		this->perfil[0] = new PV3D(0, 0, 0, 1);
		this->perfil[1] = new PV3D(1, 0, 0, 1);
		this->perfil[2] = new PV3D(1, 1, 0, 1);
		this->perfil[3] = new PV3D(0, 1, 0, 1);
		this->insertaVertice(0, 0, 0);
		this->insertaVertice(1, 0, 0);
		this->insertaVertice(1, 1, 0);
		this->insertaVertice(0, 1, 0);
	}


public:

	/****************
	*Constructoras.*
	****************/

	/*Constructora de la clase puerta.*/
	Puerta(Color * color) {
		this->door = 0;
		/*Inicializamos malla y perfil.*/
		this->perfil = new PV3D*[this->numVerticesPerfil];

		/*Creamos el perfil.*/
		this->creaPerfil();
		GLint numVerticesAnt = this->numVertices;
		GLfloat amplitud = M_PI / 4;
		GLint nQ = 5;
		GLfloat rotY = 2 * M_PI / 32;

		/*Obtenemos los vértices de la malla.*/
		for (GLint i = 0; i <= nQ; i++) {
			GLfloat theta = i * amplitud / nQ + rotY;
			GLfloat c = cos(theta);
			GLfloat s = sin(theta);
			for (GLint j = 0; j < numVerticesPerfil; j++) {
				GLint indice = numVerticesAnt + i*numVerticesPerfil + j;
				GLfloat x = c*perfil[j]->getX() + s*perfil[j]->getZ();
				GLfloat z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
				PV3D* p = new PV3D(x, perfil[j]->getY(), z, 1);
				this->insertaVertice(p, indice);
			}
		}

		/*Creamos la cara de la puerta.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(0, 0, 0);
		this->insertaVerticeEnCara(0, 1, 0);
		this->insertaVerticeEnCara(0, 2, 0);
		this->insertaVerticeEnCara(0, 3, 0);

		PV3D* v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);


		/*Creamos la cara de la puerta.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(1, 4, 1);
		this->insertaVerticeEnCara(1, 5, 1);
		this->insertaVerticeEnCara(1, 6, 1);
		this->insertaVerticeEnCara(1, 7, 1);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);


		/*Creamos la cara de la puerta.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(2, 8, 2);
		this->insertaVerticeEnCara(2, 9, 2);
		this->insertaVerticeEnCara(2, 10, 2);
		this->insertaVerticeEnCara(2, 11, 2);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);




		/*Creamos la cara de la puerta.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(3, 12, 3);
		this->insertaVerticeEnCara(3, 13, 3);
		this->insertaVerticeEnCara(3, 14, 3);
		this->insertaVerticeEnCara(3, 15, 3);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);



		/*Creamos la cara de la puerta.*/
		this->creaCara(4);

		this->insertaVerticeEnCara(4, 16, 4);
		this->insertaVerticeEnCara(4, 17, 4);
		this->insertaVerticeEnCara(4, 18, 4);
		this->insertaVerticeEnCara(4, 19, 4);

		v = this->CalculoVectorNormalPorNewell(this->getCara(this->getNumCaras() - 1));

		this->insertaNormal(v->getX(), v->getY(), v->getZ());
		this->insertaColor(color);
	}

	/*Destructora de la clase Puerta.*/
	~Puerta() {
		for (int i = 0; i < this->numVerticesPerfil; i++)
			delete perfil[i];
		delete perfil;
	}

	/**********************
	*Métodos de la clase.*
	**********************/

	/*Método dibuja.*/
	void dibuja() {
		for (GLint i = 0; i < numCaras; i++) {
			glLineWidth(1.0);
			glColor3f(this->color[i]->getR(), this->color[i]->getG(), this->color[i]->getB());
			glBegin(GL_POLYGON); //o glBegin(GL_LINE_LOOP);
			if (i == door) {
				for (GLint j = 0; j < cara[i]->getNumVertices(); j++) {
					GLint iN = cara[i]->getIndiceNormal(j);
					GLint iV = cara[i]->getIndiceVertice(j);
					glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
					//Si hubiera coordenadas de textura, aquí se suministrarían
					//las coordenadas de textura del vértice j con glTexCoor2f(…);
					glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
				}
			}
			glEnd();
		}
	}

	/*Abre la puerta.*/
	void openDoor() {
		if (door < 6) {
			door++;
		}
	}

	/*Cierra la puerta.*/
	void closeDoor() {
		if (door > 0) {
			door--;
		}
	}

};

#endif // !PUERTA_H
